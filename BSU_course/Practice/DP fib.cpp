#include <iostream>
#include <vector>
using namespace std;

vector < long long > b;

long long fib(int x){ /// __int128
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    return fib(x - 1) + fib(x - 2);
}

long long fibm(int x){
    if (b[x] == -1)
        b[x] = fibm(x - 1) + fibm(x - 2);
    return b[x];
}

int main()
{
    int n;
    cin >> n;
    /// динамическое программирование (ДП)
    vector < long long > a(n + 1);
    a[0] = 0; a[1] = 1;
    for (int i = 2; i <= n; i++)
        a[i] = a[i - 1] + a[i - 2];
    cout << a[n] << endl;
    /// рекурсия с мемоизацией
    b.resize(n + 1, -1);
    b[0] = 0; b[1] = 1;
    cout << fibm(n) << endl;
    /// рекурсия
    cout << fib(n) << endl;
    return 0;
}
