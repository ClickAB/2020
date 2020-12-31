#include<iostream>
using namespace std;
int main()
{
	int N, M, C;
	char  a[50][50];
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> a[i][j];
		}

	}


cin >> C;
for (int i = 0; i < C; i++)
{
	for (int j = 1; j <= M; j++)
	{
		for (int k = 1; k <= N; k++)
		{
			if (a[j][k] == 'X' && a[j - 1][k] != 'P' )
			{
				a[j - 1][k] = 'Y';

			}
			if (a[j][k] == 'X' && a[j + 1][k] != 'P')
			{
				a[j + 1][k] = 'Y';

			}
			if (a[j][k] == 'X' && a[j][k - 1] != 'P' )
			{
				a[j][k - 1] = 'Y';

			}
			if (a[j][k] == 'X' && a[j][k + 1] != 'P' )
			{
				a[j][k + 1] = 'Y';

			}

		}

	}
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (a[i][j] == 'Y')
			{
				a[i][j] = 'X';
			}
		}

	}
}
for (int i = 1; i <= M; i++)
{
	for (int j = 1; j <= N; j++)
	{
		cout << a[i][j];
	}
	cout << endl;

}

}



