#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int getMinimumDifference(TreeNode* root);
    void dfs(TreeNode *root, vector<int>& val);
};

// 既然是二叉搜索树，那就肯定是中序遍历
// 然后计算每对相邻两个节点的差的绝对值，然后取最小值
void Solution::dfs(TreeNode *root, vector<int>& val) {
    if (root != nullptr) {
        dfs(root->left, val);
        val.push_back(root->val);
        dfs(root->right, val);
    }
}

int Solution::getMinimumDifference(TreeNode* root) {
    vector<int> nodes;
    dfs(root, nodes);
    int minValue = INT_MAX;
    for (int i = 1; i < nodes.size(); i++)
        minValue = min(minValue, abs(nodes[i]-nodes[i-1]));
    return minValue;
}

// 当然，不借助vector保存遍历结果也行，只需要在dfs过程中记录遍历的前一个节点即可
void ::dfs(TreeNode *root, TreeNode *&prev, int &minValue) {
    if (root != nullptr) {
        dfs(root->left, prev, minValue);
        if (prev) minValue = min(minValue, abs(root->val - prev->val));
        prev = root;
        dfs(root->right, prev, minValue);
    }
}

int ::getMinimumDifference(TreeNode* root) {
    int minValue = INT_MAX;
    TreeNode *prev = nullptr;
    dfs(root, prev, minValue);
    return minValue;
}