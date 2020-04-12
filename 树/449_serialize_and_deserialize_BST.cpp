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
    // Encodes a tree to a single string.
    string serialize(TreeNode* root);
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data);
};

// DFS BFS 分别实现
// 对于空间压缩，将整数写入4个byte的内存中


