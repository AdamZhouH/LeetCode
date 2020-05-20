#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


class Solution {
public:
    int getMoneyAmount(int n)
};

// 首先不能使用二分思路去做，因为和二分没啥关系，目标数字在任何一个位置都能出现
// 并且每次失败时候的代价也不一样，这题只能用动态规划，类似扔鸡蛋的问题
// 扔鸡蛋是要求F层内确定某个临街楼层的最坏情况下的最少搜索次数，这题有点类似
// 确定[1:n]内，找到某个值的最坏情况下的最少现金值，前者限定了鸡蛋个数，而这一题没有限定搜索次数
// 解法类似，关键是抽象出本题的子问题，考虑第一次搜索选择了[1:n]中的某个数字k，考虑最坏情况下需要的金额
// 如果数字k比目标数字更大，则在左侧搜索，否则应该在右侧搜索，因为是最坏情况，我们选择需要金额更大的一侧
// 取max{左侧，右侧} + k
// 而第一次选择的位置可能是从1到n的任何一个值，因此有
// 
// dp[1][n] = min{max{dp[1][k-1], dp[k+1][n]} + k} 其中k从1取到n
// 更一般，我们有 dp[i][j]表示当查找[i:j]范围内的数字需要的至少的现金数量
// 则dp[i][j] =  min{max{dp[i][k-1], dp[k+1][j]} + k} 其中k从i取到j
// 但是这个dp公式不能从上到下，从左到右计算，因为如果从上到下，从左到右，那么当j很大时dp[k+1][j]还是未知的
// 考虑从下往上计算，也就是i从n开始，从左往右计算，那么dp[k+1][j]肯定已经计算到了
// 还有一点必须注意，i<=j，dp[i][j]中如果i>j，实际上是没有意义的，不用理会
int Solution::getMoneyAmount(int n) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++) {
			int mincost = INT_MAX;
			for (int k = i + 1; k < j; k++)
				mincost = min(mincost, max(dp[i][k-1], dp[k+1][j]) + k);
			mincost = min(mincost, dp[i+1][j] + i);
			mincost = min(mincost, dp[i][j-1] + j);
			dp[i][j] = mincost;
		}
	}
	return dp[1][n];
}

// 利用记忆化搜索写一下

class Solution2 {
public:
    int getMoneyAmount(int n);
    int getdp(int i, int j, vector<vector<int>> &dp);
};

int Solution2::getMoneyAmount(int n) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
    return getdp(1,n,dp);
}

int Solution2::getdp(int i, int j, vector<vector<int>> &dp) {
    if (dp[i][j] != -1) return dp[i][j];
    if (i == j) { dp[i][j] = 0; return 0; }
    int minCost = INT_MAX;
    for (int k = i+1; k < j; k++)
        minCost = min(minCost, max(getdp(i,k-1,dp), getdp(k+1,j,dp)) + k);
    minCost = min(minCost, getdp(i+1,j,dp) + i);
    minCost = min(minCost, getdp(i,j-1,dp) + j);
    dp[i][j] = minCost;
    return dp[i][j];
}
