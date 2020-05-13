#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
    int minDepth(TreeNode* root);
};

// 层序遍历思路：遇到一个叶子结点则记录当前的层数
int Solution::minDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int ans = INT_MAX;
    queue<TreeNode *> q; q.push(root);
    int currLevel = 0;
    while (!q.empty()) {
        currLevel++;
        int size = q.size();
        while (size--) {
            auto node = q.front(); q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
            if (!node->left && !node->right)
                ans = min(ans, currLevel);
        }
    }
    return ans;
}

// 给出一个深度遍历的思路的解法，也比较简单
class Solution2 {
public:
    int minDepth(TreeNode* root);
    void dfs(TreeNode *root, vector<TreeNode*> &path, int &minPath);
};

// 深度优先遍历思路（按照先序遍历，记录路径，每当遇到一个节点就更新最短路径）
void Solution2::dfs(TreeNode *root, vector<TreeNode*> &path, int &minPath) {
    if (root == nullptr) return;
    path.push_back(root);
    if (!root->left && !root->right)
        minPath = min(minPath, static_cast<int>(path.size()));
    dfs(root->left, path, minPath);
    dfs(root->right, path, minPath);
    path.pop_back();
}

int Solution2::minDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int ret = INT_MAX;
    vector<TreeNode *> path;
    dfs(root, path, ret);
    return ret;
}

// 最简单的递归方法
class Solution3 {
public:
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        int left=minDepth(root->left),right=minDepth(root->right);
        return (left && right) ? 1+min(left,right):1+left+right;
    }
};
