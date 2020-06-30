#include <vector>
#include <map>
#include <set>
using namespace std;

// 这道题的关键点在于，遍历每个节点时，需要记录节点的编号，这个编号直接按照完全二叉树
// 去生成，左儿子编号为父节点编号*2，右儿子编号为父节点*2+1
// 至于遍历的方法，既可以使用深度遍历，也可以使用层序遍历
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        map<unsigned long long, set<unsigned long long>> nodes;
        dfs(root, 1, 1, nodes);
        unsigned long long ms = 1;
        for (auto &s: nodes) {
            ms = max(ms, (*(s.second.rbegin())-*(s.second.begin()) + 1));
        }
        return ms;
    }
    
    void dfs(TreeNode *root, unsigned long long level, unsigned long long id, map<unsigned long long, set<unsigned long long>> &nodes) {
        if (!root) return;
        nodes[level].insert(id);
        dfs(root->left, level+1, 2*id, nodes);
        dfs(root->right, level+1, 2*id + 1, nodes);
    }
};


class Solution2 {
public:
	int widthOfBinaryTree(TreeNode* root) {
		if (!root) return 0;
		queue<pair<unsigned long long, TreeNode *>> q;
		unsigned long long ms = 1;
		q.push({1, root});
		while (!q.empty()) {
			int sz = q.size();
			int currleft = 0;
			while (sz--) {
				auto p = q.front(); q.pop();
				if (currleft == 0) currleft = p.first;
				if (sz == 0) ms = max(ms, p.first - currleft + 1);
				if (p.second->left) q.push({p.first*2, p.second->left});
				if (p.second->right) q.push({p.first*2+1, p.second->right});
			}
		}
		return ms;
	}
};
