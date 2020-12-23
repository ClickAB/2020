#include <stdio.h>
int fun(int a, int b) 
{
	int c = 1000 * (a % 10) + (b / 10) + 10 * (a / 10) + 100 * (b % 10);
	return c;
}
int main() 
{
	int a;
	int b;
	printf("请输入第一个两位数a:");
	scanf_s("%d", &a);
	printf("请输入第二个两位数b:");
	scanf_s("%d", &b);
	int c = fun(a, b);
	printf("结果为:%d", c);
	return 0;
}
int  fun1(int& a, int& b, int& c)
{
	if ((a > 100 || a < 10) || (b > 100 || b < 10))
	{
		return 0;
	}
	c = a % 10 * 1000 + b % 10 * 100 + a / 10 * 10 + b / 10;
	return 0;
}
int  fun2(int* a, int* b, int* c)
{
	if ((*a > 100 || *a < 10) || (*b > 100 || *b < 10))
	{
		return 0;
	}
	*c = *a % 10 * 1000 + *b % 10 * 100 + *a / 10 * 10 + *b / 10;
	return 0;
}