#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root);
    pair<int,int> dfs(TreeNode *root);
};

// 直接暴力递归
pair<int,int> Solution::dfs(TreeNode *root) {
    if (root == nullptr) return {0,0};
    auto leftSide = dfs(root->left);
    auto rightSide = dfs(root->right);
    auto height = max(leftSide.second, rightSide.second) + 1;
    auto diameter = max({leftSide.first, rightSide.first, leftSide.second + rightSide.second});
    return {diameter, height};
}

int Solution::diameterOfBinaryTree(TreeNode* root) {
    if (root == nullptr) return 0;
    return dfs(root).first;
}

// 另一种递归思路则是通过直接计算每个节点上，以此节点为根结点的最长路径
class Solution2 {
public:
    int dfs(TreeNode *root, int &maxValue) {
        if (root == nullptr) return 0;
        auto left = dfs(root->left, maxValue);
        auto right = dfs(root->right, maxValue);
        maxValue = max(maxValue, left+right);
        return max(left, right) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;
        int maxValue = INT_MIN;
        dfs(root, maxValue);
        return maxValue;
    }
};
