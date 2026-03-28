#include <cstdint>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

class DSU {
   public:
    explicit DSU(const int32_t n) {
        parent.resize(n);
        size.resize(n, 1);
        components = n;

        for (int32_t i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int32_t FindParent(const int32_t x) {
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

    int32_t n = 0;
    int32_t m = 0;
    int32_t q = 0;
    in >> n >> m >> q;

    DSU dsu(n);

    vector<tuple<int32_t, int32_t, bool>> roads;
    // true - the road survives
    roads.reserve(m);
    vector<int32_t> dest(q, 0);

    for (int32_t i = 0; i < m; ++i) {
        int32_t u = 0;
        int32_t v = 0;
        in >> u >> v;

        --u;
        --v;

        roads.push_back({u, v, true});
    }

    for (int32_t i = 0; i < q; ++i) {
        int32_t num = 0;
        in >> num;

        --num;

        dest[i] = num;
        get<2>(roads[num]) = false;
    }

    for (int32_t i = 0; i < m; ++i) {
        if (get<2>(roads[i]) == true) {
            dsu.Union(get<0>(roads[i]), get<1>(roads[i]));
        }
    }

    vector<short> result(q, 0);
    for (int32_t i = q - 1; i >= 0; --i) {
        result[i] = ((dsu.GetComponents() == 1) ? 1 : 0);
        int32_t road_num = dest[i];
        dsu.Union(get<0>(roads[road_num]), get<1>(roads[road_num]));
    }

    // for (int32_t i = 0; i < m; ++i) {
    //     out << "Дорога #" << i + 1 << ": "
    //          << roads[i].first.first + 1 << " - "
    //          << roads[i].first.second + 1;
    //
    //     if (roads[i].second) {
    //         out << " [СОХРАНИЛАСЬ]" << endl;
    //     } else {
    //         out << " [РАЗРУШЕНА]" << endl;
    //     }
    // }

    for (int32_t i = 0; i < q; ++i) {
        out << result[i];
    }

    in.close();
    out.close();
    return 0;
}
