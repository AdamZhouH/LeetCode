#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int totalNQueens(int n);
    void dfs(int idx, vector<vector<int>> &exists, vector<int> &vis, int n, int &cnt);
};

int Solution::totalNQueens(int n) {
    vector<vector<int>> exists;
    vector<int> vis(n, 0);
    int cnt = 0;
    dfs(0, exists, vis, n, cnt);
    return cnt;
}

void Solution::dfs( int idx, vector<vector<int>> &exists, vector<int> &vis, int n, int &cnt) {
    if (idx >= n) { cnt++; return; }
    for (int i = 0; i < n; i++) {
        if (vis[i] == 1) continue;
        // 判断两个斜方向上是否存在皇后
        bool flag = true;
        for (auto &v: exists) {
            if ((idx-v[0] == v[1]-i)|| (idx-v[0] == i-v[1])) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        // dfs+回溯
        vis[i] = 1; exists.push_back({idx, i});
        dfs(idx+1, exists, vis, n, cnt);
        vis[i] = 0; exists.pop_back();
    }
}
