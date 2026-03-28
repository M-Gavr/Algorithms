#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Node {
public:
    Node(): value_(-1), left_(-1), right_(-1) {
    }

    explicit Node(const int32_t val): value_(val), left_(-1), right_(-1) {
    }

    ~Node() = default;

    int32_t value() const { return value_; }
    int32_t left() const { return left_; }
    int32_t right() const { return right_; }

    void set_value(const int32_t val) { value_ = val; }
    void set_left(const int32_t node) { left_ = node; }
    void set_right(const int32_t node) { right_ = node; }

private:
    int32_t value_;
    int32_t left_;
    int32_t right_;
};

bool IsBST(const vector<Node>& nodes) {
    if (nodes.empty()) return true;

    queue<pair<int, pair<int64_t, int64_t>>> q;

    q.push({0, {numeric_limits<int64_t>::min(),
                numeric_limits<int64_t>::max()}});

    while (!q.empty()) {
        int32_t index = q.front().first;
        int64_t min_val = q.front().second.first;
        int64_t max_val = q.front().second.second;
        q.pop();

        const Node& current = nodes[index];

        if (current.value() < min_val || current.value() >= max_val) {
            return false;
        }

        if (current.left() != -1) {
            q.push({current.left(), {min_val, current.value()}});
        }

        if (current.right() != -1) {
            q.push({current.right(), {current.value(), max_val}});
        }
    }

    return true;
}

int main() {
    ifstream in("bst.in");
    ofstream out("bst.out");

    int32_t n = 0, m = 0;
    in >> n >> m;
    vector<Node> nodes(n);
    nodes[0].set_value(m);

    int32_t val = 0, par = -1;
    char son;
    for (int32_t i = 1; i < n; ++i) {
        in >> val >> par >> son;
        nodes[i].set_value(val);
        if (son == 'L') {
            nodes[par - 1].set_left(i);
        } else {
            nodes[par - 1].set_right(i);
        }
    }

    bool answer = IsBST(nodes);

    out << (answer ? "YES" : "NO") << endl;

    /*
    for (int32_t i = 0; i < n; ++i) {
        out << "Node " << i << ": value=" << nodes[i].value()
                  << ", parent=" << nodes[i].parent()
                  << ", left=" << nodes[i].left()
                  << ", right=" << nodes[i].right() << std::endl;
    }
    */

    in.close();
    out.close();
    return 0;
}
