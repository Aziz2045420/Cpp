#include <iostream>
#include <string>
using namespace std;

/*
Inspired by: replace.cpp

Task:
1. Implement
       string& replace_ref(string& str, char c, char d)
   so that it changes str and returns str by reference.
2. Read one word and two characters.
3. Store the function result in a reference:
       string& result = ...
4. Print both result and the original word.
5. If the word is not empty, set result[0] = '*'.
6. Print both result and the original word again.

Goal:
Show that changing result also changes the original string.
*/

string& replace_ref(string& str, char c, char d)
{
    // TODO: Replace every c by d.
    // TODO: Return str by reference.
    return str;
}

int main()
{
    string word;
    char c = '\0';
    char d = '\0';

    cout << "Word and chars: ";
    // TODO: Read word, c, and d.

    // TODO: Store the returned reference in result.

    // TODO: Print result and word on one line.

    // TODO: If word is not empty, set result[0] = '*'.

    // TODO: Print result and word again.

    return 0;
}
