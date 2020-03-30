#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>> &grid);
    int nearestDistance(int x, int y, vector<vector<int>> &grid);
};

// 此题是BFS遍历的典型题，找每个海洋cell到陆地的最近距离
// 然后在所有cell的最近距离中找到一个最大值
// 问题的核心就是如何找一个海洋cell到陆地的最近距离
//
// 开始用的DFS，想着从每个海洋cell出发，然后四个方向深度遍历，每遇到一个陆地节点，就停止遍历
// 同时计算当前的陆地和初始海洋位置的距离，并同时将已经访问过的海洋cell置位，避免其他遍历到此的节点再遍历
// 结果发现，深度遍历并不能确定到达某个陆地后，这个路径就是最短距离，因为可能到同一个陆地，可能有很多条路径
// 同时，某条最短路径可能可另一条较长路径共用了路径中的某个海洋cell，而这个被访问过的海洋cell已经被标记visited
// 不能再去访问，因此会错过最短路径，但如果不标记每个访问过的海洋cell，则会导致递归无法停止
//
// 因此这一题应该用BFS来做，想象每个cell是一个graph结构中的一个节点
// 而与之相邻的cell就是当前节点相邻的节点，按照广度优先遍历，相当于以某个海洋cell为中心
// 由中心向四周一圈一圈扩散，如果此时遇到一个陆地节点，那么当前的距离一定是最短的距离，同时可以停止bfs遍历，直接返回距离值
// 针对每个海洋，都找到一个最短距离，然后取最大值即可，同时，也需要设置一个visited数组，因为四个方向都可以走，要避免重复遍历

// 由于需要记录每个节点距离原始节点的曼哈顿距离，这里设置一个数据结构，方便直接获取距离
// 同时设置一个方向数组，方便遍历
struct Node {
    int x, y;
    int dist;
    Node(int a, int b, int c) : x(a), y(b), dist(c) {}
};

int visited[105][105];
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int Solution::nearestDistance(int x, int y, vector<vector<int>> &grid) {
    // 队列辅助BFS遍历，辅助visited数组判断是否已经访问过节点
    queue<Node> q;
    memset(visited, 0, sizeof(visited));
    q.push(Node(x, y, 0));
    // 当前节点已经入队，已经入队的节点不能再入队，visited表示节点是否已经被访问
    visited[x][y] = 1;
    while (!q.empty()) {
        Node node = q.front(); q.pop();
        if (grid[node.x][node.y] == 1) return node.dist;
        for (int i = 0; i < 4; i++) {
            if (node.x + dx[i] >= grid.size() || node.x + dx[i] < 0 || node.y + dy[i] >= grid[0].size() || node.y + dy[i] < 0) continue;
            if (visited[node.x+dx[i]][node.y+dy[i]]) continue;
            q.push(Node(node.x+dx[i], node.y+dy[i], node.dist+1));
            visited[node.x+dx[i]][node.y+dy[i]] = 1;
        }
    }
    return -1; // 没有可达的陆节点则返回-1
}

int Solution::maxDistance(vector<vector<int>> &grid) {
    int ret = -1;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 0) {
                ret = max(ret, nearestDistance(i, j, grid));
            }
        }
    }
    return ret;
}
