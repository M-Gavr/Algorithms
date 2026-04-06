#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int val) : key(val), left(nullptr), right(nullptr) {
    }
};

class Tree {
   private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    Node* deleteNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        if (node->left == nullptr) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        }

        if (node->right == nullptr) {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        }

        // Two children: replace key with minimum from right subtree.
        if (node->right != nullptr) {
            Node* minNode = findMin(node->right);
            node->key = minNode->key;
            node->right = deleteMin(node->right);
            return node;
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteMin(Node* node) {
        if (node->left == nullptr) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        }
        node->left = deleteMin(node->left);
        return node;
    }

    void preorderLeft(Node* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->key);
        preorderLeft(node->left, result);
        preorderLeft(node->right, result);
    }

    bool isMirror(Node* tree1, Node* tree2) {
        if (tree1 == nullptr && tree2 == nullptr) {
            return true;
        }
        if (tree1 == nullptr || tree2 == nullptr) {
            return false;
        }

        return isMirror(tree1->left, tree2->right) && isMirror(tree1->right, tree2->left);
    }

   public:
    Tree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteRoot() {
        root = deleteNode(root);
    }

    bool isTrivial() {
        if (root == nullptr) {
            return false;
        }
        if ((root->left == nullptr) && (root->right == nullptr)) {
            return true;
        }
        return false;
    }

    vector<int> getPreorderLeft() {
        vector<int> result;
        preorderLeft(root, result);
        return result;
    }

    bool isMirrorOf(Tree& other) {
        return isMirror(this->root, other.root);
    }
};

int main() {
    ifstream input("tst.in");

    if (!input.is_open()) {
        cerr << "Can't open file tst.in" << endl;
        return 1;
    }

    string line;

    Tree tree1;

    Tree tree2;

    Tree* tree_dir = &tree1;

    while (getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        if (line[0] == '*') {
            tree_dir = &tree2;
            continue;
        }

        stringstream ss(line);
        int num;
        ss >> num;
        tree_dir->insert(num);
    }
    input.close();

    bool bothTrivial = false;
    bool result = false;
    if (tree1.isTrivial() == true && tree2.isTrivial() == true) {
        bothTrivial = true;
        result = true;
    }

    else {
        tree1.deleteRoot();
        tree2.deleteRoot();
        result = tree1.isMirrorOf(tree2);
    }

    ofstream output("tst.out");
    if (result) {
        output << "YES" << endl;
        if (bothTrivial == false) {
            vector<int> tree_out = tree1.getPreorderLeft();
            for (size_t i = 0; i < tree_out.size(); i++) {
                if (i > 0) {
                    output << " ";
                }
                output << tree_out[i];
            }
            output << endl;
            tree_out = tree2.getPreorderLeft();
            for (size_t i = 0; i < tree_out.size(); i++) {
                if (i > 0) {
                    output << " ";
                }
                output << tree_out[i];
            }
            output << endl;
        }
    } else {
        output << "NO" << endl;
    }

    output.close();

    return 0;
}