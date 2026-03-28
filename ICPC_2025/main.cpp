#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <set>
#include <cassert>
using namespace std;

constexpr int d = 1;

void solveE() {
    int n, k;
    cin >> n >> k;
    vector<string> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }


    for (int i = 0; i < n; i++) {
        string s = v[i];
        s[0] = 'a' + (s[0] - 'a' + d) % 26;
        for (int j = 1; j < k; j++) {
            s[j] = 'a' + (s[j - 1] - 'a' + s[j] - 'a' + d) % 26;
        }
        v[i] = s;
    }
    for (int i = 0; i < n; i++) {
        cout << v[i] << '\n';
    }
}

void solveD() {
    int n, k;
    cin >> n >> k;
    multiset<string> mp;
    for (int i = 0; i < 2 * n; i++) {
        string s;
        cin >> s;
        mp.insert(s);
    }

    //for (const auto& mst : mp) {
    set<pair<string, string>> pos_keyVals;
    for (const string& s_mst : mp) {
        string s = s_mst;
        for (int i = k - 1; i > 0; i--) {
            s[i] = 'a' + (-(s[i - 1] - 'a') + (s[i] - 'a') - d + 26) % 26;
        }
        s[0] = 'a' + (s[0] - 'a' - d + 26) % 26;

        if (mp.contains(s)) {
            pos_keyVals.insert(make_pair(s_mst, s));
        }
    }

    for (const auto& [k, v] : pos_keyVals) {
        cout << k << " " << v << '\n';
    }

    if (pos_keyVals.size() == n) {
        for (const auto& [k, v] : pos_keyVals) {
            cout << k << '\n';
        }
    }
    else {
        assert(false);
    }
    //}


}

int main()
{
    int t;
    string s;
    t = 1;
    cin >> s >> t;
    if (s == "ENCODE") {
        for (int i = 0; i < t; i++) {
            solveE();
        }
    }
    else {
        for (int i = 0; i < t; i++) {
            solveD();
        }
    }

    return 0;
}
