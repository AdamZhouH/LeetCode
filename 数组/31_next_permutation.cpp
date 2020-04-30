#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums);
    void reverse(vector<int>& nums, int left, int right);
};

// 找规律题，数组的字典顺序其实就是和字符串的字典序类似，比较当前位置的元素，如果相同则比较下一个位置的元素
// 因此，通过一些简单的例子可以发现，从最后一个数往前走，如果当前元素比前一个元素更大，则将当前元素后面的
// 元素排序，然后选择从当前元素开始（包括当前元素）往后的序列中找第一个比这个序列前端的前一个元素大的元素，与之交换即可
void Solution::reverse(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    while (left < right) {
        int tmp = nums[left];
        nums[left] = nums[right], nums[right] = tmp;
        left++, right--;
    }
}

void Solution::nextPermutation(vector<int>& nums) {
    if (nums.size() <= 1) return;
    int i = nums.size() - 1;
    for (; i >= 0; i--) {
        if (i > 0 && nums[i] > nums[i-1]) break;
    }
    if (i > 0) {
        reverse(nums, i, nums.size()-1);
        // 找第一个更大的元素替换num[i-1]即可
        int j = i;
        for (; j < nums.size(); j++)
            if (nums[j] > nums[i-1]) break;
        int tmp = nums[i-1];
        nums[i-1] = nums[j];
        nums[j] = tmp;
    } else {
        reverse(nums, 0, nums.size() - 1);
    }
    return;
}