#include <iostream>
using namespace std;

void replace1(string& str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
}

string& replace2(string& str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
    return str;
}

const string& replace3(string& str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
    return str;
}

string replace4(string& str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
    return str;
}

string replace5(string str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
    return str;
}

string& replace6(string str, const char c, const char d)
{
    for (size_t i = 0; i < str.length(); i++)
        if (str[i] == c)
            str[i] = d;
    return str;
}

int main()
{
    string str = "THI";
    replace1(str, 'T', 'X');
    cout << "replace1: " << str << '\n';

    str = "THI";
    string& rep2 = replace2(str, 'T', 'X');
    cout << "replace2: " << rep2 << ' ' << str << '\n';

    // after replace2 rep2 is a reference to str
    rep2[0] = 'Y';
    cout << "          " << rep2 << ' ' << str << '\n';

    str = "THI";
    const string& rep3 = replace3(str, 'T', 'X');
    cout << "replace3: " << rep3 << ' ' << str << '\n';

    str = "THI";
    string rep4 = replace4(str, 'T', 'X');
    cout << "replace4: " << rep4 << ' ' << str << '\n';

    rep4[0] = 'Y';
    cout << "          " << rep4 << ' ' << str << '\n';

    str = "THI";
    string rep5 = replace5(str, 'T', 'X');
    cout << "replace5: " << rep5 << ' ' << str << '\n';

    str = "THI";
    string& rep6 = replace6(str, 'T', 'X');
    cout << "replace6: " << rep6 << ' ' << str << '\n';

    return 0;
}
