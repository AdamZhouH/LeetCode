// 判断是否是合法的二叉搜索树

#include <iostream>
#include <string>
#include <utility>
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
    pair<bool, pair<int,int>> isValid(TreeNode *root);
};

// 显然应该使用递归来写，递归应该返回的条件是一个pair<bool,pair<int,int>>，元素分别表示子树是否是搜索二叉树，并返回最大值和最小值
// 注意递归的终止条件以及一颗空树的情况
// 如果一棵树为空树，显然是满足条件的二叉搜索树
pair<bool, pair<int,int>> Solution::isValid(TreeNode *root) {
    int minval = root->val, maxval = root->val;
    if (root->left != nullptr) {
        auto ret = isValid(root->left);
        if (ret.first == false || ret.second.second >= root->val) return {false, {minval, maxval}};
        else minval = ret.second.first;
    }
    if (root->right != nullptr) {
        auto ret = isValid(root->right);
        if (ret.first == false || ret.second.first <= root->val) return {false, {minval, maxval}};
        else maxval = ret.second.second;
    }
    return {true, {minval, maxval}};
}

bool Solution::isValidBST(TreeNode *root) {
    if (root == nullptr) return true;
    auto ret = isValid(root);
    return ret.first;
}

// 还有一种方法，通过中序遍历，判断是否严格增序来确定是否是满足条件的树
// 这种思路的做法，关键是要用一个变量保存上一次遍历的节点的值
TreeNode *last = nullptr;
bool isValidBST(TreeNode *root) {
    if (root == nullptr) return true;
    if (!isValidBST(root->left)) return false;
    if (last != nullptr && root->val <= last->val) return false;
    last = root;
    return isValidBST(root->right);
}
