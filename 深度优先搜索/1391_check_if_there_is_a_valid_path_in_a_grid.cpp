class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid);
};

// 走过的格子不能再走，先BFS，可以把所有可达的格子都找到，如果可达格子中包含了最后一个格子，那么一定存在路径

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

map<int,set<pair<int,int>>> avaliablePath = {
    {0, {{2,2},{2,3},{2,4},{5,2},{5,3},{5,4},{6,2},{6,3},{6,4}}},
    {1, {{1,1},{1,3},{1,5},{4,1},{4,3},{4,5},{6,1},{6,3},{6,5}}},
    {2, {{2,2},{2,5},{2,6},{3,2},{3,5},{3,6},{4,2},{4,5},{4,6}}},
    {3, {{1,1},{1,4},{1,6},{3,1},{3,4},{3,6},{5,1},{5,4},{5,6}}}
};

bool canPass(vector<vector<int>> &grid, vector<vector<int>> &visited, int x, int y, int parent, int direction) {
    int m = grid.size(), n = grid[0].size();
    if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y]) return false;
    auto p = make_pair(parent, grid[x][y]);
    if (avaliablePath[direction].count(p))
        return true;
    return false;
}

bool Solution::hasValidPath(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int,int>> q;
    q.push({0,0});
    vector<vector<int>> visited(m, vector<int> (n, 0));
    visited[0][0] = 1;
    while (!q.empty()) {
        auto currnode = q.front(); q.pop();
        if (currnode.first == m - 1 && currnode.second == n - 1) return true;
        for (int i = 0; i < 4; i++) {
            int x = currnode.first + dx[i];
            int y = currnode.second + dy[i];
            if (canPass(grid, visited, x, y, grid[currnode.first][currnode.second], i)) {
                visited[x][y] = 1;
                q.push({x,y});
            }
        }
    }
    return false;
}

// 后续补上DFS解法和并查集解法