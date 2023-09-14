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