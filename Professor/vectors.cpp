#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<double> coord(3);         // Declaration of a vector with 3 elements
    coord[0] = 1.0;
    coord[1] = 1.5;
    coord[2] = 2.0;
    cout << coord[0] << ' ' << coord[1] << ' ' << coord[2] << ' ' << '\n';

    vector<double> coord2{1.0, 1.5, 2.0}; // Declaration with initialization
    cout << coord2[0] << ' ' << coord2[1] << ' ' << coord2[2] << ' ' << '\n';

    int no;
    cin >> no;
    vector<double> v(no);           // The initial size can be specified at runtime.

    coord.push_back(0.5);           // Vectors can be enlarged
 
    // The function size returns the length. 
    // It can be used e.g. in loops through the vector.
    for (size_t i = 0; i < coord.size(); i++)
        cout << coord[i] << ' ';
    cout << '\n';

    // Alternatively, the function ssize (C++20) can be used. 
    // It returns int instead of size_t.
    for (int i = 0; i < ssize(coord); i++)
        cout << coord[i] << ' ';
    cout << '\n';

    // The foreach-loop works with an iterator instead of the counter.
    for (const auto iter : coord)
        cout << iter << ' ';
    cout << '\n';
    // The variable iter is local in the loop. Therefore, changes have no effect 
    // on the vector. It should be declared with const. auto means that the data 
    // type is determined by the compiler.

    // If changes of iter should change the vector, use a reference without const.
    for (auto& iter : coord)
        iter = iter + 1.0;
    for (const auto iter : coord)
        cout << iter << ' ';
    cout << '\n';

    // Vectors can be sorted. #include <algorithm> is required. 
    // sort is part of the name space ranges, which is part of std.
    ranges::sort(coord);
    for (const auto iter : coord)
        cout << iter << ' ';
    cout << '\n';

    return 0;
}
