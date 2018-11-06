#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 先根遍历
// 遍历过程中，维护currSum 和 currPath
// 针对于上述两个变量，是一个回溯的过程
// 总体而言是一个先序遍历过程，因此，每当遍历完一个节点，必须恢复currSum 和currPath变量
// 每当遍历到一个叶子节点，则判断和，并考虑是否加入路径
// 否则直接继续dfs遍历过程

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum);
	void findPath(TreeNode *root, int &currSum, int &sum, vector<int> &currPath, vector<vector<int>> &totalPath);
};

void Solution::findPath(TreeNode *root, int &currSum, int &sum, vector<int> &currPath, vector<vector<int>> &totalPath) {
	// 采用先根遍历
	if (!root)
		return;
	currSum + =root->val;
	currPath.push_back(root->val);
	// 是否叶子
	// 是叶子，则判断路径和，并更新路径，非叶子，则直接递归遍历
	if (!root->left && !root->right) {
		if (currSum == sum)
			totalPath.push_back(currPath);
	}
	findPath(root->left, currSum, sum, currPath, totalPath);
	findPath(root->right, currSum, sum, currPath, totalPath);
	// 回溯情况，返回上一层，需要恢复currSum currPath
	currSum -= root->val;
	currPath.pop_back();
}

vector<vector<int>> Solution::pathSum(TreeNode *root, int sum) {
	vector<vector<int>> totalPath;
	vector<int> currPath;
	int currSum = 0;
	findPath(root, currSum, sum, currPath, totalPath);
	return totalPath;
}