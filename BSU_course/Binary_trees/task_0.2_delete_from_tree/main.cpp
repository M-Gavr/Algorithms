#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

class Node {
private:
    int32_t value_;
    Node* left_;
    Node* right_;

public:
    Node(): value_(0), left_(nullptr), right_(nullptr) {
    }

    explicit Node(const int32_t val): value_(val), left_(nullptr), right_(nullptr) {
    }

    ~Node() = default;

    int32_t value() const { return value_; }
    Node* left() const { return left_; }
    Node* right() const { return right_; }

    void set_value(const int32_t val) { value_ = val; }
    void set_left(Node* node) { left_ = node; }
    void set_right(Node* node) { right_ = node; }

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
public:
    BinaryTree() : root_(nullptr) {}

    explicit BinaryTree(const int32_t root_val) : root_(new Node(root_val)) {}

    BinaryTree(const BinaryTree& other) : root_(nullptr) {
        if (other.root_ != nullptr) {
            queue<Node*> q_nodes;
            q_nodes.push(other.root_);

            while (!q_nodes.empty()) {
                Node* current = q_nodes.front();
                q_nodes.pop();

                Insert(current->value());

                if (current->left() != nullptr) {
                    q_nodes.push(current->left());
                }
                if (current->right() != nullptr) {
                    q_nodes.push(current->right());
                }
            }
        }
    }

    BinaryTree(BinaryTree&& other) noexcept : root_(other.root_) {
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

                    Insert(current->value());

                    if (current->left() != nullptr) {
                        nodes.push(current->left());
                    }
                    if (current->right() != nullptr) {
                        nodes.push(current->right());
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
            other.root_ = nullptr;
        }
        return *this;
    }

    void Insert(const int32_t value) {
        Node* newNode = new Node(value);

        if (root_ == nullptr) {
            root_ = newNode;
            return;
        }

        Node* current = root_;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->value()) {
                current = current->left();
                if (current == nullptr) {
                    parent->set_left(newNode);
                    return;
                }
            } else if (value > current->value()){
                current = current->right();
                if (current == nullptr) {
                    parent->set_right(newNode);
                    return;
                }
            }
            else {
                delete newNode;
                return;
            }
        }
    }

    vector<int32_t> Vlr() const {
        vector<int32_t> result;
        VlrRecursive(root_, result);
        return result;
    }

    void Remove(int32_t target) {
        if (root_ == nullptr) return;

        Node* parent = nullptr;
        Node* current = root_;

        while (current != nullptr && current->value() != target) {
            parent = current;
            if (target < current->value()) {
                current = current->left();
            } else {
                current = current->right();
            }
        }

        if (current == nullptr) return;

        if (current->IsLeaf()) {
            if (parent == nullptr) {
                root_ = nullptr;
            } else if (parent->left() == current) {
                parent->set_left(nullptr);
            } else {
                parent->set_right(nullptr);
            }
            delete current;
            return;
        }

        if (current->HasOneChild()) {
            Node* child = (current->left() != nullptr) ? current->left() : current->right();

            if (parent == nullptr) {
                root_ = child;
            } else if (parent->left() == current) {
                parent->set_left(child);
            } else {
                parent->set_right(child);
            }
            delete current;
            return;
        }

        Node* temp_parent = current;
        Node* temp = current->right();

        while (temp->left() != nullptr) {
            temp_parent = temp;
            temp = temp->left();
        }

        current->set_value(temp->value());

        if (temp_parent->left() == temp) {
            temp_parent->set_left(temp->right());
        } else {
            temp_parent->set_right(temp->right());
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

    Node* root() const {
        return root_;
    }

private:
    Node* root_;

    static void ClearRecursive(Node* node) {
        if (node != nullptr) {
            ClearRecursive(node->left());
            ClearRecursive(node->right());
            delete node;
        }
    }

    static void VlrRecursive(const Node* node, vector<int32_t>& vlr) {
        if (node != nullptr) {
            vlr.push_back(node->value());
            VlrRecursive(node->left(), vlr);
            VlrRecursive(node->right(), vlr);
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t tar = 0;
    in >> tar;

    int32_t number = 0;
    BinaryTree tree;
    while (in >> number) {
        tree.Insert(number);
    }

    tree.Remove(tar);

    vector<int32_t> vlr = tree.Vlr();

    for (int32_t val: vlr) {
        out << val << endl;
    }

    in.close();
    out.close();
    return 0;
}
