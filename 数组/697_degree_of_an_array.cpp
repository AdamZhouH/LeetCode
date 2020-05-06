#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        // 最短连续子数组的长度
        // 1.度相同，即某个数字的频率达到度
        // 2.长度尽可能短
        // 记录频率最大数字的最左侧以及最右侧的下标即可
        // 利用hashmap
        int help[50005][2] = {0};
        int count[50005] = {0};
        int maxdegree = INT_MIN;
        int minlength = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            count[nums[i]]++;
            maxdegree = max(maxdegree, count[nums[i]]);
            if (count[nums[i]] == 1) help[nums[i]][0] = i;
            else help[nums[i]][1] = i;
        }
        if (maxdegree == 1) return 1;
        for (auto val : nums) {
            if (count[val] == maxdegree)
                minlength = min(minlength, help[val][1] - help[val][0] + 1);
        }
        return minlength;
    }
};