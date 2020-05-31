#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums);
};

// 这题在之前更大一个元素的基础上，将数组改成了循环数组，意味着这个数如果之前的某个数字也更大
// 那么也应该算存在一个更大的数字(循环搜索)
// 这种循环的话，可以用拼接的思路，在原数组后拼接一个相同的数组
// 利用单调栈的时候注意注意下标取模即可
vector<int> Solution::nextGreaterElements(vector<int>& nums) {
    vector<int> ret(nums.size(), -1);
    if (nums.empty()) return ret;
    int n = nums.size();
    vector<int> tmp = nums; for (auto val: tmp) nums.push_back(val);
    stack<int> stk; // 单调递减栈，找右侧第一个更大的元素
    for (int i = 0; i < nums.size(); i++) {
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            int idx = stk.top(); stk.pop();
            ret[idx%n] = nums[i%n];
        }
        stk.push(i);
    }
    return ret;
}
