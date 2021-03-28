#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// class BSTIterator {
// public:
//     BSTIterator(TreeNode* root) {
//         travel(root);
//     }
    
//     int next() {
//         return elems[idx++];
//     }
    
//     bool hasNext() {
//         return idx < elems.size();
//     }
// private:
//     void travel(TreeNode *root) {
//         if (root) {
//             travel(root->left);
//             elems.push_back(root->val);
//             travel(root->right);
//         }
//     }

//     int idx = 0;
//     vector<int> elems;
// };

// 上述方法空间复杂度过大，为O(n)，并且需要预先遍历整棵树
// 改用栈的思路来做
// 用栈保存中序遍历的部分结果
// 那么空间复杂度就是O(h)，其中h为树的高度
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            stk.push(root);
            root = root->left;
        }
    }
    
    int next() {
        TreeNode *curr = stk.top(); stk.pop();
        if (curr->right) {
            TreeNode *node = curr->right;
            while (node) {
                stk.push(node);
                node = node->left;
            }
        }
        return curr->val;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
private:
    stack<TreeNode *> stk;
};