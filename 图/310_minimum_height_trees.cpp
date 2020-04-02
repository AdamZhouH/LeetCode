#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;

/**
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges);
    pair<int, int> getHeight(int n, int root, map<int, set<int>> &graph); 
};

// 暂时不确定贪心算法的准确性，先暴力搜索一下
// BFS求树高，因为每个节点的邻居节点很容易知道，因此用bfs方便点
// 在Leetcode提交，果断超时了，显然不能暴力求解
pair<int, int> Solution::getHeight(int n, int root, map<int, set<int>> &graph) {
    queue<int> q;
    q.push(root);
    // 注意，由于给定的是无向图，必须保证已经在树中的节点之后不再入队
    vector<int> visited(n, 0);
    visited[root] = 1;
    int level = 0;
    while (!q.empty()) {
        int cnt = q.size();
        while (cnt--) {
            int val = q.front(); q.pop();
            for (auto i : graph[val])
                if (!visited[i]) {
                    visited[i] = 1;
                    q.push(i);
                }
        }
        level++;
    }
    return {root, level - 1};
}

vector<int> Solution::findMinHeightTrees(int n, vector<vector<int>> &edges) {
    if (n == 1) return { 0 };
    if (n == 2) return { 0, 1 };
    // 获取每个节点的邻居节点
    map<int, set<int>> graph;
    for (auto &vec : edges) {
        graph[vec[0]].insert(vec[1]);
        graph[vec[1]].insert(vec[0]);
    }
    vector<pair<int, int>> result;
    for (int i = 0; i < n; i++)
        result.push_back(getHeight(n, i, graph));
    sort(result.begin(), result.end(), [](const pair<int,int> &lhs, const pair<int,int> &rhs) { return lhs.second < rhs.second; });
    vector<int> ret = { result[0].first };
    for (int i = 1; i < result.size(); i++) {
        if (result[i].second == result[0].second) ret.push_back(result[i].first);
        else break;
    }
    return ret;
}*/

// 给出正确解法
// 两种思路：
//      1. 寻找图中路径最长的一对节点，路径上的中点即为所求（即找到图的直径，然后取直径的中点）
//         从任何一个节点开始，bfs遍历，最后一个入队的节点一定是直径上的一个端点
//      2. 拓扑排序观点，将所有当前度为1的节点删去，直到剩下1或2个节点，即为所求

// 拓扑排序解法
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges);
};

vector<int> Solution::findMinHeightTrees(int n, vector<vector<int>> &edges) {
    // 处理两种特殊情况
    if (n == 1) return {0};
    if (n == 2) return {0,1};
    // 计算节点的度以及记录每个节点的邻居节点，同时，如果一个节点已经被入队，则degree为<= 0，可以起到在后续BFS
    // 过程中，帮助判断节点是否已经被删除的作用
    // 邻接矩阵存储无向图
    vector<int> degree(n, 0);
    map<int, set<int>> graph;
    for (auto &vec : edges) {
        degree[vec[0]]++, degree[vec[1]]++;
        graph[vec[0]].insert(vec[1]);
        graph[vec[1]].insert(vec[0]);
    }
    // BFS遍历，将所有度为1的节点都入队，同时记录剩余节点数，当剩余节点少于3个时，剩余节点即为所求
    queue<int> q;
    int left = n;
    for (int i = 0; i < degree.size(); i++) {
        if (degree[i] == 1) {
            q.push(i);
            degree[i] = -1;
            left--;
        }
    }
    while (left > 2) {
        // 将node所有邻接节点的度-1，若此邻接节点时度为1，则入队
        int cnt = q.size();
        while (cnt--) {
            int node = q.front(); q.pop();
            for (auto adj : graph[node]) {
                degree[adj]--;
                if (degree[adj] == 1) {
                    q.push(adj);
                    degree[adj] = -1;
                    left--;
                }
            }
        }
    }
    // 将剩余节点返回
    vector<int> ret;
    for (int i = 0; i < degree.size(); i++) 
        if (degree[i] >= 0) ret.push_back(i);
    return ret;
}














