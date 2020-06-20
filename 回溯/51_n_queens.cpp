#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n);
    void dfs(vector<vector<string>> &ret, vector<string> &curr, int idx, vector<vector<int>> &exists, vector<int> &vis, int n);
};

vector<vector<string>> Solution::solveNQueens(int n) {
    vector<vector<string>> ret;
    vector<string> curr(n, string(n, '.'));
    vector<vector<int>> exists;
    vector<int> vis(n, 0);
    dfs(ret, curr, 0, exists, vis, n);
    return ret;
}

void Solution::dfs(vector<vector<string>> &ret, vector<string> &curr, int idx, vector<vector<int>> &exists, vector<int> &vis, int n) {
    if (idx >= n) { ret.push_back(curr); return; }
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
        vis[i] = 1; exists.push_back({idx, i}); curr[idx][i] = 'Q';
        dfs(ret, curr, idx+1, exists, vis, n);
        vis[i] = 0; exists.pop_back(); curr[idx][i] = '.';
    }
}
