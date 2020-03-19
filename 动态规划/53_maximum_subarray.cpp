// 53_maximum_subarray.cpp

// 动态规划，先寻找子问题，然后找到递推公式（状态转移方程）
// 考虑从位置0开始，到位置i并且包含i的最大子序列的和，记为f(i)
// 则，状态转移方程为 f(i + 1) = max(f(i) + arr[i + 1], arr[i + 1])
// 一维情况下的动态规划问题dp[]

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSubArray(vector<int>& nums);
};

int Solution::maxSubArray(vector<int> &nums) {
    if (nums.size() == 1)
        return nums[0];
    int currMaxSum = nums[0];
    int maxSum = nums[0];
    int length = nums.size();
    for (int i = 1; i < length; i++) {
        currMaxSum = max(currMaxSum + nums[i], nums[i]);
        maxSum = max(currMaxSum, maxSum);
    }
    return maxSum;
}