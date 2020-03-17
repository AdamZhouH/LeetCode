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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
    TreeNode* buildTree(vector<int>& preorder, int beg1, int end1, vector<int>& inorder, int beg2, int end2);
};

TreeNode *Solution::buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.empty())
        return nullptr;
    return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

TreeNode *Solution::buildTree(vector<int>& preorder, int beg1, int end1, vector<int>& inorder, int beg2, int end2) {
    // 递归构建左右子树
    // preorder数组首元素为根结点元素，然后在inorder根据根结点元素划分出左右子树的元素
    // 注意递归的基准情况的判断
    if (beg1 > end1)
        return nullptr;
    // assert((end1 - beg1) == (end2 - beg2));
    int val = preorder[beg1];
    int k;
    for (k = beg2; k <= end2; k++)
        if (inorder[k] == val)
            break;
    TreeNode *root = new TreeNode(val);
    root->left = buildTree(preorder, beg1 + 1, k + beg1 - beg2, inorder, beg2, k - 1);
    root->right = buildTree(preorder, k + beg1 - beg2 + 1, end1, inorder, k + 1, end2);
    return root;
}
