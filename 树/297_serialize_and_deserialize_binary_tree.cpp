#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// #define DFS
#define BFS
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) { }
};

class Codec {
public:
    string serialize(TreeNode *root);
    TreeNode *deserialize(string data);
};

// 之前做的时候，想到利用前序遍历和中序遍历的思路来反序列化，但是忽略了元素的重复导致的问题
// 出现重复元素则无法保证反序列化的二叉树的唯一性，因此这种方法无法解决问题
// 实际上可以利用二叉树层次遍历或者深度优先遍历来实现，如果其中的某种遍历，保存了null节点的信息
// 是可以反序列化为原来的二叉树的（单独的层次遍历或者深度优先遍历无法恢复原始二叉树是因为没有
// 保存之前的null节点信息）
// 给出DFS和BFS两种解法

#ifdef DFS
void help(string &ret, TreeNode *root) {
    if (!root) {
        ret += "null ";
        return;
    }
    ret += to_string(root->val) + " ";
    help(ret, root->left);
    help(ret, root->right);
}

string Codec:: serialize(TreeNode *root) {
    string ret;
    if (!root) return ret;
    // 按先序遍历递归完成序列化
    help(ret, root);
    return ret;
}

TreeNode *help(queue<string>& q) {
    if (q.empty()) return nullptr;
    string rootval = q.front();
    q.pop();
    if (rootval == "null") return nullptr;
    TreeNode *root = new TreeNode(stoi(rootval));
    root->left = help(q);
    root->right = help(q);
    return root;
}

TreeNode *Codec::deserialize(string data) {
    if (data.empty()) return nullptr;
    queue<string> q;
    string str;
    istringstream input(data);
    while (input >> str) q.push(str);
    return help(q);
}

#endif

#ifdef BFS
// 按照层序遍历的顺序来存放所有的元素
string Codec::serialize(TreeNode *root) {
    if (!root) return "";
    queue<TreeNode *> q;
    q.push(root);
    string ret;
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        if (node) {
            q.push(node->left);
            q.push(node->right);
            ret += to_string(node->val) + " ";
        } else {
            ret += "null ";
        }
    }
    return ret;
}

TreeNode *Codec::deserialize(string data) {
    if (data.empty()) return nullptr;
    queue<string> elems;
    istringstream input(data);
    string str;
    while (input >> str) elems.push(str);
    // 层次遍历构建树时，需要知道当前节点的根结点，因此需要用辅助数据结构保存之前构建好的根
    // 这里使用一个队列来保存之前构建好的可能是之后的元素的根的节点
    queue<TreeNode *> help;
    // 先构建整棵树的根
    str = elems.front(); elems.pop();
    TreeNode *root = new TreeNode(stoi(str));
    help.push(root);
    while (!elems.empty()) {
        TreeNode *node = help.front();
        help.pop();
        // 从elems中获取当前node的左儿子 
        str = elems.front(); elems.pop();
        if (str != "null") {
            TreeNode *child = new TreeNode(stoi(str));
            node->left = child;
            help.push(child);
        }
        // 获取右儿子
        if (elems.empty()) break;
        str = elems.front(); elems.pop();
        if (str != "null") {
            TreeNode *child = new TreeNode(stoi(str));
            node->right = child;
            help.push(child);
        }
    }
    return root;
}
#endif


int main(void) {
    TreeNode *a = new TreeNode(2);
    TreeNode *b = new TreeNode(3);
    TreeNode *c = new TreeNode(3);
    TreeNode *d = new TreeNode(4);
    c->left = a, c->right = d, a->left = b;
    Codec  slu;
    string s1 = slu.serialize(c);
    TreeNode *rebuild = slu.deserialize(s1);
    string s2 = slu.serialize(rebuild);
    cout << s1 << '\n' << s2 << endl;
    return 0;
}


