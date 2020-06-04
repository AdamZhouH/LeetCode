#include <vector>
#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    string largestNumber(vector<int>& cost, int target);
};

// 很明显是一个完全背包问题，使用动态规划来做，dp[i][j]表示用1-i数字，在target为j的情况下，能组成的最大整数
// 时间超限(TIL)
struct Cmp {
    bool operator()(const string &lhs, const string &rhs) {
        if (lhs.empty() && rhs.empty()) return false;
        if (lhs.size() != rhs.size()) return lhs.size() > rhs.size();
        else return lhs > rhs;
    }
};

Cmp cmp;

string Solution::largestNumber(vector<int> &cost, int target) {
    int m = cost.size(), n = target;
    vector<vector<string>> dp(m+1, vector<string>(target+1,""));
    string ret;
    for (int i = 1; i <= n; i++) {
        if (i % cost[0] == 0 && i / cost[0] >= 1) 
            dp[1][i] = string(i/cost[0], '1');
        if (cmp(dp[1][i], ret))
            ret = dp[1][i];
    }
    for (int i = 2; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; j - k*cost[i-1] >= 0; k++) {
                if (j - k*cost[i-1] > 0 && dp[i-1][j-k*cost[i-1]].empty()) continue;
                else {
                    if (cmp(string(k,i+'0')+dp[i-1][j-k*cost[i-1]], dp[i][j]))
                        dp[i][j] = string(k,i+'0')+dp[i-1][j-k*cost[i-1]];
                }
            }
        }
    }
    return dp[m][n].empty() ? "0":dp[m][n];
}

// 上述而为dp超时了TLE，因此要进行优化，其实也可以用一维dp来解决
// dp[i]表示target为i的情况下的最大整数，则对于dp[i+1]，考虑整数字符串的最后一个数字，可以分别是1-9
// dp[i] = max{dp[i-cost[k]]+k+'0'} 其中，i-cost[k]>=0即可
class Solution2 {
public:
    string largestNumber(vector<int>& cost, int target) {
    vector<string> dp(target+1, "");
    for (int i = 1; i <= target; i++) {
        for (int j = 1; j <= 9; j++) {
            if ((i-cost[j-1] > 0 && dp[i-cost[j-1]].empty()) || i-cost[j-1] < 0) continue;
            if (cmp(dp[i-cost[j-1]]+string(1, j+'0'), dp[i])) dp[i] = dp[i-cost[j-1]]+string(1, j+'0');
        }
    }
    return dp[target].empty() ? "0":dp[target];
}
};
