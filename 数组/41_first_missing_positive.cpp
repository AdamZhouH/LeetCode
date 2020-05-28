#include <iostream>
#include <vector>
using namespace std;

// 比较巧妙的hash碰撞法
// 首先，如果不是1-nums.size()之间的数字直接丢弃，因为在nums
// 中出现的只能是1-nums.size()之间的数字，如果重复出现也不考虑
// 其次，将数字放到正确的位置上，数字i应该放在下标为i-1的位置处
// 第二次遍历，直接得到不存在的最小正数即可
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // nums中的数如果在1到nums.size()之间则可以保存下来，否则不用理会
        for (int i = 0; i < nums.size(); i++) {
            // <=0 >nums.size() 或者重复出现，则不用理会
            // 否则放置到正确的位置上
            while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i]-1]) {
                int tmp = nums[nums[i]-1];
                nums[nums[i]-1] = nums[i];
                nums[i] = tmp;
            }
        }
        for (int i = 0; i < nums.size(); i++) 
            if (nums[i] != i+1) return i+1;
        return nums.size()+1;
    }
};
