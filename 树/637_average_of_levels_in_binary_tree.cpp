#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root);
};

vector<double> Solution::averageOfLevels(TreeNode *root) {
    vector<double> ret;
    if (!root) return ret;
    queue<TreeNode *> q;
    q.push(root);
    double currSum = 0;
    while (!q.empty()) {
        int size = q.size();
        int tmp = size;
        currSum = 0;
        while (tmp--) {
            auto node = q.front(); q.pop();
            currSum += node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ret.push_back(currSum / size);
    }
    return ret;
}
