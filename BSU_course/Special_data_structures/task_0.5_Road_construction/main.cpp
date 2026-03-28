#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

class DSU {
   public:
    DSU(int32_t n) {
        parent.resize(n);
        size.resize(n, 1);
        components = n;

        for (int32_t i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int32_t FindParent(int32_t x) {
        if (x == parent[x]) {
            return x;
        }
        parent[x] = FindParent(parent[x]);
        return parent[x];
    }

    void Union(int32_t x, int32_t y) {
        int32_t rootX = FindParent(x);
        int32_t rootY = FindParent(y);

        if (rootX == rootY) {
            return;
        }

        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }

        components--;
    }

    int32_t GetComponents() const {
        return components;
    }

   private:
    vector<int32_t> parent;
    vector<int32_t> size;
    int32_t components;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n, q;
    in >> n >> q;

    DSU dsu(n);

    for (int32_t i = 0; i < q; ++i) {
        int32_t u, v;
        in >> u >> v;

        --u; --v;

        dsu.Union(u, v);
        out << dsu.GetComponents() << '\n';
    }

    return 0;
}
