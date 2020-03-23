#include <iostream>
#include <vector>
using namespace std;
#define GOODSTYLE

#ifndef GOODSTYPE
class Solution {
public:
    // 偷头不偷尾，偷尾不偷头
    // 两个dp数组
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp1(nums.size() - 1, 0);
        vector<int> dp2(nums.size() - 1, 0);
        // 先计算不选择最后一个房屋的最高金额
        dp1[0] = nums[0];
        int ret = dp1[0];
        int currmax = nums[0];
        for (int i = 1; i < dp1.size(); i++) {
            currmax = max(currmax, nums[i]);
            dp1[i] = (i<2) ? currmax: max(dp1[i-2]+nums[i], dp1[i-1]);
            ret = max(ret, dp1[i]);
        }
        // 再计算不选择第一个房屋的最高金额
        dp2[0] = nums[1];
        ret = max(ret, dp2[0]);
        currmax = nums[1];
        for (int i = 1; i < dp2.size(); i++) {
            currmax = max(currmax, nums[i+1]);
            dp2[i] = (i<2) ? currmax : max(dp2[i-2]+nums[i+1], dp2[i-1]);
            ret = max(ret, dp2[i]);
        }
        
        return ret;
    }
};
#else
// 代码风格更加优化的同类解法
class Solution {
public:
    // 偷头不偷尾，偷尾不偷头
    // 两个dp数组
    int rob(vector<int>& nums);
    int help(const vector<int>& nums);
};

int Solution::help(const vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    vector<int> dp(nums.size(), 0);
    dp[0] = nums[0], dp[1] = max(nums[0], nums[1]);
    int ret = dp[1];
    for (int i = 2; i < dp.size(); i++) {
        dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
        ret = max(ret,dp[i]);
    }
    return ret;
}

int Solution::rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    vector<int> nums1(nums.begin(), nums.end()-1);
    vector<int> nums2(nums.begin()+1, nums.end());
    return max(help(nums1), help(nums2));
}
#endif
