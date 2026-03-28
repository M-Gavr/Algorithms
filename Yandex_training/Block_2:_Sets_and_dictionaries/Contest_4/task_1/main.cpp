#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    in >> n;

    vector<string> names(n);
    map<string, int32_t> totalPoints;

    for (int32_t i = 0; i < n; i++) {
        in >> names[i];
        totalPoints[names[i]] = 0;
    }

    int32_t m = 0;
    in >> m;

    int32_t prev_1 = 0, prev_2 = 0;

    for (int32_t i = 0; i < m; i++) {
        int32_t a, b;
        string name;
        char dots;

        in >> a >> dots >> b >> name;

        int32_t diff_1 = a - prev_1;
        int32_t diff_2 = b - prev_2;

        totalPoints[name] += diff_1 + diff_2;

        prev_1 = a;
        prev_2 = b;
    }

    string winner;
    int32_t maxPoints = -1;

    for (const auto& player : totalPoints) {
        if (player.second > maxPoints) {
            maxPoints = player.second;
            winner = player.first;
        }
    }

    out << winner << " " << maxPoints << '\n';

    in.close();
    out.close();
    return 0;
}
