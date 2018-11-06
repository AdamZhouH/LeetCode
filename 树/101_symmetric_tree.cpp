#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 给定一颗二叉树，判断其是否是一颗镜像二叉树

// 个人思路，考虑镜像二叉树的特点
// 如果从根节点开始，递归的把左右子树都交换，那么得到的还是和原来一颗一模一样的树
// 否则，则是不同的树
// 考虑一颗二叉树，中序遍历和先序遍历结合，可以确定一棵二叉树的形态
// 那么只要两颗树的中序遍历和先序遍历，完全一致，那么就可以断定为镜像树
// 时间复杂度，两次遍历树 o(n)
// 两次比较遍历结果，时间复杂度O(n)
// 总体时间复杂度 O(n)

// 自己想的方法，真的是很蠢的方法
// 实际上可以考虑递归，把一棵树，堪称由两颗子树组成的树来判断
// 一棵树是镜像的，那么他的左右子树互为镜像的
// 如果可以判断两颗子树镜像的，那么整棵树就是镜像的
// 对于判断两颗子树是否镜像，可以有如下的方法
// 先判断两颗子树的根是否是相同元素，否则，直接return false
// 是，判断左子树的左子树的根和右子树的右子树的根
//    判断左子树的右子树的根和右子树的左子树的根
// 如果都相同，则递归的判断即可。


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        // 一些可以直接判断的情况
        if (!root)
        	return true;
        else
    		return symmetric(root->left, root->right);
    }

    bool symmetric(TreeNode *left, TreeNode *right) {
    	// 均为空
    	if (!left && !right)
    		return true;
    	// 其中一个为空，另一个不为空
    	if (!left || !right)
    		return false;
    	// 均不为空
    	else if (left->val == right->val)
    		return symmetric(left->left, right->right) && symmetric(left->right, right->left);
    	else
    		return false;
    }
};