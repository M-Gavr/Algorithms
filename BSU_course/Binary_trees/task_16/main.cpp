#include <fstream>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct Node {
    int32_t key;
    Node* left;
    Node* right;
    Node* parent;

    int32_t down_len;
    int64_t down_cnt;

    int32_t up_len;
    int64_t up_cnt;

    int64_t answer;

    explicit Node(int32_t key)
        : key(key)
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
        , down_len(0)
        , down_cnt(1)
        , up_len(-1)
        , up_cnt(0)
        , answer(0) {
    }
};

class BinarySearchTree {
   private:
    Node* root_ = nullptr;
    int32_t node_count_ = 0;
    int32_t diameter_ = 0;

   public:
    ~BinarySearchTree() {
        Clear();
    }

    Node* GetRoot() const {
        return root_;
    }

    int GetNodeCount() const {
        return node_count_;
    }

    void Insert(int32_t x) {
        if (root_ == nullptr) {
            root_ = new Node(x);
            node_count_ = 1;
            return;
        }

        Node* cur = root_;
        Node* parent = nullptr;

        while (cur != nullptr) {
            parent = cur;
            if (x < cur->key) {
                cur = cur->left;
            } else if (x > cur->key) {
                cur = cur->right;
            } else {
                return;
            }
        }

        Node* v = new Node(x);
        v->parent = parent;
        if (x < parent->key) {
            parent->left = v;
        } else {
            parent->right = v;
        }
        ++node_count_;
    }

    void RemoveRootByRightDeletion() {
        if (root_ == nullptr) {
            return;
        } else {
            RemoveByKey(root_->key);
        }
    }

    void Solve() {
        if (root_ == nullptr) {
            return;
        }

        ComputeDownAndDiameter();

        if (node_count_ == 1) {
            root_->answer = 1;
            return;
        }

        ComputeUp();
        ComputeAnswers();
    }

    void PrintPreorder(ofstream& out) const {
        if (root_ == nullptr) {
            return;
        }

        stack<Node*> st;
        st.push(root_);

        while (!st.empty()) {
            const Node* v = st.top();
            st.pop();

            out << v->key << ' ' << v->answer << '\n';

            if (v->right != nullptr) {
                st.push(v->right);
            }
            if (v->left != nullptr) {
                st.push(v->left);
            }
        }
    }

   private:
    void Clear() {
        if (root_ == nullptr) {
            return;
        }

        stack<Node*> st;
        st.push(root_);

        while (!st.empty()) {
            Node* v = st.top();
            st.pop();

            if (v->left != nullptr) {
                st.push(v->left);
            }
            if (v->right != nullptr) {
                st.push(v->right);
            }
            delete v;
        }

        root_ = nullptr;
        node_count_ = 0;
    }

    void RemoveByKey(const int32_t key) {
        Node* v = root_;

        while (v != nullptr && v->key != key) {
            if (key < v->key) {
                v = v->left;
            } else {
                v = v->right;
            }
        }

        if (v == nullptr) {
            return;
        }
        if (v->left != nullptr && v->right != nullptr) {
            Node* s = v->right;
            while (s->left != nullptr) {
                s = s->left;
            }
            v->key = s->key;
            v = s;
        }

        Node* child = (v->left != nullptr ? v->left : v->right);

        if (child != nullptr) {
            child->parent = v->parent;
        }

        if (v->parent == nullptr) {
            root_ = child;
        } else if (v->parent->left == v) {
            v->parent->left = child;
        } else {
            v->parent->right = child;
        }

        delete v;
        --node_count_;
    }

    void ComputeDownAndDiameter() {
        diameter_ = 0;

        stack<pair<Node*, bool>> st;
        st.push({root_, false});

        while (!st.empty()) {
            auto [v, used] = st.top();
            st.pop();

            if (v == nullptr) {
                continue;
            }

            if (!used) {
                st.push({v, true});
                st.push({v->right, false});
                st.push({v->left, false});
            } else {
                int32_t left_len = -1;
                int32_t right_len = -1;
                int64_t left_cnt = 0;
                int64_t right_cnt = 0;

                if (v->left != nullptr) {
                    left_len = v->left->down_len;
                    left_cnt = v->left->down_cnt;
                }
                if (v->right != nullptr) {
                    right_len = v->right->down_len;
                    right_cnt = v->right->down_cnt;
                }

                v->down_len = max(left_len, right_len) + 1;

                if (left_len == -1 && right_len == -1) {
                    v->down_cnt = 1;
                } else if (left_len > right_len) {
                    v->down_cnt = left_cnt;
                } else if (right_len > left_len) {
                    v->down_cnt = right_cnt;
                } else {
                    v->down_cnt = left_cnt + right_cnt;
                }

                int32_t through_v = left_len + right_len + 2;
                if (through_v > diameter_) {
                    diameter_ = through_v;
                }
            }
        }
    }

    void RelaxCandidate(int32_t cand_len, int64_t cand_cnt, int32_t& best_len, int64_t& best_cnt) {
        if (cand_len > best_len) {
            best_len = cand_len;
            best_cnt = cand_cnt;
        } else if (cand_len == best_len) {
            best_cnt += cand_cnt;
        }
    }

    void ComputeChildUp(Node* parent, Node* child, Node* sibling) {
        int32_t best_len = 1;
        int64_t best_cnt = 1;

        if (parent->up_len >= 0) {
            RelaxCandidate(1 + parent->up_len, parent->up_cnt, best_len, best_cnt);
        }

        if (sibling != nullptr) {
            RelaxCandidate(2 + sibling->down_len, sibling->down_cnt, best_len, best_cnt);
        }

        child->up_len = best_len;
        child->up_cnt = best_cnt;
    }

    void ComputeUp() {
        root_->up_len = -1;
        root_->up_cnt = 0;

        stack<Node*> st;
        st.push(root_);

        while (!st.empty()) {
            Node* v = st.top();
            st.pop();
            if (v->left != nullptr) {
                ComputeChildUp(v, v->left, v->right);
                st.push(v->left);
            }
            if (v->right != nullptr) {
                ComputeChildUp(v, v->right, v->left);
                st.push(v->right);
            }
        }
    }

    void ComputeAnswers() {
        stack<Node*> st;
        st.push(root_);

        while (!st.empty()) {
            Node* v = st.top();
            st.pop();

            vector<pair<int32_t, int64_t>> rays;
            rays.push_back({0, 1});

            if (v->left != nullptr) {
                rays.push_back({1 + v->left->down_len, v->left->down_cnt});
            }
            if (v->right != nullptr) {
                rays.push_back({1 + v->right->down_len, v->right->down_cnt});
            }
            if (v->up_len >= 0) {
                rays.push_back({v->up_len, v->up_cnt});
            }

            int64_t ways = 0;
            for (size_t i = 0; i < rays.size(); ++i) {
                for (size_t j = i + 1; j < rays.size(); ++j) {
                    if (rays[i].first + rays[j].first == diameter_) {
                        ways += rays[i].second * rays[j].second;
                    }
                }
            }

            v->answer = ways;

            if (v->right != nullptr) {
                st.push(v->right);
            }
            if (v->left != nullptr) {
                st.push(v->left);
            }
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    BinarySearchTree tree;
    int32_t x = 0;

    while (in >> x) {
        tree.Insert(x);
    }

    tree.RemoveRootByRightDeletion();
    tree.Solve();
    tree.PrintPreorder(out);

    return 0;
}
