#include <fstream>
#include <queue>
#include <vector>

using namespace std;

class Node {
private:
    int32_t value;
    Node* left;
    Node* right;

public:
    Node(): value(0), left(nullptr), right(nullptr) {
    }

    explicit Node(const int32_t val): value(val), left(nullptr), right(nullptr) {
    }

    ~Node() = default;

    int32_t getValue() const { return value; }
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }

    void setValue(const int32_t val) { value = val; }
    void setLeft(Node* node) { left = node; }
    void setRight(Node* node) { right = node; }
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    explicit BinaryTree(const int32_t root_val) : root(new Node(root_val)) {}

    BinaryTree(const BinaryTree& other) : root(nullptr) {
        if (other.root != nullptr) {
            queue<Node*> q_nodes;
            q_nodes.push(other.root);

            while (!q_nodes.empty()) {
                Node* current = q_nodes.front();
                q_nodes.pop();

                insert(current->getValue());

                if (current->getLeft() != nullptr) {
                    q_nodes.push(current->getLeft());
                }
                if (current->getRight() != nullptr) {
                    q_nodes.push(current->getRight());
                }
            }
        }
    }

    BinaryTree(BinaryTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    ~BinaryTree() {
        clear();
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear();
            if (other.root != nullptr) {
                queue<Node*> nodes;
                nodes.push(other.root);

                while (!nodes.empty()) {
                    Node* current = nodes.front();
                    nodes.pop();

                    insert(current->getValue());

                    if (current->getLeft() != nullptr) {
                        nodes.push(current->getLeft());
                    }
                    if (current->getRight() != nullptr) {
                        nodes.push(current->getRight());
                    }
                }
            }
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    void insert(const int32_t value) {
        Node* newNode = new Node(value);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (value < current->getValue()) {
                current = current->getLeft();
                if (current == nullptr) {
                    parent->setLeft(newNode);
                    return;
                }
            } else if (value > current->getValue()){
                current = current->getRight();
                if (current == nullptr) {
                    parent->setRight(newNode);
                    return;
                }
            }
            else {
                delete newNode;
                return;
            }
        }
    }

    vector<int32_t> VLR() const {
        vector<int32_t> result;
        VLR_recursive(root, result);
        return result;
    }

    void clear() {
        clearRecursive(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    Node* getRoot() const {
        return root;
    }

private:
    static void clearRecursive(Node* node) {
        if (node != nullptr) {
            clearRecursive(node->getLeft());
            clearRecursive(node->getRight());
            delete node;
        }
    }

    static void VLR_recursive(const Node* node, vector<int32_t>& vlr) {
        if (node != nullptr) {
            vlr.push_back(node->getValue());
            VLR_recursive(node->getLeft(), vlr);
            VLR_recursive(node->getRight(), vlr);
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t number;
    BinaryTree tree;
    while (in >> number) {
        tree.insert(number);
    }

    vector<int32_t> vlr = tree.VLR();

    for (int32_t val: vlr) {
        out << val << endl;
    }

    in.close();
    out.close();
    return 0;
}
