/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 第k小，考虑中序遍历的过程中寻找
// 题目中已经说明了，k一定有效，因此当遍历到第k个元素，则可以直接返回
// 编码一定要注意鸭，不要粗心大意
// 基准情况和递推情况都要考虑清楚鸭

class Solution {
public:
    int kthSmallest(TreeNode* root, int k);
    bool kthSmallest(TreeNode* root, int k, int &cnt, int &value);
};


bool Solution::kthSmallest(TreeNode *root, int k, int &cnt, int &value) {
    // 基准情况，刚好找到元素，或者指针为空
    if (!root)
        return false;

    bool ret = false;

    if (root->left) {
        ret = kthSmallest(root->left, k, cnt, value);
    }
    if (ret)
        return ret;
    cnt++;
    if (cnt == k) {
        value = root->val;
        return true;
    }

    return kthSmallest(root->right, k, cnt, value);
}

int Solution::kthSmallest(TreeNode *root, int k) {
    int value;
    int cnt = 0;
    kthSmallest(root, k, cnt, value);
    return value;
}
