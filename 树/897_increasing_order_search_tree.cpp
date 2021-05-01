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
    // 类似于递归过程中构建一个双向链表，之不过链表的left指针均为空
    // 同样，按照中序遍历的思路来构建双链表
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode *head = nullptr, *tail = nullptr;
        travel(root, head, tail);
        tail->left = nullptr;
        return head;
    }
    
    void travel(TreeNode *root, TreeNode *&head, TreeNode *&tail) {
        if (root) {
            travel(root->left, head, tail);
            if (head == nullptr) {
                head = tail = root;
            } else {
                tail->left = nullptr;
                tail->right = root;
                tail = root;
            }
            travel(root->right, head, tail);
        }    
    }
};