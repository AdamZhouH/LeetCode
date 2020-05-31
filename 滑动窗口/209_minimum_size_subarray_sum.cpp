#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    // 滑动窗口题
    // 直接双指针即可，逐步扩展右侧指针，直到和满足条件
    // 然后缩减左指针，不断更新最短长度，直到和不满足条件
    // 由于双指针保证了求解到了以当前右侧为结尾的最短子数组
    // 并且遍历到了所有的合法的右侧，因此一定可以找到最短子数组
    // 双指针一般都是因为可以直接排除一些无需计算的子问题，从而降低了时间复杂度
    // 使用双指针时，考虑是否能够排除一些子问题的计算，可以，那么双指针算法就有正确性保证
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty()) return 0;
        int currSum = 0, i = 0, j = 0;
        int minLen = INT_MAX;
        while (j < nums.size()) {
            while (currSum < s && j < nums.size()) currSum += nums[j++];
            while (i < j && currSum >= s) minLen = min(minLen, j-i), currSum -= nums[i++];
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};
