#ifndef NULL
#define NULL 0
#endif

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

// 把有序数组转变为平衡二叉树
// 直接分治递归即可

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums);
    TreeNode *doSortedArrayToBST(vector<int> &nums, int start, int end);
};

TreeNode *Solution::sortedArrayToBST(vector<int> &nums) {
	if (nums.size() == 0)
		return nullptr;
	return
		doSortedArrayToBST(nums, 0, nums.size() - 1);
}

TreeNode *Solution::doSortedArrayToBST(vector<int> &nums, int start, int end) {
	if (end < start)
		return nullptr;
	int center = (start + end) / 2;
    
	TreeNode *root = new TreeNode(nums[center]);
	root->left = doSortedArrayToBST(nums, start, center - 1);
	root->right = doSortedArrayToBST(nums, center + 1, end);
    
	return root;
}

