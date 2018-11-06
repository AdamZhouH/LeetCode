// 二叉树的前序遍历的迭代版本的实现

#ifndef NULL
#define NULL 0
#endif

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> preorderTraversal(TreeNode *root);
};

vector<int> Solution::preorderTraversal(TreeNode *root) {
	vector<int> result;
	if (!root)
		return result;
	stack<TreeNode *> path;
	TreeNode *currNode = root;

	while (currNode || !path.empty()) {
		// 先遍历根节点和左子树的根节点直到左边都遍历完
		while (currNode) {
			result.push_back(currNode->val);
			path.push(currNode);
			currNode = currNode->left;
		}
		// 完成后，上一个节点出栈，遍历其右子树
		// 这里保证了每次返回到下一次迭代时，都是从右边子树返回，并且其根节点已经出栈，不会重复访问
		// 其实做法步骤和中序遍历结果是类似的，但是细节调整
		// 中序是先左子树，然后根然后右子树，我们要先找到最左边子树的根，然后访问其左子树
		// 然后根，然后右子树，并且一旦根访问完，就必须出栈，整体的逻辑关系是 if else
		// 先序遍历则是先根，后然左子树，然后右子树，那么在一直往左走的过程中，每个遇到的都是左子树的根节点
		// 必须先遍历访问，留在栈中的都是已经遍历其根和做子树，但是没有遍历右子树的节点
		// 一旦遍历完成左子树和自身，则立马出栈，currNode设置为右儿子的指针
		// 反映在逻辑上则是先while，然后每一次迭代都先出栈一个当前元素，然后设置currNode为其右儿子
		currNode = path.top()->right;
		path.pop();
	}
	return result;
}

int main(void) {
	vector<int> traverPath;
	TreeNode *root = new TreeNode(1);
	TreeNode *node1 = new TreeNode(2);
	TreeNode *node2 = new TreeNode(3);

	root->right = node1;
	node1->left = node2;

	Solution solution;
	traverPath = solution.preorderTraversal(root);
	for (auto var : traverPath)
		cout << var << " ";
	cout << endl;
	return 0;
}
