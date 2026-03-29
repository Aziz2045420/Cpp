#include <iostream>
using namespace std;

int main()
{
    int number1;
    int number2;

    // Read two integers
    cout << "Enter two integers: ";
    cin >> number1 >> number2;

    // Calculate the sum of both numbers
    int sum = number1 + number2;

    // Display the result on the screen
    cout << "sum=" << sum << '\n';

    return 0;
}
