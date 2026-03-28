#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bool prime(int x){
    if (x < 2)
        return false;
    for (long long i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;
}

int main()
{
    int n, ans = 0;
    cin >> n;
    // n = 10'000'000;
    // vector < bool > a(n + 1, 1);
    bitset < 10000001 > a;
    a[0] = a[1] = 1;
    /// O(n log log n)  M(n)
    for (long long i = 2; i * i <= n; i++)
        if (a[i] == 0)
            for (int j = i * i; j <= n; j += i)
                a[j] = 1;
    for (int i = 0; i <= n; i++)
        ans += (1 - a[i]);
    cout << ans;
    return 0;
}
