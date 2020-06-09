#include <unordered_set>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    int minJump(vector<int>& jump);
};

// 利用bfs分别搜索到每一步可以到达的位置的最小距离(这里的距离指的是按弹簧的次数)
int Solution::minJump(vector<int>& jump) {
    int cnt = 0; // 计步
    unordered_set<int> vis;
    queue<int> q; q.push(0); vis.insert(0);
    int currmax = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto node = q.front(); q.pop();
            if (node >= jump.size()) return cnt;
            // 这段直接超时，因为如果从0开始，其实很多节点已经走到过，不需要从0开始枚举，应该从当前还没有到达过的节点开始枚举
            // 因此用一个坐标来记录当前可达的最远坐标
            for (int j = currmax + 1; j < node; j++) {
                if (!vis.count(j)) {
                    vis.insert(j);
                    q.push(j);
                }
            }
            if (!vis.count(node+jump[node])) { vis.insert(node+jump[node]); q.push(node+jump[node]); }
            currmax = max(currmax, node);
        }
        cnt++;
    }
    return -1;
}
