#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int m);
};

// 极大化极小化问题，利用dp求解
// dp[i][j]表示将1-i个数字分解成j组，其中最大子数组和的最小值
// 显然，根据递推关系，有dp[i][j] = min { max(dp[k][j-1], nums[k+1]+nums[k+2]+..nums[j]) } 其中k从j-1取i-1
// 求nums[k+1]+..nums[j]可以用数组前缀和进行优化到O(1)时间复杂度
int Solution::splitArray(vector<int> &nums, int m) {
    int n = nums.size();
    int maxe = INT_MIN;
    vector<long> sum(n+1, 0);
    vector<long> maxele(n+1, 0);
    vector<vector<long>> dp(n+1, vector<long> (m+1, INT_MAX));
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i-1]+nums[i-1];
        dp[i][1] = sum[i];
        maxe = max(maxe, nums[i-1]);
        maxele[i] = maxe;
    }
    //for_each(sum.begin(),sum.end(),[](int v){cout<<v<<' ';});cout << endl;
    //for_each(maxele.begin(),maxele.end(),[](int v){cout<<v<<' ';});cout << endl;
    for (int j = 2; j <= m; j++) {
        for (int i = j; i <= n; i++) {
            if (i == j) { dp[i][j] = maxele[i]; continue; }
            for (int k = j-1; k <= i-1; k++)
                dp[i][j] = min(dp[i][j], max(dp[k][j-1], sum[i]-sum[k]));
        }
    }
    return dp[n][m];
}
