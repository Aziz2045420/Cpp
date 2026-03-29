#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "Hello World";           // Declaration of a string,
                                        // "Hello World" is a char-array
    cout << s << '\n';                  // Output of the string s to the console

    cout << s[0] << '\n';               // Output of the character at index 0
    s[0] = 'X';                         // Change the character at index 0

    // Instead of the unsafe access with [] the function at can be used. This 
    // function throws a runtime error, if the index is not in the valid index range.
    cout << s.at(0) << '\n';

    cout << s.length() << '\n';         // Length of the string

    s[0] = 'H';                         // Change the character at index 0
    string t = s;                       // Assignment
    cout << t + " Again" << '\n';       // Concatenation

    cout << s.find("World") << '\n';    // Search and repace
    s.replace(s.find("World"), s.length(), "THI");
    cout << s << '\n';
    return 0;
}
