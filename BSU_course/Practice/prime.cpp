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
    cout << prime(n);
    return 0;
}
