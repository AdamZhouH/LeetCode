#include <vector>
#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        // 注意是二叉搜索树，因此需要充分利用排序的特点
        // 中序遍历是有序结果，因此在有序结果上进行查找
        // 使用二分或者双指针，这里用双指针会快些
        if (root == nullptr) return false;
        vector<int> ret;
        travel(root, ret);
        int left = 0, right = ret.size()-1;
        while (left < right) {
            int sum = ret[left] + ret[right];
            if (sum == k) return true;
            else if (sum > k) right--;
            else left++;
        }
        return false;
    }
    
    void travel(TreeNode *root, vector<int> &ret) {
        if (root != nullptr) {
            travel(root->left, ret);
            ret.push_back(root->val);
            travel(root->right, ret);
        }
    }                                   
};
