#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef OPITIMZE
class Solution {
public:
    int rob(vector<int>& nums);
};

int Solution::rob(vector<int> &nums) {
    if (nums.size() <= 0)
        return 0;
    if (nums.size() == 1)
        return nums[0];
    vector<int> dp(nums.size(), 0);
    dp[0] = nums[0];
    int maxMoney = dp[0];
    for (int i = 1; i < dp.size(); i++) {
        if (i == 1) {
            dp[i] = nums[i];
        } else {
            int temp = nums[0];
            for (int j = 0; j <= i - 2; j++) {
                temp = max(temp, dp[j]);
            }  
            dp[i] = temp + nums[i];
        }
        maxMoney = max(maxMoney, dp[i]);
    }
    return maxMoney;
}
#else
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0], dp[1] = max(nums[0], nums[1]);
        int ret = dp[1];
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
            ret = max(ret,dp[i]);
        }
        return ret;
    }
};
#endif

int main(void) {
    vector<int> nums;
    int val;
    while (cin >> val) {
        nums.push_back(val);
    }
    Solution solu;
    cout << solu.rob(nums) << endl;
    return 0;
}
