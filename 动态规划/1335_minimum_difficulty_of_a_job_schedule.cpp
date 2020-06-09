#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d);
};

// 典型dp题
// 将JobDifficulty中的数组按顺序分割成d组，每一组的最大值相加，求这个和的最小值
// 最大值的最小值(极大化极小化问题)
// dp[i][j]表示将前i天分成j组得到的最小值
// dp[i][j] = min{ dp[k][j-1] + max{jobDifficulty[k+1-1], jobDifficulty[k+2-1],...,jobDifficulty[i]} }
// 由于每天必须保证一项任务的完成，因此每天至少要分配到一个任务，那么dp[i][j]中，i>=j
// 同时注意，上述的dp递推公式中k从j-1开始取到i-1
// 上述问题分析清楚后，代码就很好写了，还有注意求max{jobDifficulty[k+1-1], jobDifficulty[k+2-1],...,jobDifficulty[i]}是的优化
int Solution::minDifficulty(vector<int>& jobDifficulty, int d) {
    if (jobDifficulty.size() < d) return -1;
    vector<vector<int>> dp(jobDifficulty.size()+1, vector<int> (d+1, INT_MAX));
    vector<int> sum(jobDifficulty.size()+1, 0);
    int currmax = INT_MIN;
    for (int i = 1; i <= jobDifficulty.size(); i++) {
        sum[i] = sum[i-1] + jobDifficulty[i-1];
        currmax = max(currmax, jobDifficulty[i-1]);
        dp[i][1] = currmax;
    }
    for (int j = 2; j <= d; j++) {
        for (int i = j; i <= jobDifficulty.size(); i++) {
            if (i == j) { dp[i][j] = sum[i]; continue; }
            int curr = jobDifficulty[i-1];
            for (int k = i-1; k >= j-1; k--) {
                curr = max(curr, jobDifficulty[k+1-1]);
                dp[i][j] = min(dp[i][j], curr + dp[k][j-1]);
            }
        }
    }
    return dp[jobDifficulty.size()][d];
}
