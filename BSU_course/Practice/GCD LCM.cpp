#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    int a, b, NOD, NOK, a1, b1;
    cin >> a >> b; a1 = a; b1 = b;
    /*
    while (a != b)
        if (a > b)
            a -= b;
        else
            b -= a;
    NOD = a;
    */
    /*
    while (a > 0 && b > 0)
        if (a > b)
            a %= b;
        else
            b %= a;
    NOD = a + b;
    NOK = a1 / NOD * b1;
    cout << NOD << " " << NOK;
    */
    // cout << __gcd(a, b) << " " << a / __gcd(a, b) * b;
    cout << gcd(a, b) << " " << lcm(a, b);
    return 0;
}
