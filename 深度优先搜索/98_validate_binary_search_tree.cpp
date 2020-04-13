// 98_validate_binary_search_tree.cpp


// 踩坑过程
// 1.没有考虑全局情况，很简单的直接递归dfs，导致子树是合格BST但是整体并不是
//   这种反例非常好举，因此，在和根结点比较的时候，应该和左子树的最大值 右子树的最小值比较
//   不能单独比较左子树根结点，右子树根结点这两个结点
//   考虑到我们使用的是dfs，递归到最深的子树最多三个结点，因此，最深处的dfs判断的结果是准确的
//   如果不是合法BST直接就return false了
//   每次获取子树的最大或者最小值的基础就是，子树本身就是合法的BST，这点在上述得到证明
//   如果子树不是合法的，那么在比较之前，肯定就在深一层次的dfs已经返回false而不需要比较判断了

#include <iostream>
#include <vector>
#include <algorithm>
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
    bool isValidBST(TreeNode* root);
    int getMinval(TreeNode *root);
    int getMaxval(TreeNode *root);
};

int Solution::getMinval(TreeNode *root) {
	while (root->left)
		root = root->left;
	return root->val;
}

int Solution::getMaxval(TreeNode *root) {
	while (root->right)
		root = root->right;
	return root->val;
}

bool Solution::isValidBST(TreeNode *root) {
	// 处理输入为空树的情况
	if (root == nullptr)
		return true;
	if (root != nullptr && root->left == nullptr && root->right == nullptr)
		return true;

	int rootVal = root->val;
    // 左右子树都存在
    if (root->left && root->right) {
        if (getMaxval(root->left) < rootVal && getMinval(root->right) > rootVal) {
		    return isValidBST(root->left) &&
			       isValidBST(root->right);
	    } else
		    return false;
    } else if (root->left) {    // 只有左子树
        if (getMaxval(root->left) < rootVal)
            return isValidBST(root->left);
        return false;
    } else {                    // 只有右子树
         if (getMinval(root->right) > rootVal)
            return isValidBST(root->right);
        return false;
    }
}