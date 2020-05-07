#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode  {
    int val;
    TreeNode *left, *right;
    TreeNode (int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSubtree(TreeNode *s, TreeNode *t);
    void  isSubtree(TreeNode *s, TreeNode *t, bool &flag);
    bool help(TreeNode *s, TreeNode *t);
};

// 简单递归思路，当遍历到节点和根节点相同的值时，调用help判断是否当前子树和目标子树具有一致的结构
// 遍历节点用递归，判断子树一致性也用递归，注意剪枝
void Solution::isSubtree(TreeNode *s, TreeNode *t, bool &flag) {
    if (flag || s == nullptr) return;
    if (s->val == t->val)
        flag = help(s->left,t->left) && help(s->right, t->right);
    if (!flag) isSubtree(s->left, t, flag);
    if (!flag) isSubtree(s->right, t, flag);
} 

bool Solution::help(TreeNode *s, TreeNode *t) {
    if (s == nullptr && t == nullptr) return true;
    if (s == nullptr || t == nullptr) return false;
    return s->val == t->val && help(s->left, t->left) && help(s->right, t->right);
}

bool Solution::isSubtree(TreeNode *s, TreeNode *t) {
    if (t == nullptr) return true;
    if (s == nullptr) return false;
    bool flag = false;
    isSubtree(s, t, flag);
    return flag;
}

// 代码简化版本
class Solution2 {
public:
    bool isSubtree(TreeNode *s, TreeNode *t);
    bool help(TreeNode *s, TreeNode *t);
};

bool Solution2::help(TreeNode *s, TreeNode *t) {
    if (s == nullptr && t == nullptr) return true;
    if (s == nullptr || t == nullptr) return false;
    return s->val == t->val && help(s->left, t->left) && help(s->right, t->right);
}

bool Solution2::isSubtree(TreeNode *s, TreeNode *t) {
    if (t == nullptr) return true;
    if (s == nullptr) return false;
    return help(s,t) || isSubtree(s->left, t) || isSubtree(s->right, t);
}


