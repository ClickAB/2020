#include<iostream>
#include<stack>
#include<cmath>
using namespace std;
int getpriority(char op)
{
	int priority = 0, bracketPrioriy=0;
	if (op == '+' || op == '-')
	{
		priority = 1;
	}
	if (op == '*' || op == '/')
	{
		priority = 2;
	}	
	return priority;
}
float cal(float n1, float  n2, char op)
{
	float result = 0;
	switch (op)
	{
	case '*':
		result = n1 * n2;
		break;
	case '/':
		result = n1 / n2;
		break;
	case '+':
		result = n1 + n2;
		break;
	case '-':
		result = n1 - n2;
		break;  







	}
	return result;
}
float calculator(const string& c)
{
	string str = c;
	float n1, n2, num = 0;
	int priority=0, lastpriority = 0; //优先级，当前优先级
	int breakpriority = 0;
		char op;
	stack<float>nums;//存放计算数
	stack<char>ops;//存放操作数
	float result = 0;
	for (int i = 0; i <= c.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = float(str[i] - '0');
			nums.push(num);
		}
		else if (str[i] == ' ')
		{
			continue;
		}
		else if (str[i] == '(')
		{
			ops.push(str[i]);
			breakpriority = 10;
		}
		else if (str[i]==')')
		{
			while (ops.top() != '('&&!ops.empty())
			{
				op = ops.top();
				priority = getpriority(op);
				if (lastpriority >= priority)
				{
					n2 = nums.top();
					nums.pop();
					n1 = nums.top();
					n1 = cal(n1, n2, op);
					ops.pop();
					cout << n1 << endl;
					nums.push(n1);
				}
			}
			ops.pop();
				breakpriority = 0;
		}
		else {
			priority = getpriority(str[i]);
			if (breakpriority+priority<= lastpriority)
			{
				while (!ops.empty())
				{
					op = ops.top();
					lastpriority = getpriority(op);
					if (lastpriority >= priority)
					{
						ops.pop();
						n2 = nums.top();
						cout << n2 << endl;
						nums.pop();
						n1 = nums.top();
						cout << n1 << endl;
						nums.pop();
						n1 = cal(n1, n2, op);
						nums.push(n1);

					}
					else {
						break;//跳出循环
					}
				}
				ops.push(str[i]);
			}
			else
			{
				ops.push(str[i]);
			}
			lastpriority = priority;
		}


	}
	result = nums.top();
	return result;
}
int main()
{
	cout << " 5 * 8 - 3 / 2+8= " << calculator(" (3-2)/2") << endl;
	return 0;
}
