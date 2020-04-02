#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void sortColors(vector<int> &nums);
};
// 先用计数排序搞定
void Solution::sortColors(vector<int> &nums) {
    vector<int> help(3, 0);
    for (auto var : nums)
        help[var]++;
    int idx = 0;
    for (int i = 0; i < help.size(); i++) {
        while (help[i]--) nums[idx++] = i;
    }
}

// 三指针（荷兰国旗问题）
void swap(vector<int> &nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

// p2用来遍历，指向当前元素
// p1则表示0的左边界，而p1指向的则是下一个0可插入位置
// p2表示2的左边界，而p2指向的是下一个2可以插入的位置
void sortColors(vector<int> &nums) {
    int p1 = 0, p2 = 0, p3 = nums.size() - 1;
    while (p2 <= p3) {
        // 遍历数组，将0放在p1左边，2放在p1右边，1则不管
        if (nums[p2] == 0) {
            // 从左侧交换过来的元素是已经遍历过的，非0即1，因此curr放心地+1
            swap(nums, p1, p2);
            p1++, p2++;
        } else if (nums[p2] == 2) {
            // 从右侧交换过来的元素是没有遍历过的，因此curr不走
            swap(nums, p2, p3);
            p3--;
        } else {
            p2++;
        }
    }
}
