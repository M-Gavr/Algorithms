#include <iostream>
#include <cstdint>

using namespace std;

int main() {

    int32_t n = 0;
    cin >> n;
    cout << (n & 1 ? "Masha" : "Anya") << '\n';

    return 0;
}