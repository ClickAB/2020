#include<iostream>
#include<ostream>
using namespace std;
int main()
{
	int m, n, attend, num, temp = 1;
	int monkey[50];
	cout << "∵猴子的数量 m 为:" << endl;
	cin >> m;
	cout << "∵数到退场的数 n 为:" << endl;
	cin >> n;
	attend = m;
	for (num = 0; num < m; num++)
		monkey[num] = num + 1;
	num = 0;
	while (attend > 1)
	{
		if (monkey[num] > 0)
		{
			if (temp != n)
			{
				temp++;
				num = (num + 1) % m;
			}
			else
			{
				monkey[num] = 0;
				temp = 1;
				attend--;
				num = (num + 1) % m;
			}
		}
		else
		{
			num = (num + 1) % m;
		}
	}
	for (num = 0; num < m; num++)
	{
		if (monkey[num] > 0)
			cout << "∴猴王的编号为:" << monkey[num] << endl;
	}
	return 0;
}