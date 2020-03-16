#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left, *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root);
};

vector<vector<int>> Solution::levelOrderBottom(TreeNode *root) {
	vector<vector<int>> ret;
	if (!root)
		return ret;
	queue<TreeNode *> nodes;
	nodes.push(root);
	int currLevelNumber = 1;
	int nextLevelNumber = 0;
	vector<int> currLevelNode;
	// 层次遍历，每层元素放入一个vector中
	while (!nodes.empty()) {
		while (currLevelNumber--) {
			TreeNode *node = nodes.front();
			nodes.pop();
			currLevelNode.push_back(node->val);
			if (node->left) {
				nodes.push(node->left);
				nextLevelNumber++;
			}
			if (node->right) {
				nodes.push(node->right);
				nextLevelNumber++;
			}
		}
		ret.push_back(currLevelNode);
		currLevelNode.clear();
		currLevelNumber = nextLevelNumber;
		nextLevelNumber = 0;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}
