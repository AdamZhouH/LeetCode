#include <vector>
#include <string>
#include <queue>
using namespace std;

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) return 0;
        int sum = 0;
        if (root->left && root->left->left == nullptr && root->left->right == nullptr) {
            sum += root->left->val;
        } else {
            sum += sumOfLeftLeaves(root->left);
        }
        sum += sumOfLeftLeaves(root->right);
        return sum;
    }
};

// 如果使用非递归的方式，利用队列来做层次遍历
int sumOfLeftLeaves(TreeNode *root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int sum = 0;
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        if (node->left && !node->left->left && !node->left->right)
            sum += node->left->val;
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return sum;
}