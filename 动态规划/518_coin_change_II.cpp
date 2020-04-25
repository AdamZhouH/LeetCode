#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <numeric>
using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins);
};

// 显然是一个完全背包问题，使用动态规划思路
// 从第一种硬币开始遍历
// 当前硬币不用、当前硬币用1枚、当前硬币用2枚
// dp[i][j]表示用0-i种硬币凑j元的方案数
// dp[i][j] = dp[i-1][j] + dp[i-1][j-1*coins[i]] + dp[i-1][j-2*coins[i]] + ...
// 上述递推如果直接使用，那么时间复杂度为O(mn^2)，其中m为硬币种类数，n为凑要凑齐的面值，时间复杂度较大
// 利用数学推导可以优化递推公式
// dp[i][j] = dp[i-1][j] + dp[i-1][j-1*coins[i]] + dp[i-1][j-2*coins[i]] + ...
// dp[i][j+coins[i]] = dp[i-1][j+coins[i]] + dp[i-1][j] + dp[i-1][j-1*coins[i]] + ...
// 显然可以得到 dp[i][j+coins[i]] = dp[i-1][j+coins[i]] + dp[i][j]
// 也即递推公式 dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]] 当然，前提是j-coins[i]>=0才有这一项，否则没有这一项
int Solution::change(int amount, vector<int> &coins) {
	if (amount == 0) return 1;
	if (coins.empty()) return 0;
	int n = coins, m = amount;
	vector<vector<int>> dp(n, vector<int> (m+1, 0));
	for (int i = 0; i < n; i++) dp[i][0] = 1;
	for (int j = 0; j <= m; j++) dp[0][j] = (j % coins[0] ? 0:1);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = dp[i-1][j] + (j-coins[i] >= 0 ? dp[i][j-coins[i]]:0);
		}
	}
	return dp[n-1][m];
}