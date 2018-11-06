/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// 思路，层序遍历的应用，每次给出每一层的最后一个节点即可
// BSF遍历+辅助队列，每次更新下一层的节点个数，更新当前层次剩余节点的个数

class Solution {
public:
    vector<int> rightSideView(TreeNode* root);
};

vector<int> Solution::rightSideView(TreeNode *root) {
    vector<int> ret;
    if (!root)
        return ret;
    int currLevel = 1;
    int nextLevel = 0;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        // 开始遍历每一层，同时更新下一层的节点数目
        // 最后还需要更新当前层的个数
        while (currLevel--) {
            // 判断是否是当前层的最后一个节点
            TreeNode *p = q.front();
            q.pop();
            if (p->left) {
                q.push(p->left);
                nextLevel++;
            }
            if (p->right) {
                q.push(p->right);
                nextLevel++;
            }
            if (!currLevel) 
                ret.push_back(p->val);
        }
        currLevel = nextLevel;
        nextLevel = 0;
    }
    return ret;
}