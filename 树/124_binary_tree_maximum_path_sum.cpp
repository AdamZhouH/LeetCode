/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#define MIN -11111

class Solution {
public:
    int maxPathSum(TreeNode* root);
    int findMaxPath(TreeNode *root, int);
};

// 思路
// 从树中，任意节点到另外一个任意节点，是唯一路径的
// 并且这条路径一定是以某个节点为根节点
// 然后左半边就是这个根节点到它的左子树的某个节点的最大路径和
// 右半边就是这个根节点到它的右子树的某个节点的最大路径和
// 因此，解决方法就很清楚了
// 遍历，针对每一个节点，找到从根节点到某个节点的最大路径
// 上述方法可以利用递归
// 同时，在遍历过程中，判断当前路径和是否是最大的，是，则更新最大路径
// 直到都遍历完毕即可

// 函数用于找到以某个节点为根，从此节点到某一个节点的路径最大值
class Solution {
public:
    int maxPathSum(TreeNode* root);
    int findMaxPath(TreeNode *root, int &maxPath);
};

// 思路
// 从树中，任意节点到另外一个任意节点，是唯一路径的
// 并且这条路径一定是以某个节点为根节点
// 然后左半边就是这个根节点到它的左子树的某个节点的最大路径和
// 右半边就是这个根节点到它的右子树的某个节点的最大路径和
// 因此，解决方法就很清楚了
// 遍历，针对每一个节点，找到从根节点到某个节点的最大路径
// 上述方法可以利用递归
// 同时，在遍历过程中，判断当前路径和是否是最大的，是，则更新最大路径
// 直到都遍历完毕即可

int Solution::findMaxPath(TreeNode *root, int &maxPath) {
	if (!root)
		return 0;
	int left = findMaxPath(root->left, maxPath);
	int right = findMaxPath(root->right, maxPath);
	// ret 和 maxPath 求值时候要特别注意，因为两个意义并不相同
	// 而且maxPath和返回值没有关系，maxPath只是为了减少复杂度，顺带求的，实际上和这个函数的目的是两个问题
	int ret = max(max(left, 0), max(right, 0)) + root->val;
	maxPath = max(maxPath, max(left, 0) + max(right, 0) + root->val);
	return ret;
}

int Solution::maxPathSum(TreeNode *root) {
	int max = MIN;
	findMaxPath(root, max);
	return max;
}