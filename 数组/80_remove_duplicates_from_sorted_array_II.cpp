#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 相比前一个题，本题目的要求则是允许最多出现两次
// 因此加上一个变量用来记录变量出现的次数即可

// 双指针思路
// 一个指针指向不重复数组的最后一个数字（也即是上一个数字）
// 一个指针用来遍历数组元素，指向当前的元素

class Solution {
public:
    int removeDuplicates(vector<int> &nums);
};

int Solution::removeDuplicates(vector<int> &nums) {
    if (nums.size() == 0)
        return nums.size();
    int cnt = 0;
    int i = 0, j = 1;
    while (j < nums.size()) {
        if (nums[j] != nums[i]) {
            nums[++i] = nums[j++]; 
            cnt = 0;
        } else if (cnt == 0) {
            nums[++i] = nums[j++];
            cnt = 1;
        } else {
            j++;
        }
    }
    return i + 1;
}