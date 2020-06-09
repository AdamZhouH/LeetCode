#include <vector>
using namespace std;

class Solution {
public:
    // 先给出暴力dp解法，时间复杂度达到了O(n^2)
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();
        int maxlen = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < dp.size(); i++) {
            for (int j = i-1; j >= 0; j--) {
                if (nums[j] >= nums[i]) continue;
                else dp[i] = max(dp[i], dp[j] + 1);
            }
            maxlen = max(maxlen, dp[i]);
        }
        return maxlen;
    }
};