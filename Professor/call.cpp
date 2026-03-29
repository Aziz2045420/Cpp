#include <iostream>
using namespace std;

// Call-by-value
int fac1(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    // n is local in the function
    n = 0;
    return res;
}

int fac2(const int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    //n = 0; // Error: The parameter is const.
    return res;
}

// Call-by-reference
int fac3(int& n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    n = 0; // The global variable n is changed.
    return res;
}

int fac4(const int& n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    //n = 0; // Error: The parameter is const.
    return res;
}

void fac5(int n, int& res)
{
    res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
}

int main()
{
    int n = 3;

    cout << "fac1: " << fac1(n) << " is the factorial of " << n << '\n';
    cout << "fac2: " << fac2(n) << " is the factorial of " << n << '\n';
    cout << "fac3: " << fac3(n) << " is the factorial of " << n << '\n';
    // Error: It is not possible to create a reference to 3.
    //cout << "fac3: " << fac3(3) << " is the factorial of " << "3" << '\n';
    n = 3;
    cout << "fac4: " << fac4(n) << " is the factorial of " << n << '\n';
    cout << "fac4: " << fac4(3) << " is the factorial of " << "3" << '\n';
    int res5 = 1;
    fac5(n, res5);
    cout << "fac5: " << res5 << " is the factorial of " << n << '\n' << '\n';

    return 0;
}
