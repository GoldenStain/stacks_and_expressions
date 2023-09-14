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
    TreeNode *Root = solution.build(preorder, inorder);
    TreeTravel(Root);
    return 0;
}