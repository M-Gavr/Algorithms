#include <fstream>
#include <set>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::set<int32_t> tree;
    int32_t key = 0;
    int64_t sum = 0;

    while(in >> key) {
        tree.insert(key);
    }

    for (int32_t value : tree) {
        sum = sum + value;
    }

    out << sum << std::endl;

    in.close();
    out.close();
    return 0;
}
