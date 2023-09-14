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


