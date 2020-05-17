class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums);
    TreeNode* build(vector<int>& nums, int start, int end);
};

TreeNode *Solution::build(vector<int>& nums, int start, int end) {
    if (start > end) return nullptr;
    if (start == end) return new TreeNode(nums[start]);
    int maxpos = start;
    for (int i = start; i <= end; i++) {
        if (nums[i] > nums[maxpos]) maxpos = i;
    }
    TreeNode *root = new TreeNode(nums[maxpos]);
    root->left = build(nums, start, maxpos-1);
    root->right = build(nums, maxpos+1, end);
    return root;
}

TreeNode *Solution::constructMaximumBinaryTree(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return build(nums, 0, nums.size() -1);
}