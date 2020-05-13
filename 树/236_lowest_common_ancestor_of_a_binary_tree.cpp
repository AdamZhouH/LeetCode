#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
    void findPath(TreeNode *root, TreeNode *p, TreeNode *q, vector<TreeNode*> &currPath, vector<TreeNode*> &pathOfp, vector<TreeNode*> &pathOfq);
};

// 先根遍历找到分别从根结点到p节点和q节点的路径
// 注意回溯
void Solution::findPath(TreeNode *root, TreeNode *p, TreeNode *q, vector<TreeNode*> &currPath, vector<TreeNode*> &pathOfp, vector<TreeNode*> &pathOfq) {
    // 加一个剪枝条件，尽量避免整棵树的遍历
    if (!pathOfp.empty() && !pathOfq.empty()) return;
    if (root == nullptr) return;
    currPath.push_back(root);
    if (root == p) pathOfp = currPath;
    else if (root == q) pathOfq = currPath;
    findPath(root->left, p, q, currPath, pathOfp, pathOfq);
    if (!pathOfp.empty() && !pathOfq.empty()) return;
    findPath(root->right, p, q, currPath, pathOfp, pathOfq);
    currPath.pop_back();
}

TreeNode *Solution::lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    vector<TreeNode*> pathA, pathB, currPath;
    findPath(root, p, q, currPath, pathA, pathB);
    TreeNode *ans = nullptr;
    int i = 0, j = 0;
    while (i < pathA.size() && i < pathB.size()) {
        if (pathA[i] == pathB[i]) ans = pathA[i], i++;
        else break;
    }
    return ans;
}


/***************
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
    //void findPath(TreeNode *root, TreeNode *p, TreeNode *q, vector<TreeNode*> &currPath, vector<TreeNode*> &pathOfp, vector<TreeNode*> &pathOfq);
    void findPath(TreeNode *root, TreeNode *p, vector<TreeNode *> &currPath, vector<TreeNode *> &path);
};

void Solution::findPath(TreeNode *root, TreeNode *p, vector<TreeNode *> &currPath, vector<TreeNode *> &path) {
    if (root == nullptr || !path.empty()) return;
    currPath.push_back(root);
    if (root == p) path = currPath;
    findPath(root->left, p, currPath, path);
    findPath(root->right, p, currPath, path);
    currPath.pop_back();
}



TreeNode *Solution::lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    vector<TreeNode*> pathA, pathB, currPath;
    //findPath(root, p, q, currPath, pathA, pathB);
    findPath(root, p, currPath, pathA);
    currPath.clear();
    findPath(root, q, currPath, pathB);
    TreeNode *ans = nullptr;
    int i = 0, j = 0;
    while (i < pathA.size() && i < pathB.size()) {
        if (pathA[i] == pathB[i]) ans = pathA[i], i++;
        else break;
    }
    return ans;
}
******************/
