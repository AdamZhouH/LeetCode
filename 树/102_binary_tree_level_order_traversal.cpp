#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

// 比较简单的层次遍历的实现
// 注意的是需要分开每个层次的节点，放入不同的vector中

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :
		val(x),
		left(nullptr),
		right(nullptr) {}
};

using namespace std;

class Solution {
	public:
		vector<vector<int>> levelOrder(TreeNode *root);
};

vector<vector<int>> Solution::levelOrder(TreeNode *root) {
	vector<vector<int>> ret;
	if (!root)
		return ret;
	queue<TreeNode *> nodes;
	nodes.push(root);
	int currLevelLength = 1;
	int nextLevelLength = 0;
	while (!nodes.empty()) {
		// 处理每一层的节点，同时计算下一层的节点个数
		vector<int> currLevelNodeValue;
		while (currLevelLength--) {
			TreeNode *temp = nodes.front();
			nodes.pop();
			if (temp->left) {
				nodes.push(temp->left);
				nextLevelLength++;
			}
			if (temp->right) {
				nodes.push(temp->right);
				nextLevelLength++;
			}
			currLevelNodeValue.push_back(temp->val);
		}
		ret.push_back(currLevelNodeValue);
		currLevelNodeValue.clear();
		currLevelLength = nextLevelLength;
		nextLevelLength = 0;
	}
	return ret;
	
}
