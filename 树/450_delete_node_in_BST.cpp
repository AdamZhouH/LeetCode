#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key);
};

// 先找到需要被删除的节点以及其父节点
// 然后根据不同的情况对节点执行删除操作
// 1.根结点或者非跟节点
// 2.叶子节点或者非叶子节点
// 先找到需要被删除的节点以及其父节点
// 然后根据不同的情况对节点执行删除操作
// 1.根结点或者非跟节点
// 2.叶子节点或者非叶子节点
TreeNode* Solution::deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
	// 删除根节点的情况
	if (root->val == key) {
		if (!root->left && !root->right) { delete root; return nullptr; }
		if (!root->left) { auto ret = root->right; delete root; return ret; }
		if (!root->right) { auto ret = root->left; delete root; return ret; }
		TreeNode *lr = root->left, *lrp = root->left; while (lr->right) lrp = lr, lr = lr->right;
        if (lr == lrp) {
            lr->right = root->right;
        } else {
            lrp->right = lr->left;
            lr->left = root->left;
            lr->right = root->right;
        }
        delete root;
        return lr;
	}
	TreeNode *parent = nullptr, *target = nullptr, *curr = root;
	while (target == nullptr && curr != nullptr) {
		if (curr->val == key) { target = curr; break;}
		else if (curr->val > key) parent = curr, curr = curr->left;
		else parent = curr, curr = curr->right;
	}
	// 没找到的情况
	if (target == nullptr) return root; 
	// 若为叶子节点
	if (!target->left && !target->right) { 
        if (parent->val > key) parent->left = nullptr;
        else parent->right = nullptr;
        delete target; return root; 
    }
	// 若存在一个空子树
	if (!target->left || !target->right) {
		if (!target->left) {
			if (parent->val > key) parent->left = target->right;
			else parent->right = target->right;
		} else {
			if (parent->val > key) parent->left = target->left;
			else parent->right = target->left;
		}
		delete target;
		return root;
	}
	// 若子树均非空，则找target的左子树最右节点或者右子树最左节点，作为新的target节点，这里选择左子树最右作为新的target节点
    TreeNode *lr = target->left, *lrp = target->left;
    while (lr->right) lrp = lr, lr = lr->right;
    if (lr == lrp) {
        lr->right = target->right;
        if (parent->val > key) parent->left = lr;
        else parent->right = lr;
    } else {
        lrp->right = lr->left;
        lr->left = target->left, lr->right = target->right;
        if (parent->val > key) parent->left = lr;
        else parent->right = lr;
    }
    delete target;
    return root;
    
}

// 这个递归，写的真是简洁
class Solution2 {
public:
    TreeNode* deleteNode(TreeNode* root, int key);
};

TreeNode* Solution2::deleteNode(TreeNode *root, int key) {
    if (root == NULL) return NULL;
    if (root->val == key) {
        if (root->left == NULL) return root->right;
        if (root->right == NULL) return root->left;
        TreeNode* leftright = root->left; 
		while (leftright->right) leftright = leftright->right;
        root->val = leftright->val;
        root->left = deleteNode(root->left, root->val);
    } else if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else
        root->right = deleteNode(root->right, key);
    return root;
}