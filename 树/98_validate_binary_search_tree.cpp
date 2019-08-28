// 判断是否是合法的二叉搜索树

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :
		val(x), left(nullptr), right(nullptr) { }
};

class Solution {
	public:
		bool isValidBST(TreeNode *root);
};
