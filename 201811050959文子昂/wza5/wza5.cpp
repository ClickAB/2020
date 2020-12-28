#include <Windows.h>
#include <iostream>
#include <vector>
#include <String>
#include <stack>
#include <cstdlib>
using namespace std;
int main()
{
	string str_in;
	vector<string> houzhuibiaodashi;
	stack<char> CStack;
	string temp;
	stack <float> NStack;
	while (1)
	{
		houzhuibiaodashi.clear();
		while (!CStack.empty())	
		{
			CStack.pop();
		}
		temp = "";
		while (!NStack.empty())
		{
			NStack.pop();
		}
		cout << "请输入多项式：";
		cin >> str_in;
		for (int i = 0; i < str_in.length(); i++)
		{
			if (str_in[i] == '(')		
			{
				CStack.push(str_in[i]);				
			}
			else if (str_in[i] >= '0' && str_in[i] <= '9')			
			{
				temp = str_in[i];
				while (str_in[i + 1] >= '0' && str_in[i + 1] <= '9' && i < str_in.length())
				{
					temp += str_in[++i];
				}
				houzhuibiaodashi.push_back(temp);			
			}
			else if (
				(str_in[i] == '-'
					&& (i > 0 && !(str_in[i - 1] >= '0' && str_in[i - 1] <= '9' && str_in[i + 1] >= '0' && str_in[i + 1] <= '9'))
					&& (i > 0 && !(str_in[i - 1] == ')' && str_in[i + 1] >= '0' && str_in[i + 1] <= '9'))	
					&& (i > 0 && !(str_in[i + 1] == ')' && str_in[i - 1] >= '0' && str_in[i - 1] <= '9')))	
				|| (str_in[i] == '-' && i == 0)										
				)//
			{
				temp = "";

				temp = str_in[i++];
				while (str_in[i] >= '0' && str_in[i] <= '9' && i < str_in.length())
				{
					temp += str_in[i];
					i++;
				}

				houzhuibiaodashi.push_back(temp);				

				i--;		

			}
			else if (str_in[i] == '-' && str_in[i + 1] == '(' && (i == 0))	
			{


				houzhuibiaodashi.push_back("-1");			


				while (!CStack.empty() && (CStack.top() == '*' || CStack.top() == '/'))
				{
					temp = "";
					temp = CStack.top();
					CStack.pop();
					houzhuibiaodashi.push_back(temp);
				}
				CStack.push('*');
			}



			else if (str_in[i] == ')')
			{
				temp = "";
				while (!CStack.empty() && CStack.top() != '(')
				{
					temp = "";
					temp = CStack.top();
					houzhuibiaodashi.push_back(temp);
					CStack.pop();
				}
				CStack.pop();			
			}

			else if (str_in[i] == '+' || str_in[i] == '-' || str_in[i] == '*' || str_in[i] == '/')
			{
				temp = "";
				if (str_in[i] == '+' || str_in[i] == '-')
				{
					while (!CStack.empty() && (CStack.top() == '+' || CStack.top() == '-' || CStack.top() == '*' || CStack.top() == '/'))
					{
						temp = "";
						temp = CStack.top();
						CStack.pop();
						houzhuibiaodashi.push_back(temp);
					}
					CStack.push(str_in[i]);
				}
				else if (str_in[i] == '*' || str_in[i] == '/')
				{
					while (!CStack.empty() && (CStack.top() == '*' || CStack.top() == '/'))
					{
						temp = "";
						temp = CStack.top();
						CStack.pop();
						houzhuibiaodashi.push_back(temp);
					}
					CStack.push(str_in[i]);
				}

			}




		}


		while (!CStack.empty())
		{
			temp = CStack.top();
			CStack.pop();
			houzhuibiaodashi.push_back(temp);
		}
		int i = 0;
		float num1, num2;
		while (!houzhuibiaodashi.empty() && i < houzhuibiaodashi.size())
		{
			if (houzhuibiaodashi[i] == "+")
			{
				num1 = NStack.top();
				NStack.pop();
				num2 = NStack.top();
				NStack.pop();
				NStack.push(num1 + num2);
			}
			else if (houzhuibiaodashi[i] == "-")
			{
				if (i == 0)			
				{
					char* data = new char[houzhuibiaodashi.size()];
					for (int t = 1; t < houzhuibiaodashi[i].size(); t++)
					{
						data[t] = houzhuibiaodashi[i][t];
					}

					NStack.push(0 - atoi(data));
				}
				else
				{
					num1 = NStack.top();
					NStack.pop();
					num2 = NStack.top();
					NStack.pop();
					NStack.push(num2 - num1);
				}
			}
			else if (houzhuibiaodashi[i] == "*")
			{
				num1 = NStack.top();
				NStack.pop();
				num2 = NStack.top();
				NStack.pop();
				NStack.push(num1 * num2);
			}
			else if (houzhuibiaodashi[i] == "/")
			{
				num1 = NStack.top();
				NStack.pop();
				num2 = NStack.top();
				NStack.pop();
				NStack.push(num2 / num1);
			}
			else
			{
				char* data = new char[houzhuibiaodashi.size()];
				for (int t = 0; t < houzhuibiaodashi[i].size(); t++)
				{
					data[t] = houzhuibiaodashi[i][t];
				}

				NStack.push(atoi(data));
			}

			i++;
		}
		cout << "等式的值为" << NStack.top() << endl;
	}
	system("pause");
}