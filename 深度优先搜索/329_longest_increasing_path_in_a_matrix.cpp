// 思路
// 矩阵搜索这类题目，首先想到的是一个搜索，不管是dfs还是bfs
// 考虑这道题，一开始可以想到的方法则是针对每一个点dfs找到从这个点开始的最大路径
// 也即每个方向上，如果此方向上的点比当前节点大，那么递归得到这个方向上的最大路劲长度+1
// 这样dfs四个方向上的点之后，就可以得到当前点开始的最大路径长度
// 但是很显然，如果每个点dfs一次，那么时间复杂度会非常大，并且，从一个点开始，他的最大路径长度的路径中
// 包括了子问题的解，也就是，当前路径是最长的，那么从路径中某个节点开始的最长路径也是同一条
// 因此，子问题重叠，考虑动态规划
// 利用二维dp数组存储(dp[i][j])，表示从ij出发，最长路径的长度
// dp数组初始化为0，然后开始dfs，如果dp[i][j]不为0，那么直接返回这个值
// 这是因为如果不为0，那么之前的遍历肯定把这个子问题解决了（这也是利用dp的原因，降低复杂度）
// 如果为0，说明从这个点开始的最大路径上的所有点都没有计算过（包括子问题），那么按照四个方向
// dfs即可，最后返回dp[i][j]

// 思路想清楚，这道题还是很好写的
// 其实还bfs的方法，以后补充

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix);
    int dfs(vector<vector<int>> &matrix, vector<vector<int>> &dp,int i, int j, int m, int n);
    
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
};


int Solution::longestIncreasingPath(vector<vector<int>> &matrix)  {
    if (matrix.empty())
        return 0;
    int m = matrix.size();
    int n = matrix[0].size();
    
    vector<vector<int>> dp(m, vector<int>(n, 0));
    int maxLen = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maxLen = max(maxLen, dfs(matrix, dp, i, j, m, n));
        }
    }
    return maxLen;
}

int Solution::dfs(vector<vector<int>> &matrix, vector<vector<int>> &dp,int i, int j, int m, int n) {
    if (dp[i][j])
        return dp[i][j];
    int currMax = 0;
    for (int k = 0; k < 4; k++) {
        int idx = i + dx[k];
        int idy = j + dy[k];
        if (idx >= 0 && idx < m && idy >= 0 && idy < n && matrix[idx][idy] > matrix[i][j])
            currMax = max(currMax, dfs(matrix, dp, idx, idy, m, n));
    }
    dp[i][j] = 1 + currMax;
    return dp[i][j];
}