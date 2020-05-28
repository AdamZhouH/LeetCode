#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        // 先计算总和,然后再遍历每个元素即可，实际上只需要两次遍历
        long sum = accumulate(nums.begin(), nums.end(), static_cast<long>(0));
        long prefixSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            long suffixSum = sum - nums[i] - prefixSum;
            if (prefixSum == suffixSum) return i;
            prefixSum += nums[i];
        }
        return -1;
    }
};