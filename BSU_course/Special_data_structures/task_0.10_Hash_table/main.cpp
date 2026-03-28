#include <cstdint>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

void insert(vector<int32_t>& table, const int32_t& x, const int32_t& c) {
    int32_t m = table.size();
    for (int32_t i = 0; i < m; ++i) {
        int32_t index = ((x % m) + c * i) % m;
        if (table[index] == -1) {
            table[index] = x;
            break;
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t m = 0;
    int32_t c = 0;
    int32_t n = 0;
    in >> m >> c >> n;

    set<int32_t> hash_set;

    vector<int32_t> table(m, -1);

    for (int32_t i = 0; i < n; ++i) {
        int32_t number = 0;
        in >> number;
        if (hash_set.find(number) != hash_set.end()) {
           continue;
        }
        insert(table, number, c);
        hash_set.insert(number);
    }

    for (int32_t i = 0; i < m; ++i) {
        out << table[i] << ' ';
    }

    in.close();
    out.close();
    return 0;
}
