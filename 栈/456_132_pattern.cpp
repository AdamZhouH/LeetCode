#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 暴力思路，暴力竟然可以过
    // 针对每个元素，往左侧找一个更大的元素，然后继续找一个更小的元素
    // 并且可以保证更小的元素在更大元素的左侧，则说明存在这样的132                             
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) return false;
        for (int i = 2; i < nums.size(); i++) {
            int j = i - 1;
            while (j > 0 && nums[j] <= nums[i]) j--;
            if (j > 0) {
                for (int k = 0; k < j; k++) {
                    if (nums[k] < nums[i]) return true;
                }
            }
        }
        return false;
    }
};