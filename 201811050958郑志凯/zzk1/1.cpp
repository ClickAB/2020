#include <iostream>
#include <ostream>
using namespace std;
int fun(int a, int b);
int fun1(int& a, int& b, int& c);
int fun2(int* a, int* b, int* c);
int main()
{
    int a, b, c;
    cout << "∵ 分别输入a、b:" << endl;
    cin >> a >> b;
    c = fun(a, b);
    cout << "∴ c = " << c << endl;
    return 0;
}

int fun(int a, int b)
{
    return (a % 10 * 1000 + b % 10 * 100 + a / 10 * 10 + b / 10);
}

int fun1(int& a, int& b, int& c)
{
    c = a % 10 * 1000 + b % 10 * 100 + a / 10 * 10 + b / 10;
    return 0;
}

int fun2(int* a, int* b, int* c)
{
    *c = *a % 10 * 1000 + *b % 10 * 100 + *a / 10 * 10 + *b / 10;
    return 0;
}