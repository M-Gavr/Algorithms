#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int32_t n = 0;
    cin >> n;

    vector<int32_t> mosquitoes(n + 1);
    for (size_t i = 1; i <= n; i++) {
        cin >> mosquitoes[i];
    }

    vector<int32_t> results(n + 1, -1);
    vector<int32_t> prev(n + 1, 0);

    if (n >= 1) {
        results[1] = mosquitoes[1];
    }
    if (n >= 2) {
        results[2] = -1;
    }
    if (n >= 3) {
        results[3] = results[1] + mosquitoes[3];
        prev[3] = 1;
    }
    if (n >= 4) {
        results[4] = results[1] + mosquitoes[4];
        prev[4] = 1;
    }

    for (int32_t i = 1; i <= n; ++i) {
        if (results[i] == -1) {
            continue;
        }
        if (i + 2 <= n) {
            int32_t result = results[i] + mosquitoes[i + 2];
            if (result > results[i + 2]) {
                results[i + 2] = result;
                prev[i + 2] = i;
            }
        }
        if (i + 3 <= n) {
            int32_t result = results[i] + mosquitoes[i + 3];
            if (result > results[i + 3]) {
                results[i + 3] = result;
                prev[i + 3] = i;
            }
        }
    }

    if (results[n] == -1) {
        cout << -1 << endl;
        return 0;
    }

    vector<int32_t> path;
    for (int32_t cur = n; cur != 0; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << results[n] << endl;

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 == path.size() ? '\n' : ' ');
    }

    return 0;
}
