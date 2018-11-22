#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

// 返回下一个二叉搜索树中下一个最小的数
// 时间复杂度要求为O(1)，空间复杂度为O(h)，其中h为树的高度，也即是空间复杂度为O(logn)
// 按照题目时空复杂度的要求，应该缓存一部分数据，用于快速的查找过程
// 思路：
// 题目要求next的时间复杂度为O(1)，指的是均摊下来的时间复杂度，并不要求具体到每一步都是O(1)复杂度
// 考虑二叉树的有序序列可以利用中序遍历获得，但是中序遍历显然不能一次性都遍历完成然后缓存下来，这样不复合时间复杂度要求
// 这一题其实可以看做类似于二叉树中序遍历的非递归的做法，利用栈保存接下来要遍历的节点
// 因此联想到利用栈结构，模拟二叉树中序遍历思想
// 每次遍历，找接下来树中的最小元素，就是中序遍历中的下一个元素
// 考虑第一个元素，那就是整棵树的最小元素，显然，从根开始，一直左走下去，直到没有左子树，同时，路径上每个左节点入栈
// 那么当前栈顶元素就是第一个最小的元素，看似这一步的时间复杂度为logn，但实际上接下来的next操作会均摊这一步的时间复杂度
// 同时，因为只是保存路径中的左节点，因此，空间复杂度也满足要求
// 当前栈顶，就是即将访问的下一个元素
// 访问元素时候，栈顶出栈，然后模拟中序遍历，需要把当前栈顶的右子树的根及其一直往左走的路径入栈，如果当前节点没有右子树
// 那么实际上直接出栈即可，这就分担了之前的节点的时间复杂度

class BSTIterator {
public:
    BSTIterator(TreeNode *root);
    bool hasNext();
    int next();    
private:
    statck<TreeNode *> stk;
};

BSTIterator::BSTIterator(TreeNode *root) {
    TreeNode *tmp = root;
    while (tmp) {
        stk.push(tmp);
        tmp = tmp->left;    
    }
}

bool BSTIterator::hasNext() {
    return !stk.empty();
}

int BSTIterator::next() {
    TreeNode *p = stk.top();
    stk.pop();
    TreeNode *tmp = p->right;
    int ans = p->val;
    while (tmp) {
        stk.push(tmp);
        tmp = tmp->left;
    }
    return ans;
}
