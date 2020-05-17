#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int longestUnivaluePath(TreeNode* root);
    int dfs(TreeNode *root, int &maxValue);
    void travel(TreeNode *root, int &maxValue);
};

// 遍历，遍历过程中，计算以某个节点为根节点的最长路径，并更新整棵树的最长同路径值即可
// dfs返回的是以当前节点为根结点的左右两侧中的最大路径长度
int Solution::dfs(TreeNode *root, int &maxValue) {
    if (root == nullptr) return 0;
    int leftSide = (root->left == nullptr || root->val != root->left->val) ? 0 : dfs(root->left, maxValue) + 1;
    int rightSide = (root->right == nullptr || root->val != root->right->val) ? 0 : dfs(root->right, maxValue) + 1;
    maxValue = max(maxValue, leftSide + rightSide);
    return max(leftSide, rightSide);
}

void Solution::travel(TreeNode *root, int &maxValue) {
    if (root) {
        travel(root->left, maxValue);
        dfs(root, maxValue);
        travel(root->right, maxValue);
    }
}

int Solution::longestUnivaluePath(TreeNode *root) {
    if (root == nullptr) return 0;
    int maxValue = 0;
    travel(root, maxValue);
    return maxValue;
}
