#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {val = _val;}
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ret;
        if (!root) return ret;
        queue<Node*> q;
        q.push(root);
        vector<int> currnodes;
        while (!q.empty()) {
            currnodes.clear();
            int size = q.size();
            while (size--) {
                auto node = q.front(); q.pop();
                currnodes.push_back(node->val);
                for (auto child : node->children)
                    q.push(child);
            }
            ret.push_back(currnodes);
        }
        return ret;
    }
};
