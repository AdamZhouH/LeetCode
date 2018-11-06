#ifndef NULL
#define NULL 0
#endif

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

// 二叉树的中序遍历的非递归版本

// 基本思路，中序遍历的顺序是左子树 根 右子树
// 那么，先从根出发，一直往左走，边走元素边入栈，直到走到最左，然后元素出栈
// 访问此元素，然后置当前指针为此出栈节点的右儿子指针，然后重复上述循环
// 实际上，我们这样做保证了每次出栈后，继续下一次迭代的时候，都是从右子树返回的
// 那么就不会导致重复遍历左子树而带来的死循环

// 循环的边界条件是当前指针为空并且栈也为空


#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> inorderTraversal(TreeNode *root);
};

vector<int> Solution::inorderTraversal(TreeNode *root) {
	if (root == nullptr)
		return vector<int> ();
	stack<TreeNode *> path;  // 存放没有访问过，即将被访问的结点
	vector<int> result;
	TreeNode *currNode = root;
/* 问题代码
	path.push(root);
	while (!path.empty()) {
		currNode = path.top();
		// 一直左走，直到遇到空，说明走到最左边
		while (currNode->left) {
			path.push(currNode->left);
			currNode = currNode->left;
		}
		// 遍历当前栈顶节点，并出栈，然后判断是否存在右子树，存在则右子树根结点入栈，之后重复上述步骤
		path.pop();
		result.push_back(currNode->val);
		// 右子树是否存在？
		if (currNode->right) 
			path.push(currNode->right);
		// 这里容易导致死循环，当从当前节点返回到上层的节点，如果左子树不为空，则会重复循环访问
		// 导致死循环，因为实际上返回到的上一层的左子树已经被访问过了，如何判断上一层的左子树已经访问
	}
	*/
	// 正确做法
	while (currNode || !path.empty()) {
		if (currNode) {
			path.push(currNode);
			currNode = currNode->left;
		} else {
			currNode = path.top();
			path.pop();
			result.push_back(currNode->val);
			currNode = currNode->right;
		}
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
	traverPath = solution.inorderTraversal(root);
	for (auto var : traverPath)
		cout << var << " ";
	cout << endl;
	return 0;
}