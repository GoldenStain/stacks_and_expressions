# stacks_and_expressions 用栈处理算数表达式的二三事

## 前置知识 二叉树结构的确定

因为前缀表达式，中缀表达式，以及后缀表达式，本质上是对表达式树进行不同遍历方式所得到的结果，所以在进行表达式求解之前，我们有必要知道这三种结构的处理和转化。
根据树的遍历的特性，可以得到：*前序遍历和中序遍历的组合，或者后序遍历和中序遍历的组合，可以确定一棵树的结构*。

### 根据前序遍历和中序遍历确定一棵树的结构
```
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;

int n;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> preorder, inorder;

class DataProcess
{
public:
    void input()
    {
        scanf("%d", &n);
        preorder.resize(n);
        inorder.reserve(n);
        for (int i = 0; i < n; i++)
            scanf("%d", &preorder[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &inorder[i]);
    }
};

class Solution
{
public:
    TreeNode* build(vector<int>& preorder, vector<int>& inorder)
    {
        for(int i = 0; i < n; i++) 
         inorder_map[inorder[i]] = i;
        return TreeBuild(preorder, 0, n - 1, inorder, 0, n - 1);
    }
private:
    unordered_map<int, int> inorder_map;
    TreeNode* TreeBuild(vector<int> preorder, int pre_l, int pre_r, vector<int> inorder, int in_l, int in_r)
    {
        if(pre_l > pre_r) return nullptr;
        int RootVal = preorder[pre_l], RootPos = inorder_map[RootVal];
        TreeNode* Root = new TreeNode(RootVal);
        int TreeLength = RootPos - in_l;
        Root->left = TreeBuild(preorder, pre_l + 1, pre_l + TreeLength, inorder, in_l, RootPos - 1);
        Root->right = TreeBuild(preorder, pre_l + TreeLength + 1, pre_r, inorder, RootPos + 1, in_r);
        return Root;
    }
};

void TreeTravel(TreeNode *Root)
{
    if (Root)  //第一次写时顺手写成了while，这就导致while的循环功能和递归函数的重复处理功能相冲突，导致程序在递归的上下两层之间无限循环。
    {
        TreeTravel(Root->left); 
        printf("%d ", Root->val);
        TreeTravel(Root->right);
    }
}

int main()
{
    DataProcess dataprocess;
    dataprocess.input();
    Solution solution;
    TreeNode *Root = solution.build(preorder, inorder);
    TreeTravel(Root);
    return 0;
}
```

### 根据后序遍历和中序遍历确定一棵树的结构

整体思路相同，只不过后序遍历的序列改为倒序循环遍历来确定根和左右子树。

```
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
using namespace std;

int n = 5;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> postorder, inorder;

class DataProcess
{
public:
    void input()
    {
        scanf("%d", &n);
        postorder.resize(n);
        inorder.reserve(n);
        for (int i = 0; i < n; i++)
            scanf("%d", &postorder[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &inorder[i]);
    }
};

class Solution
{
public:
    TreeNode *build(vector<int> &postorder, vector<int> &inorder)
    {
        for (int i = 0; i < n; i++)
            inorder_map[inorder[i]] = i;
        return TreeBuild(postorder, 0, n - 1, inorder, 0, n - 1);
    }

private:
    unordered_map<int, int> inorder_map;
    TreeNode *TreeBuild(vector<int> postorder, int post_l, int post_r, vector<int> inorder, int in_l, int in_r)
    {
        if (post_l > post_r)
            return nullptr;
        int RootVal = postorder[post_r], RootPos = inorder_map[RootVal];
        TreeNode *Root = new TreeNode(RootVal);
        int TreeLength = RootPos - in_l;
        Root->right = TreeBuild(postorder, post_l + TreeLength, post_r - 1, inorder, RootPos + 1, in_r);
        Root->left = TreeBuild(postorder, post_l, post_l + TreeLength - 1, inorder, in_l, RootPos - 1); 
        return Root;
    }
};

void TreeTravel(TreeNode *Root)
{
    if (Root)
    {
        TreeTravel(Root->left);
        printf("%d ", Root->val);
        TreeTravel(Root->right);
    }
}

int main()
{
    DataProcess dataprocess;
    dataprocess.input();
    Solution solution;
    TreeNode *Root = solution.build(postorder, inorder);
    TreeTravel(Root);
    return 0;
}

```



## 前缀表达式求值

这是最为简单的一种情况，因为你不需要栈，仅用一个优美的递归就能解决这个问题。

### 1.
```
#include <stdio.h>
#include <stdlib.h>
char a[20];
double expt()
{
    scanf("%s",a);
    switch(a[0])
    {
        case '+':
            return expt()+expt();
        case '-':
            return expt()-expt();
        case '*':
            return expt()*expt();
        case '/':
            return expt()/expt();
        default:
            return atof(a);
    }
    return a[0];
}
int main()
{
 
    double ans=0;
    ans=expt();
    printf("%lf\n",ans);
    return 0;
}

```

### 2.
当然，因为这个问题也可以用循环和栈来实现。
根据前缀表达式的特点，我们可以建三个栈：
字符串栈，符号栈，以及数字栈。符号栈和数字栈用于处理运算，字符串栈用于判断当前树的结构。
```
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
```

## 后缀表达式求值

和前缀表达式大体类似，它们在形式上相互对称。

```
#include <stdio.h>
#include <stdlib.h>
#include <stack>
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
    while(scanf("%s", a) != -1)
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
    printf("%lf\n", num.top());
    return 0;
}
```

## 中缀表达式求值

虽然这是最便于人类理解的一种方式，但这恰恰是处理起来最麻烦的，因为它引入了括号来控制计算的优先级。
前面的表达式求值代码都是用于应对输入的符号和数字之间两两使用空格隔开的情况，这段代码用于处理输入不带空格隔开的中缀表达式。
（这段代码中的除法为整数除法）
这篇题解可以帮助更好地理解这个算法 https://www.acwing.com/solution/content/69284/

```
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

stack<char> op;
stack<int> num;
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void eval()
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

int main()
{
    string s;
    cin >> s;

    for(int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if(isdigit(c))
        {
            int x = 0, j = i;
            while(j < s.size() && isdigit(s[j])) x = 10 * x + s[j++] - '0';
            i = j - 1;
            num.push(x);
        }
        else if(c == '(') op.push(c);
        else if(c == ')')
        {
            while(op.size() && op.top() != '(') eval();
            op.pop();
        }
        else
        {
            while(op.size() && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    while(op.size()) eval();
    cout << num.top() << endl;
    return 0;
}

```

## 中缀表达式求值 plus

但是上面的代码有一个问题：它不能处理带有负数的情况，即输入的表达式中，减号只能做减号使用，不能表示负号，为了解决这个问题，我们不得不升级上面的代码。
把每个负号后紧跟的数字或括号整体，当作一个独立的表达式，首先进行递归运算，返回其整体的计算结果，再将其入栈。

```
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
```


