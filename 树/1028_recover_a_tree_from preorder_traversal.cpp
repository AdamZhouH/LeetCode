#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        if (S.empty()) return nullptr;
        vector<pair<int, pair<int, TreeNode *>>> dp; // 记录每个节点的层数以及其节点的指针
        int i = 0;
        while (i < S.size()) {
            int cnt = 0;
            while (i < S.size() && S[i] == '-') cnt++, i++;
            assert(i < S.size() && S[i] != '-');
            int j = i;
            while (j < S.size() && S[j] != '-') j++;
            dp.push_back({stoi(S.substr(i, j-i)), {cnt, nullptr}});
            i = j;
        }
        TreeNode *root = new TreeNode(dp[0].first); dp[0].second.second = root;
        for (int i = 1; i < dp.size(); i++) {
            TreeNode *node = new TreeNode(dp[i].first);
            dp[i].second.second = node;
            // 找到根结点
            int j;
            for (j = i - 1; j >= 0; j--) {
                if (dp[j].second.first + 1 == dp[i].second.first) break;
            }
            if (dp[j].second.second->left) dp[j].second.second->right = node;
            else dp[j].second.second->left = node;
        }
        return root;
    }
};
