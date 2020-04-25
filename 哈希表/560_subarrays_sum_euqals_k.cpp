#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k);
};

int Solution::subarraySum(vector<int> &nums, int k) {
	unordered_map<long, int> dp;
	long sum = 0;
	dp[0] = 1;
	int ans = 0;
	for (int i = 0; i < nums.size(); i++) {
		sum += nums[i];
		ans += dp[sum-k];
		dp[sum]++;
	}
	return ans;
}