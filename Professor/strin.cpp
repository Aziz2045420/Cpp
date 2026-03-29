#include <iostream>
using namespace std;

int main( )
{
    string line;
    char c;

    cout << "Input:  ";

    while (cin.get(c) && c != '\n')
        line = line + c;

    cout << "Output: " << line << '\n';

    cout << "Input:  ";
    getline(cin, line);
    cout << "Output: " << line << '\n';

    return 0;
}
