#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <queue>
using namespace std;

// 思路
// 利用双端队列，左边右边都可以插入或者删除，从而模拟行为
// 当前层次如果是正向遍历，那么先push_front左子树然后push_front右子树
// 当前层次如果是反向遍历，那么先push_front右子树然后push_front左子树
// 具体流程画图便可以直到，每次遍历时候，应该先push左子数还是右子树
// 总体来世，每次push使用的都是push_front这个接口
// 实际上可以优化一下，不使用deque，毕竟deque的push_front操作开销还是大一些
// 可以直接使用queue即可，插入和取出的时候注意下次序，或者直接使用栈也是可以的
// 因为每次都是取front队头的那个节点

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root);
};

vector<vector<int>> Solution::zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> ret;
    if (!root)
        return ret;
    deque<TreeNode *> currLevel;
    deque<TreeNode *> nextLevel;
    currLevel.push_back(root);
    bool isReverse = false;
    vector<int> nodeVal;

    while (!currLevel.empty() || !nextLevel.empty()) {
        while (!currLevel.empty()) {
            TreeNode *node = currLevel.front();
            currLevel.pop_front();
            nodeVal.push_back(node->val);
            if (isReverse) {
                if (node->right)
                    nextLevel.push_front(node->right);
                if (node->left)
                    nextLevel.push_front(node->left);
            } else {
                if (node->left)
                    nextLevel.push_front(node->left);
                if (node->right)
                    nextLevel.push_front(node->right);
            }
        }
        ret.push_back(nodeVal);
        nodeVal.clear();
        currLevel = nextLevel;
        nextLevel.clear();
        isReverse = ( isReverse == true ? false : true);
    }
    return ret;
}
