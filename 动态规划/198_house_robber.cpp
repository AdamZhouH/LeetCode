#include <iostream>
#include <string>
#include <vector>
using namespace std;

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