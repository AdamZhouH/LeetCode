#include <queue>
#include <iostream>
using namespace std;

// 层序遍历判断
// 1.只要出现节点左子树空，但右子树非空，则非完全
// 2.如果出现右子树为空，那么剩下所有节点都必须是叶子节点
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode *> q; q.push(root);
        bool flag = false;
        while (!q.empty()) {
            auto node = q.front(); q.pop();
            // 把肯定不合法的两种情况直接排除
            if (!node->left && node->right) return false;
            if (flag && (node->left || node->right)) return false;
            // 出现子树为空，置flag为true，剩下的节点必须是叶子节点
            if (!node->left || !node->right) flag = true;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return true;
    }
};