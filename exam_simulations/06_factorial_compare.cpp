#include <iostream>
using namespace std;

/*
Inspired by: call.cpp

Task:
1. Implement fac_value(int n):
   It returns n! and must not change the variable in main.
2. Implement fac_ref(int& n):
   It returns n! and then sets n to 0.
3. Read one integer n.
4. Create a copy m = n.
5. Print:
   fac_value: <result> n=<n>
   fac_ref: <result> m=<m>

Assume n >= 0.
*/

int fac_value(int n)
{
    // TODO: Compute the factorial and return it.
    return 0;
}

int fac_ref(int& n)
{
    // TODO: Compute the factorial.
    // TODO: Set n to 0 before returning.
    return 0;
}

int main()
{
    int n = 0;

    cout << "n: ";
    // TODO: Read n.

    int m = n;

    // TODO: Call fac_value and print the result together with n.

    // TODO: Call fac_ref and print the result together with m.

    return 0;
}
