#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) { }
};

class Solution {
public:
    // 考虑存在不同节点相同值的情况，如果是节点值都不同那就没什么意义了
    // 注意cloned和original实际上是结构完全相同的，因此两者跟着一起遍历即可
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        if (!original) return nullptr;
        if (original == target) return cloned;
        auto res = getTargetCopy(original->left, cloned->left, target);
        if (res) return res;
        return getTargetCopy(original->right, cloned->right, target);
    }
    
};
