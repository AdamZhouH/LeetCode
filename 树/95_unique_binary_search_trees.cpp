#include <iostream>
#include <string>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeeNode(int x) :
		val(x),
		left(nullptr),
		right(nullptr) { }
};

class Solution {
	public:
		vector<TreeNode *> generateTrees(int n);
		vector<TreeNode *> generateTrees(int start, int end);
};

vector<TreeNode *> Solution::generateTrees(int n) {
	vector<TreeNode *> ret;
	if (!n) {
		return ret;
	}
	return generateTrees(1, n);
}

vector<TreeNode *> Solution::generateTrees(int start, int end) {
	vector<TreeNode *> ret;
	if (start > end) {
		ret.push_back(nullptr);
		return ret;
	}
	if (start == end) {
		ret.push_back(new TreeNode(start));
		return ret;
	}
	// 尝试start和end之间的每个数字作为根节点
	// 利用二叉搜索树的特性：左子树节点 根节点 右子树节点的大小关系
	// 递归获取左右子树，然后将他们和根节点组合拼接
	for (int i = start; i <= end; i++) {
		// 获取左子树
		vector<TreeNode *> leftTrees = generateTrees(start, i - 1);
		// 获取右子树
		vector<TreeNode *> rightTrees = generateTrees(i + 1, end);
		// 拼接
		for (TreeNode *leftTree: leftTrees){
			for (TreeNode *rightTree: rightTrees) {
				TreeNode *root = new TreeNode(i);
				root->left = leftTree;
				root->right = rightTree;
				// 作为一颗完整的树，加入到ret集合中
				ret.push_back(root);
#include <vector>
#include <list>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeeNode(int x) :
		val(x),
		left(nullptr),
		right(nullptr) { }
};

class Solution {
	public:
		vector<TreeNode *> generateTrees(int n);
		vector<TreeNode *> generateTrees(int start, int end);
};

vector<TreeNode *> Solution::generateTrees(int n) {
	vector<TreeNode *> ret;
	if (!n) {
		return ret;
	}
	return generateTrees(1, n);
}

vector<TreeNode *> Solution::generateTrees(int start, int end) {
	vector<TreeNode *> ret;
	if (start > end) {
		ret.push_back(nullptr);
		return ret;
	}
	if (start == end) {
		ret.push_back(new TreeNode(start));
		return ret;
	}
	// 尝试start和end之间的每个数字作为根节点
	// 利用二叉搜索树的特性：左子树节点 根节点 右子树节点的大小关系
	// 递归获取左右子树，然后将他们和根节点组合拼接
	for (int i = start; i <= end; i++) {
		// 获取左子树
		vector<TreeNode *> leftTrees = generateTrees(start, i - 1);
		// 获取右子树
		vector<TreeNode *> rightTrees = generateTrees(i + 1, end);
		// 拼接
		for (TreeNode *leftTree: leftTrees){
			for (TreeNode *rightTree: rightTrees) {
				TreeNode *root = new TreeNode(i);
				root->left = leftTree;
				root->right = rightTree;
				// 作为一颗完整的树，加入到ret集合中
				ret.push_back(root);
			}
		}
	}
	return ret;
}


