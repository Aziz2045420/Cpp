#include <iostream>
using namespace std;

int gcd(int a, int b) {
    // handle negative numbers
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    // avoid infinite loop if one is 0
    if (a == 0) return b;
    if (b == 0) return a;

    // subtraction algorithm
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }

    return a; // or b (they are equal)
}

int main() {
    int number1, number2;

    cout << "Enter two integers: ";
    cin >> number1 >> number2;

    int result = gcd(number1, number2);

    cout << "gcd = " << result << endl;

    return 0;
}