#include <algorithm>
#include <cstdint>
#include <fstream>
#include <queue>

using namespace std;

class Node {
   private:
    int32_t value_;
    Node* left_;
    Node* right_;
    int32_t height_;
    int32_t height_vars_;
    int32_t parent_height_;
    int32_t parent_height_vars_;
    int32_t path_count_;

   public:
    Node()
        : value_(0)
        , left_(nullptr)
        , right_(nullptr)
        , height_(0)
        , height_vars_(1)
        , parent_height_(-1)
        , parent_height_vars_(0)
        , path_count_(0) {
    }

    explicit Node(const int32_t val)
        : value_(val)
        , left_(nullptr)
        , right_(nullptr)
        , height_(0)
        , height_vars_(1)
        , parent_height_(-1)
        , parent_height_vars_(0)
        , path_count_(0) {
    }

    ~Node() = default;

    int32_t GetValue() const {
        return value_;
    }

    Node* GetLeft() const {
        return left_;
    }

    Node* GetRight() const {
        return right_;
    }

    int32_t GetHeight() const {
        return height_;
    }

    int32_t GetHeightVars() const {
        return height_vars_;
    }

    int32_t GetParentHeight() const {
        return parent_height_;
    }

    int32_t GetParentHeightVars() const {
        return parent_height_vars_;
    }

    int32_t GetPathCount() const {
        return path_count_;
    }

    void setValue(const int32_t& val) {
        value_ = val;
    }

    void setLeft(Node* node) {
        left_ = node;
    }

    void setRight(Node* node) {
        right_ = node;
    }

    void setHeight(const int32_t& h) {
        height_ = h;
    }

    void setHeightVars(const int32_t& count) {
        height_vars_ = count;
    }

    void setParentHeight(const int32_t& height) {
        parent_height_ = height;
    }

    void setParentHeightVars(const int32_t& vars) {
        parent_height_vars_ = vars;
    }

    void setPathCount(const int32_t& count) {
        path_count_ = count;
    }

    void IncreasePathCount(const int32_t& count) {
        path_count_ += count;
    }

    bool IsLeaf() const {
        return left_ == nullptr && right_ == nullptr;
    }

    bool HasOneChild() const {
        return (left_ != nullptr && right_ == nullptr) || (left_ == nullptr && right_ != nullptr);
    }

    bool HasTwoChildren() const {
        return left_ != nullptr && right_ != nullptr;
    }
};

class BinaryTree {
   private:
    Node* root_;
    int32_t global_max_path_;

   public:
    int32_t GetMaxPaths() const {
        return global_max_path_;
    }

    BinaryTree() : root_(nullptr), global_max_path_(0) {
    }

    explicit BinaryTree(const int32_t root_val) : root_(new Node(root_val)), global_max_path_(0) {
    }

    BinaryTree(const BinaryTree& other) : root_(nullptr), global_max_path_(0) {
        if (other.root_ != nullptr) {
            queue<Node*> q_nodes;
            q_nodes.push(other.root_);

            while (!q_nodes.empty()) {
                Node* current = q_nodes.front();
                q_nodes.pop();

                Insert(current->GetValue());

                if (current->GetLeft() != nullptr) {
                    q_nodes.push(current->GetLeft());
                }
                if (current->GetRight() != nullptr) {
                    q_nodes.push(current->GetRight());
                }
            }
        }
    }

    BinaryTree(BinaryTree&& other) noexcept
        : root_(other.root_), global_max_path_(other.global_max_path_) {
        other.root_ = nullptr;
    }

    ~BinaryTree() {
        Clear();
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            Clear();
            if (other.root_ != nullptr) {
                queue<Node*> nodes;
                nodes.push(other.root_);

                while (!nodes.empty()) {
                    Node* current = nodes.front();
                    nodes.pop();

                    Insert(current->GetValue());

                    if (current->GetLeft() != nullptr) {
                        nodes.push(current->GetLeft());
                    }
                    if (current->GetRight() != nullptr) {
                        nodes.push(current->GetRight());
                    }
                }
            }
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            Clear();
            root_ = other.root_;
            global_max_path_ = other.global_max_path_;
            other.root_ = nullptr;
        }
        return *this;
    }

    void Insert(const int32_t value) {
        Node* new_node = new Node(value);

        if (root_ == nullptr) {
            root_ = new_node;
            return;
        }

        Node* current = root_;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->GetValue()) {
                current = current->GetLeft();
                if (current == nullptr) {
                    parent->setLeft(new_node);
                    return;
                }
            } else if (value > current->GetValue()) {
                current = current->GetRight();
                if (current == nullptr) {
                    parent->setRight(new_node);
                    return;
                }
            } else {
                delete new_node;
                return;
            }
        }
    }

    vector<tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>> VLR() const {
        vector<tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>> result;
        VlrRecursive(root_, result);
        return result;
    }

    void ExecuteHeightsAndPaths() {
        if (root_ != nullptr) {
            global_max_path_ = 0;
            ExecuteHeightsAndGlobalMaxRecursiveAndHeightVariantsRecursive(root_);
            ExecutePathsNumbers();
        }
    }

    void Remove(int32_t target) {
        if (root_ == nullptr) {
            return;
        }

        Node* parent = nullptr;
        Node* current = root_;

        while (current != nullptr && current->GetValue() != target) {
            parent = current;
            if (target < current->GetValue()) {
                current = current->GetLeft();
            } else {
                current = current->GetRight();
            }
        }

        if (current == nullptr) {
            return;
        }

        if (current->IsLeaf()) {
            if (parent == nullptr) {
                root_ = nullptr;
            } else if (parent->GetLeft() == current) {
                parent->setLeft(nullptr);
            } else {
                parent->setRight(nullptr);
            }
            delete current;
            return;
        }

        if (current->HasOneChild()) {
            Node* child =
                (current->GetLeft() != nullptr) ? current->GetLeft() : current->GetRight();

            if (parent == nullptr) {
                root_ = child;
            } else if (parent->GetLeft() == current) {
                parent->setLeft(child);
            } else {
                parent->setRight(child);
            }
            delete current;
            return;
        }

        Node* temp_parent = current;
        Node* temp = current->GetRight();

        while (temp->GetLeft() != nullptr) {
            temp_parent = temp;
            temp = temp->GetLeft();
        }

        current->setValue(temp->GetValue());

        if (temp_parent->GetLeft() == temp) {
            temp_parent->setLeft(temp->GetRight());
        } else {
            temp_parent->setRight(temp->GetRight());
        }

        delete temp;
    }

    void Clear() {
        ClearRecursive(root_);
        root_ = nullptr;
    }

    bool IsEmpty() const {
        return root_ == nullptr;
    }

    Node* GetRoot() const {
        return root_;
    }

   private:
    static void ClearRecursive(Node* node) {
        if (node != nullptr) {
            ClearRecursive(node->GetLeft());
            ClearRecursive(node->GetRight());
            delete node;
        }
    }

    static void VlrRecursive(
        const Node* node,
        vector<tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>>& vlr) {
        if (node != nullptr) {
            const tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t> par = {
              node->GetValue(),        node->GetHeight(),           node->GetHeightVars(),
              node->GetParentHeight(), node->GetParentHeightVars(), node->GetPathCount()};
            vlr.push_back(par);
            VlrRecursive(node->GetLeft(), vlr);
            VlrRecursive(node->GetRight(), vlr);
        }
    }

    pair<int32_t, int32_t> ExecuteHeightsAndGlobalMaxRecursiveAndHeightVariantsRecursive(
        Node* node) {
        if (node == nullptr) {
            return {-1, 0};
        }

        const pair<int32_t, int32_t> left_height =
            ExecuteHeightsAndGlobalMaxRecursiveAndHeightVariantsRecursive(node->GetLeft());
        const pair<int32_t, int32_t> right_height =
            ExecuteHeightsAndGlobalMaxRecursiveAndHeightVariantsRecursive(node->GetRight());

        node->setHeight(max(left_height.first, right_height.first) + 1);
        node->setHeightVars(
            (left_height.first == right_height.first)
                ? ((left_height.second + right_height.second) == 0
                       ? 1
                       : left_height.second + right_height.second)
                : max(left_height.second, right_height.second));

        const int32_t path_through_node = left_height.first + right_height.first + 2;
        global_max_path_ = max(path_through_node, global_max_path_);

        return {node->GetHeight(), node->GetHeightVars()};
    }

    void ExecutePathsNumbers() {
        if (root_ == nullptr) {
            return;
        }

        queue<Node*> clear_queue;
        clear_queue.push(root_);
        while (!clear_queue.empty()) {
            Node* curr = clear_queue.front();
            clear_queue.pop();
            curr->setPathCount(0);
            if (curr->GetLeft() != nullptr) {
                clear_queue.push(curr->GetLeft());
            }
            if (curr->GetRight() != nullptr) {
                clear_queue.push(curr->GetRight());
            }
        }

        // Инициализация для корня
        root_->setParentHeight(-1);
        root_->setParentHeightVars(1);

        queue<pair<Node*, Node*>> bfs_queue;
        bfs_queue.emplace(root_, nullptr);

        while (!bfs_queue.empty()) {
            Node* node = bfs_queue.front().first;
            Node* parent = bfs_queue.front().second;
            bfs_queue.pop();

            // Высоты детей
            int32_t left_h = (node->GetLeft() != nullptr) ? node->GetLeft()->GetHeight() : -1;
            int32_t right_h = (node->GetRight() != nullptr) ? node->GetRight()->GetHeight() : -1;

            // Высота от родителя (уже вычисленная для родителя)
            int32_t parent_h = (parent != nullptr) ? parent->GetParentHeight() : -1;

            // Количество вариантов от родителя (для корня parent_vars = 1)
            int32_t parent_vars = 1;
            if (parent != nullptr && parent_h >= 0) {
                parent_vars = (parent != nullptr) ? parent->GetParentHeightVars() : 1;
            } else if (parent != nullptr && parent_h == -1) {
                parent_vars = 1;
            }

            // Находим брата
            Node* brother = nullptr;
            if (parent != nullptr) {
                brother = (parent->GetLeft() == node) ? parent->GetRight() : parent->GetLeft();
            }

            // Вычисляем высоту и варианты через брата
            int32_t brother_h = -2;
            int32_t brother_vars = 0;
            if (brother != nullptr) {
                brother_h = brother->GetHeight();
                brother_vars = brother->GetHeightVars();
            }

            // ===== ПОДСЧЕТ ПУТЕЙ =====

            // 1. Путь через два поддерева (вершина - центр)
            if (left_h + right_h + 2 == global_max_path_) {
                int32_t left_cnt = (left_h >= 0) ? node->GetLeft()->GetHeightVars() : 1;
                int32_t right_cnt = (right_h >= 0) ? node->GetRight()->GetHeightVars() : 1;
                node->IncreasePathCount(left_cnt * right_cnt);
            }

            // 2. Путь через левое поддерево и родителя
            if (left_h >= 0 && parent_h >= 0 && left_h + parent_h + 2 == global_max_path_) {
                int32_t left_cnt = node->GetLeft()->GetHeightVars();
                node->IncreasePathCount(left_cnt * parent_vars);
            }

            // 3. Путь через правое поддерево и родителя
            if (right_h >= 0 && parent_h >= 0 && right_h + parent_h + 2 == global_max_path_) {
                int32_t right_cnt = node->GetRight()->GetHeightVars();
                node->IncreasePathCount(right_cnt * parent_vars);
            }

            // ===== ВЫЧИСЛЕНИЕ parent_height ДЛЯ ДЕТЕЙ =====

            // Путь вверх через родителя
            int32_t up_through_parent = parent_h + 1;
            int32_t up_through_parent_vars = parent_vars;

            // Путь вверх через брата (идет вниз до брата, потом вверх)
            int32_t up_through_brother = brother_h + 2;
            int32_t up_through_brother_vars = brother_vars;

            // Выбираем максимальный путь вверх
            if (up_through_parent > up_through_brother) {
                node->setParentHeight(up_through_parent);
                node->setParentHeightVars(up_through_parent_vars);
            } else if (up_through_brother > up_through_parent) {
                node->setParentHeight(up_through_brother);
                node->setParentHeightVars(up_through_brother_vars);
            } else if (up_through_parent == up_through_brother) {
                node->setParentHeight(up_through_parent);
                if (up_through_parent == -1) {
                    node->setParentHeightVars(1);
                } else {
                    node->setParentHeightVars(up_through_parent_vars + up_through_brother_vars);
                }
            } else {
                // Этот случай не должен произойти, но на всякий случай
                node->setParentHeight(-1);
                node->setParentHeightVars(1);
            }

            // Добавляем детей в очередь
            if (node->GetLeft() != nullptr) {
                bfs_queue.emplace(node->GetLeft(), node);
            }
            if (node->GetRight() != nullptr) {
                bfs_queue.emplace(node->GetRight(), node);
            }
        }
    }
};

int main() {
    ifstream in("../input.txt");
    ofstream out("../output.txt");

    int32_t number = 0;
    BinaryTree tree;
    while (in >> number) {
        tree.Insert(number);
    }

    tree.Remove(tree.GetRoot()->GetValue());
    tree.ExecuteHeightsAndPaths();

    const vector<tuple<int32_t, int32_t, int32_t, int32_t, int32_t, int32_t>> vlr = tree.VLR();

    for (auto [val, height, height_var, parent_height, parent_height_vars, count] : vlr) {
        out << "v = " << val << " h = " << height << " h_v = " << height_var << " p_h = "
            << parent_height << " p_h_v = " << parent_height_vars << " c = " << count << '\n';
    }

    out << tree.GetMaxPaths() << '\n';

    in.close();
    out.close();
    return 0;
}
