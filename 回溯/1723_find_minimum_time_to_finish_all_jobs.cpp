#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 可以想到的是一个动态规划的思路
// dp[n][k]表示前n个工作分配给k个人，能够得到的最大工作时间的最小值
// 则有dp[n][k] = min{
//          max{dp[n-1][k-1], jobs[n]},
//          max{dp[n-2][k-1], jobs[n-1]+jobs[n]},
//          ...
//          max{dp[k-1][k-1], jobs[k]+..jobs[n]}
//     }

class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k);
};

int Solution::minimumTimeRequired(vector<int> &jobs, int k) {
    vector<vector<int>> dp(jobs.size() + 1, vector<int>(k + 1, 0));    
}