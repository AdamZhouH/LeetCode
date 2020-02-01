// 已知一颗二叉树中的两个节点被交换，导致二叉搜索树的性质被破坏
// 现在需要你恢复这颗二叉搜索树

// 思路：暴力破解
// 二叉搜索树的恢复这种问题，很显然的必须用到二叉树搜索树的突出的性质
// 中序遍历的结果应该是有序非递减序列
// 我们先遍历，得到中序遍历结果，然后从数组中应当很容易找到两个错误的节点，然后交换即可
// 注意，遍历的结果存放在数组中，数组中每个元素保存两个内容，一个是指向节点的指针，一个则是节点的值
// 这样，一次遍历完毕后，直接交换

// 时间复杂度和空间复杂度都是 O(n)

// 思路二，可以在中序遍历的过程中直接找到错误节点，记录下来，然后完成中序遍历之后，把两个错误节点的指针
// 的值交换即可，从而保证空间复杂度为常数
// 那么递归过程中，需要增加一个pre参数，表示之间遍历到的节点

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void recoverTree(TreeNode* root);
    void inorderTraversal(TreeNode *root, vector<pair<TreeNode *, int>> &path);
};

void Solution::inorderTraversal(TreeNode *root, vector<pair<TreeNode *, int>> &path) {
	if (root == nullptr)
		return;
	inorderTraversal(root->left, path);
	path.push_back(make_pair(root, root->val));
	inorderTraversal(root->right, path);
}

void Solution::recoverTree(TreeNode * root) {
	vector<pair<TreeNode *, int>> path;
	inorderTraversal(root, path);
	// 从头尾分别遍历，找到两个元素，时间复杂度一起为 O(n)
	TreeNode *first, *second;
	for (int i = 1; i < path.size(); i++)
		if (path[i].second < path[i - 1].second) {
			first = path[i - 1].first;   // 赋值这里不要搞错了
			break;
		}
	for (int j = path.size() - 2; j >= 0; j--) {
		if (path[j].second > path[j + 1].second) {
			second = path[j + 1 ].first;  // 同上，注意赋值不要搞错
			break;
		}
	}
	// 交换两个指针指向的元素即可
	int temp = first->val;
	first->val = second->val;
	second->val = temp;
}


