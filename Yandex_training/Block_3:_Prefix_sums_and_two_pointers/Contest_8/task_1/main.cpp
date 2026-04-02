#include <fstream>
#include <map>
#include <cstdint>
#include <string>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    string commands;
    in >> commands;

    map<std::pair<int32_t, int32_t>, int32_t> visits;

    int32_t x = 0, y = 0;
    visits[{x, y}]++;

    for (char cmd : commands) {
        if (cmd == 'U') y++;
        else if (cmd == 'D') y--;
        else if (cmd == 'R') x++;
        else if (cmd == 'L') x--;

        visits[{x, y}]++;
    }

    int32_t count = 0;
    for (auto& entry : visits) {
        if (entry.second > 1) {
            count++;
        }
    }

    out << count << '\n';

    in.close();
    out.close();
    return 0;
}
