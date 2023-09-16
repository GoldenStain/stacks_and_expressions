#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;

const int N = 1000005;

char a[20]; //用于输入

bool expression [N];//表达式栈，用于判断当前树的结构，0表示符号，1表示数字
stack<char> op;//符号栈
stack<double> num;//数字栈
int top; 

void calc()
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
    while(scanf("%s", a) != -1)
    {
        if(a[0] == '+' || a[0] == '-' || a[0] == '*' || a[0] == '/') 
        {
            expression[++top] = 0;
            op.push(a[0]);
        } 
        else 
        {
            double n = atof(a);
            expression[++top] = 1;
            num.push(n);
            while(expression[top] && top >= 3 && expression[top - 1])
            {
                calc();
            }
        }
    }
    printf("%lf\n", num.top());
    return 0;
}