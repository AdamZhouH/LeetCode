#include <vector>
#include <utility>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root);
    pair<bool, int> help(TreeNode *root);
};

pair<bool, int> Solution::help(TreeNode *root) {
    if (!root)
        return {true, 0};
    auto lh = help(root->left);
    auto rh = help(root->right);
    if (lh.first && rh.first && abs(lh.second - rh.second) <= 1)
        return {true, max(lh.second, rh.second) + 1};
    return {false, -1};
}

bool Solution::isBalanced(TreeNode *root) {
    auto ret = help(root);
    return ret.first;
}

