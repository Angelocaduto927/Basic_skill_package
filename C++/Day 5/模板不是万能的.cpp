#include <iostream>
using namespace std;

template <class T>
T func(T a, T b)
{
    a = b;
    return a;
}
int main()
{
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {2, 3, 4, 5};
    int *a = func(arr1, arr2);
    cout << *a << endl;
}
