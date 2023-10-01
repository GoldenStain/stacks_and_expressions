#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;

const int N = 1000005;

char a[20];
int top;
bool expression[N];//表达式栈
stack<char> op;//符号栈
stack<double> num;//数字栈

inline void calc()
{
    double b = num.top();
    num.pop();
    double a = num.top();
    num.pop();
    char c = op.top();
    op.pop();
    double res;
    if(c == '+') res = a + b;
    if(c == '-') res = a - b;
    if(c == '*') res = a * b;
    if(c == '/') res = a / b;
    num.push(res);
    top -= 3;
    expression[++top] = 1;
}

int main()
{
    while(cin >> a)
    {
        if(a[0] == '-' || a[0] == '+' || a[0] == '/' || a[0] == '*')
        {
            expression[++top] = 0;
            op.push(a[0]);
            while(!expression[top])
            {
                calc();
            }
        }
        else 
        {
            double n = atof(a);
            expression[++top] = 1;
            num.push(n);
        }
    }
    if(num.size() > 1) puts("error");
    else printf("%lf\n", num.top());
    return 0;
}