#include <iostream>
using namespace std;
struct Monkey
{
    int num;
    struct Monkey* next;
};

int main()
{
    int m, n, i, j, king;
    Monkey* head, * p1, * p2;
    cout << "∵猴子的数量 m 为:" << endl;
    cin >> m;
    cout << "∵数到退场的数 n 为:" << endl;
    cin >> n;
    if (n == 1)
    {
        king = m;
    }
    else
    {
        p1 = p2 = new Monkey;
        head = p1;
        p1->num = 1;
        for (i = 1; i < m; i++)
        {
            p1 = new Monkey;
            p1->num = i + 1;
            p2->next = p1;
            p2 = p1;
        }
        p2->next = head;
        p1 = head;
        for (i = 1; i < m; i++)
        {
            for (j = 1; j < n - 1; j++)
                p1 = p1->next;
            p2 = p1->next;
            p1->next = p2->next;
            p1 = p2->next;
            delete p2;
        }
        king = p1->num;
        delete p1;
    }
    cout << "∴猴王的编号为:" << king << endl;
    return 0;
}