#include <iostream>
#include <ostream>
#include <algorithm>
using namespace std;
struct node
{
    int yuwen, shuxue, yingyu;
    int num, sum;
}student[3000];
int cmp(node x, node y)
{
    if (x.sum != y.sum) return x.sum > y.sum;
    if (x.yuwen != y.yuwen) return x.yuwen > y.yuwen;
    if (x.num != y.num) return x.num < y.num;
}
int main()
{
    int i, j, n, m;
    cout << "输入学生个数n，换行后分别输入各个学生的语数英成绩:" << endl;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> student[i].yuwen >> student[i].shuxue >> student[i].yingyu;
        student[i].num = i + 1;
        student[i].sum = student[i].yuwen + student[i].shuxue + student[i].yingyu;
    }
    sort(student, student + n, cmp);
    cout << "前5名学生的学号和总分:" << endl;
    for (i = 0; i < 5; i++)
        cout << student[i].num << " " << student[i].sum << endl;
    return 0;
}