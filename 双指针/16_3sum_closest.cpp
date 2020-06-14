#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ans = 1000000;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size()-2; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            for (int j = i+1, k = nums.size()-1; j < k;) {
                if (j > i+1 && nums[j] == nums[j-1]) {j++;continue;}
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == target) return target;
                ans = abs(ans-target) > abs(sum-target) ? sum : ans;
                if (sum > target) k--;
                else j++;
            }
        }
        return ans;
    }
};
