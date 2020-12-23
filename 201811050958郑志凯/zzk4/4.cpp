#include<iostream>
#include<ostream>
using namespace std;
int main()
{
    char a[50][50];
    int n, m, i, j, c, x;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }
    cin >> c;
    for (int x = 1; x <= c; x++)
    {
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (a[i][j] == 'X')
                {
                    if (a[i + 1][j] != 'P' && a[i + 1][j] != 'X')
                        a[i + 1][j] = 'N';
                    if (a[i - 1][j] != 'P' && a[i + 1][j] != 'X')
                        a[i - 1][j] = 'N';
                    if (a[i][j + 1] != 'P' && a[i + 1][j] != 'X')
                        a[i][j + 1] = 'N';
                    if (a[i][j - 1] != 'P' && a[i + 1][j] != 'X')
                        a[i][j - 1] = 'N';
                }
            }
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (a[i][j] == 'N')
                {
                    a[i][j] = 'X';
                }
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << a[i][j];
        }cout << endl;
    }
    return 0;
}