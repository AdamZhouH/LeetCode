#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode (int x) : val(x), left(nullptr), right(nullptr) { }
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
