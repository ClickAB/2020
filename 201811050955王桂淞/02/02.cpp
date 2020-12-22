#include<iostream>
using namespace std;

int MonkyKing(int a[], int m,int n)
{
	int i, j, k = -1;
	for (int i = 0; i < m; i++)
	{
		a[i] = 1;//初始化猴子数m个
	}
	
	for (i = 1; i<= m; i++)//开始绕圈循环
	{
		j = 1;//数到第J个猴子
		while (j <=n)
		{
			k = (k + 1) % m;//在所有猴子中进行循环
			if (a[k] == 1)//找到还在圈中的猴子
			{
				j++;
			}
		}
		a[k] = 0;//让他出圈
		
	}
	return k+1;//猴子之王的序号
}
typedef struct node {
	int data;
	struct node* next;

}monkey;
int Monky(int m, int n)
{
	monkey* head, * p, * s, * q;
	int i, total;
	head = new monkey;
	p = head;
	p->data = 1;
	p->next = p;
	for (int i = 2; i <= m; i++)
	{
		s = new monkey;
		s->data = i;
		s->next = p->next;
		p->next = s;
		p = p->next;

	}
	p = head;
	q = head;
	total = m;
	while (total != 1)
	{
		for (i = 1; i < n; i++)
		{
			p = p->next;
		}
		while (q->next != p)
		{
			q = q->next;	
		}
		q->next = p->next;
		s = p;
		p = p->next;
		delete(s);
		total--;
	}
	int king = p->data;
	return king;

}
int main()
{
	int m, n, a[100];//猴子个数最大100
	cin >> m >> n;
	int king,king1;
	king = MonkyKing(a,m,n);
	cout << "猴子之王是" << king << endl;
	king1 = Monky(m, n);
	cout << "猴子之王是" << king1<< endl;

}