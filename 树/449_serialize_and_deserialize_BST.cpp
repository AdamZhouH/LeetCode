#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    string serialize(TreeNode* root);
    TreeNode* deserialize(string data);
};

string Codec::serialize(TreeNode *root) {
    if (!root) return "";
    ostringstream out;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        auto n = q.front(); q.pop();
        if (!n) { out << "#,"; }
        else {
            out << n->val << ',';
            q.push(n->left); q.push(n->right);
        }
    }
    return out.str();
}

TreeNode *Codec::deserialize(string data) {
    if (data.empty()) return nullptr;
    for (auto &c: data) if (c == ',') c = ' ';
    istringstream in(data);
    queue<TreeNode *> q; // 辅助存放当前的根结点
    string tmp; in >> tmp;
    TreeNode *root = new TreeNode(stoi(tmp));
    q.push(root);
    string left, right;
    while (in >> left >> right) {
        TreeNode *lchild = left == "#" ? nullptr : new TreeNode(stoi(left));
        TreeNode *rchild = right == "#" ? nullptr : new TreeNode(stoi(right));
        q.front()->left = lchild; q.front()->right = rchild;
        q.pop();
        if (lchild) q.push(lchild);
        if (rchild) q.push(rchild);
    }
    return root;
}
// 注意题目中实际上给出的树是BST，并不是普通的一棵树，因此考虑利用BST的搜索性质，中间节点大于左子树节点并小于右子树节点
// 实际上可以通过分别得到先根遍历和中根遍历的结果，然后根据两个序列可以反推会之前的BST，这样做也可以
// 我这里给出的是更一般的做法
