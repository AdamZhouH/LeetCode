#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target);
};

// 如果一开始想不到动态规划的具体状态转移方程，可以先考虑dfs求解的情况
// dfs过程中，考虑当前房子i可以涂的颜色j，以及当前构成k个社区
// 同时，必须知道前一个房子的信息，因为颜色的相同或者不同会导致社区个数k的变化
// 很显然，当前的选择导致三个状态的变化，i j k
// 那么用动态规划也就清楚了子问题应该如何定义
// dp[i][j][k]表示前i个房子，并且最后也就是第i个房子涂第j种颜色，构成k个社区的最小花费
// 是一个三维的dp问题，但是这也是通过思考dfs过程能够想出来的，所以遇到这类问题不要慌张
// 现在考虑状态转移过程
// 很显然，第i个房子如果和前一个房子相同颜色，那么花费就是dp[i-1][j][k]+cost[i][j]
// 如果第i个房子和前一个房子不同颜色，那么当第i个房子涂色后，导致社区个数加1，从中选择花费最小的颜色
// 即min{dp[i-1][j'][k-1]} 其中，j'从1到n并且!=j
// 注意还有考虑到房子如果本身就有颜色，那么不能再涂其他颜色，因此，如果这个房子的颜色不是j
// 那么dp[i][j][k]显然是无解，直接置为最大值INT_MAX即可，表示花费无穷大
// 综合上述考虑
// dp[i][j][k] = INT_MAX if houses[i-1] != 0 && houses[i-1] != j
// dp[i][j][k] = min{dp[i-1][j][k], min{dp[i-1][j'][k-1] | 1<=j'<=n and j'!=j}} + houses[i-1]==0?cost[i-1][j-1]:0 if houses[i-1] == 0
// 以上为状态转移方程，考虑到方便计算，可以将dp[i][j][k]的顺序调换为dp[i][k][j]这样便于自底向上填充dp数组
// 考虑边界情况，当i==1时，若没有颜色，则每种颜色都可以填填充，若有颜色，则只有唯一解
int Solution::minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
	vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(target+1, vector<int>(n+1, INT_MAX)));
    for (int j = 1; j <= n; j++) { 
        if (houses[0] == 0) dp[1][1][j] = cost[0][j-1];
        else if (houses[0] == j) dp[1][1][j] = 0;
    }
    for (int i = 2; i <= m; i++) {
        for (int k = 1; k <= i && k <= target; k++) {
            for (int j = 1; j <= n; j++) {
                if (houses[i-1] != 0 && houses[i-1] != j) continue;
                int currmin = INT_MAX;
                for (int r = 1; r <= n; r++) {
                    if (r == j) currmin = min(currmin, dp[i-1][k][r]);
                    else currmin = min(currmin, dp[i-1][k-1][r]);
                }
                currmin = currmin == INT_MAX ? INT_MAX :
                    (houses[i-1] == 0 ? currmin + cost[i-1][j-1] : currmin);
                dp[i][k][j] = currmin;
            }
        }
    }
    // find minimum of dp[m][target][1] dp[m][target][2] ... dp[m][target][n]
    int ans = INT_MAX;
    for (int j = 1; j <= n; j++) ans = min(ans, dp[m][target][j]);
    return ans == INT_MAX ? -1 : ans;
}

