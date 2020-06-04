#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums);
};

// 类似滚动数组的思想(动态规划)
// 两次遍历，输出数组不视为额外空间的话，其实很好写，直接用输出数组先记录前缀积
// 然后第二次从后往前遍历，用一个变量suffix记录当前后缀积，并不断更新输出数组
// 这样只需要一个额外变量
vector<int> Solution::productExceptSelf(vector<int>& nums) {
    vector<int> ret(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++) {
        ret[i] = (i == 0) ? 1: ret[i-1] * nums[i-1];
    }
    int suffix = 1;
    for (int i = nums.size() - 1; i >= 0; i--) {
        ret[i] *= suffix;
        suffix *= nums[i];
    }
    return ret;
}