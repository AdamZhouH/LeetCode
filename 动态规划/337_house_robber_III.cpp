#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 之前的思路是将元素节点的关系保存在一维数组中
// 结果是错的，因为一维数组中只能保存某个元素与左右两个元素的相邻关系
// 而实际上树中的节点可能存在3个相邻关系，一维数组不可能保存所有的元素之间的相邻关系
// 需要换其他的思路

// 个人感觉dp问题中，对于dp的解释很重要，dp解释好了，才能清楚如何初始化dp的值，以及明确递推公式

class Solution {
public:
    int rob(TreeNode* root);
    void postOrder(TreeNode *root, int &maxprofit, map<TreeNode *, int> &dp);
};

// 递归+dp思路
// dp[i]表示以i为根结点的树的能够获得的最大收益
// 则根据i节点是否选择，得到递推公式
// dp[i] = max(dp[i.left] + dp[i.right] , i.val + dp[i.left.left] + dp[i.left.right] + dp[i.right.left] + dp[i.right.right])
// 意思就是，当前节点可选择或者不选
// 如果不选，则左右儿子都可以选，并且都选
// 如果选择了根结点，则左右子树的根结点都不可以选择，应该选择左右子树的左右子树（但实际上左右儿子的左右儿子不一定存在）
// 根据以上的递推公式，考虑自底向上的遍历的同时，填充dp数组, dp数组的初始化显然是要根据那些叶子节点来，因为叶子节点没有左右儿子
// 因此，想到用后序遍历，在后续遍历的过程中，填充每个节点的dp值，算法利用递归来实现

void Solution::postOrder(TreeNode *root, int &maxprofit, map<TreeNode *, int> &dp) {
    // 递归基准情况，当前节点为叶子节点
    // 此情况下，以root为根的树的最大收益显然是选择自己
    if (root && !root->left && !root->right) {
        dp[root] = root->val;
        maxprofit = max(maxprofit, dp[root]);
        return;
    }
    // 按照后序遍历，递归左右子树，得到左右子树的最大收益
    if (root->left) postOrder(root->left, maxprofit, dp);
    if (root->right) postOrder(root->right, maxprofit, dp);
    // 填充根结点的dp
    // 计算选择根结点时候的最大收益
    int withoutRoot = dp[root->left]+dp[root->right];
    int withRoot = root->val;
    if (root->left) {
        if (root->left->left) withRoot += dp[root->left->left];
        if (root->left->right) withRoot += dp[root->left->right];
    }
    if (root->right) {
        if (root->right->left) withRoot += dp[root->right->left];
        if (root->right->right) withRoot += dp[root->right->right];
    }
    dp[root] = max(withoutRoot, withRoot);
    maxprofit = max(maxprofit, dp[root]);
}

int Solution::rob(TreeNode *root) {
    if (!root) return 0;
    int maxprofit = 0;
    map<TreeNode *, int> dp;
    postOrder(root, maxprofit, dp);
    return maxprofit;
}


/* 这是个错误做法，因为相邻关系不可能全部保存在一维数组中
void Solution::inorderTravel(vector<int>& values, TreeNode *root) {
    if (root) {
        values.push_back(root->val);
        inorderTravel(values, root->left);
        inorderTravel(values, root->right);
    }
}

int Solution::rob(TreeNode *root) {
    vector<int> values;
    inorderTravel(values, root);
    if (values.size() == 0) return 0;
    if (values.size() == 1) return values[0];
    vector<int> dp(values.size(), 0);
    int ret = max(values[0], values[1]);
    dp[0] = values[0], dp[1] = ret;
    for (int i = 2; i < dp.size(); i++) {
        dp[i] = max(dp[i - 2] + values[i], dp[i - 1]);
        ret = max(ret, dp[i]);
    }
    return ret;
}
*/

TreeNode *buildTree() {
    TreeNode *a = new TreeNode(3);
    TreeNode *b = new TreeNode(2);
    TreeNode *c = new TreeNode(3);
    TreeNode *d = new TreeNode(3);
    TreeNode *e = new TreeNode(1);
    a->left = b, a->right = c, b->right = d, c->right = e;
    return a;
}

int main(void) {
    TreeNode *root = buildTree();
    Solution slu;
    cout << slu.rob(root) << endl;
    return 0;
}