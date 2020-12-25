#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
int Priority(char c);
double Float(string s);
string Postfix(const string& infix);
double Result(const string& postfix);
int main() 
{
    string str_in;
    cout << "请输入多项式：";
    cin >> str_in;
    string postfix·notation = Postfix(str_in);
    double result = Result(postfix·notation);
    cout << "结果为: " << result << endl;
}

int Priority(char op)
{
    int priority = 0;
    if (op == '+' || op == '-')
        priority = 1;
    else if (op == '*' || op == '/')
        priority = 2;
    return priority;
}

string Postfix(const string& infix) 
{
    string postfix;
    stack<char> op;
    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] >= '0' && infix[i] <= '9') 
        {
            string temp;
            while (i <= infix.length() && infix[i] >= '0' && infix[i] <= '9')
            {
                postfix += infix[i];
                postfix += " ";
                i++;
            }
        }
        if (op.empty() || infix[i] == '(') 
        {
            op.push(infix[i]);
        }
        else if (infix[i] == ')') 
        {
            while (op.top()!='(') 
            {
                char temp = op.top();
                op.pop();
                postfix += temp;
                postfix += " ";
            }
            op.pop();
        }
        else if (Priority(infix[i]) > Priority(op.top())) 
        {
            op.push(infix[i]);
        }
        else if (Priority(infix[i]) == Priority(op.top()))
        {
            postfix += infix[i];
            postfix += " ";
        }
        else if (Priority(infix[i]) < Priority(op.top()))
        { 
            char temp = op.top();
            op.pop();
            postfix += temp;
            postfix += " ";
            i--;
        }
    }
    while (!op.empty()) 
    {
        char temp = op.top();
        op.pop();
        postfix += temp;
        postfix += " ";
    }
    return postfix;
}

double Result(const string& postfix)
{
    stack<double> numSt;
    double n1, n2;
    for (int i = 0; i < postfix.length(); i++)
    {
        if (postfix[i] == ' ')
            continue;
        if (postfix[i] >= '0' && postfix[i] <= '9')
        {
            string temp;
            while (i < postfix.length() && postfix[i] >= '0' && postfix[i] <= '9')
            {
                if (postfix[i] == ' ') 
                {
                    i++; 
                    continue;
                }
                temp += postfix[i];
                i++;
            }
            double num = Float(temp);
            numSt.push(num);
        }
        else
        {
            n1 = numSt.top();
            numSt.pop();
            n2 = numSt.top();
            numSt.pop();
            switch (postfix[i]) 
            {
            case '+':
                n1 = n1 + n2;
                break;
            case '-':
                n1 = n1 - n2;
                break;
            case '*':
                n1 = n1 * n2;
                break;
            case '/':
                n1 = n1 / n2;
                break;
            }
            numSt.push(n1);
        }
    }
    double result = n1;
    return result;
}

double Float(string num) 
{
    double n = 0;
    for (int i = 0; i < num.length(); i++)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            n = n * 10 + float(num[i] - '0');
        }
    }
    return n;
}