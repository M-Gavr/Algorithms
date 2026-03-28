#include <iostream>
using namespace std;

unsigned long long P(int x){
    if (x == 1)
        return 1;
    return 2 * P(x - 1) + 1;
}

void H(int n, int a, int b){
    if (n == 0)
        return;
    H(n - 1, a, 6 - a - b);
    cout << a << " -> " << b << endl;
    H(n - 1, 6 - a - b, b);
}

int main()
{
    int n;
    cin >> n;
    H(n, 1, 2);
    cout << P(n); ///  / 60  / 60 / 24 / 366;
    // cout << ((unsigned long long)1LL << n) - 1;
    return 0;
}
