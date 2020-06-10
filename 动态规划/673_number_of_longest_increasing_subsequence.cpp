#include <iostream>
#include <string>
#include <vector>


class Solution {
public:
    int findNumberOfLIS(vector<int>& nums);
};

int Solution::findNumberOfLIS(vector<int> &nums) {
    if (nums.size() <= 1) return nums.size();
    vector<int> dp(nums.size(), 1);
    vector<int> dp2(nums.size(), 0); dp2[0] = 1;
    int maxlen = 1;
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] >= nums[i]) continue;
            else dp[i] = max(dp[i], dp[j]+1);
        }
		// 主要是更新在每个点的最大长度时，统计以这个点为结束点的长度为该点处的最大长度的序列的个数
        // 那么直接往前找长度为该点长度-1并且值<当前元素的位置，这些位置的序列个数相加即可
        // 从前往后迭代，具有累加效应
        maxlen = max(maxlen, dp[i]);
        if (dp[i] == 1) dp2[i] = 1;
        else
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && (dp[j] == dp[i] - 1)) dp2[i] += dp2[j];
            }
    }
    if (maxlen == 1) return nums.size();
    int cnt = 0;
    for (int i = 0; i < dp.size(); i++) {
        if (dp[i] == maxlen) cnt += dp2[i];
    }
    return cnt;
}