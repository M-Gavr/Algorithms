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
    int n, i = 2;
    cin >> n;
    while (i * i <= n)
        if (n % i == 0){
            cout << i << " ";
            n /= i;
        } else
            i++;
    if (n > 1)
        cout << n;
    return 0;
}
