#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <stdlib.h>

using namespace std;
typedef pair<int, int> PII;

unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void eval(stack<int>& num, stack<char>& op)
{
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    char c = op.top(); op.pop();

    int x;
    if(c == '+') x = a + b;
    else if(c == '-') x = a - b;
    else if(c == '*') x = a * b;
    else x = a / b;

    num.push(x);
}

bool is_negtive(string& s, int pos)
{
    if(pos == 0 && s[pos] == '-') return 1;
    if(s[pos] == '-' && s[pos - 1] == '(') return 1;
    return false; 
}

int GetNum(bool prefix, string& s, int start, stack<int>& num, stack<char>& op)
{
    int x = 0, j = start;
    while(j < s.size() && isdigit(s[j])) x = 10 * x + s[j++] - '0';
    if(prefix) num.push(x);
    else num.push(-x);
    //if(x == 100) cout << op.top() << endl;
    //if(!prefix) cout << "x=" << x << endl;
    return j;
}

PII resolve(string& s, int start)
{
    stack<char> op;
    stack<int> num;
    for(int i = start; i < s.size(); i++)
    {
        //cout << "now it is" << s[i] << endl;
        if(s[i] == ' ') continue;
        char c = s[i];
        if(isdigit(c))
        {
            int j = GetNum(1, s, i, num, op);
            i = j - 1;
            //cout << "after that is " << s[i] << endl;
        }
        else if(is_negtive(s, i))
        {
            if(isdigit(s[i + 1])) 
            {
                int j = GetNum(0, s, i + 1, num, op);
               //cout <<"j" << s[j] << ' ' << s[j - 1] << endl;
                //cout << "op.top()=" << op.top() << endl;
                i = j - 1;//注意要减一
            }
            else
            {
                PII tmp = resolve(s, i + 1);
                //cout << "tmp.first=" << tmp.first << endl;
                num.push(-tmp.first);
                //.cout << tmp.first << endl;
                i = tmp.second;//这里不用减一
                //cout <<  "I " << s[i] << endl;
            }
        }
        else if(c == '(') op.push(c);
        else if(c == ')')
        {
            while(op.size() && op.top() != '(') eval(num,op);
            op.pop();
            if(op.empty()) 
            {
                //cout << i << ' ' << s[i] << endl;
                return {num.top(),i};
            }
        }
        else
        {
            //cout << "op=" << s[i] << endl;
            //if(s[i] == '+') cout << s[i] << endl, cout << num.top() << endl;
            while(op.size() && pr[op.top()] >= pr[c]) eval(num, op);
            op.push(c);
            //cout << "now optop=" << op.top() << endl;
        }
    }
}

int main()
{
    string s;
    getline(cin, s);
    s = "(" + s + ")";//关键预处理，让递归得以实现
    cout << resolve(s, 0).first << endl;
    return 0;
}