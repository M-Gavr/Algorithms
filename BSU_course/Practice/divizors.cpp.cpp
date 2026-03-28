#include <iostream>
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
    int n;
    cin >> n;
    long long  i;
    for (i = 1; i * i < n; i++)
        if (n % i == 0)
            cout << i << " " << n / i << " ";
    if (i * i == n)
        cout << i;
    return 0;
}
