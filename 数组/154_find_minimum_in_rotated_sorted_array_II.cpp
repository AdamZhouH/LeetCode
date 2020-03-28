#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define OPTIMITION
// The element can repeat in the vector
// 当允许出现重复元素时，具体情况具体分析
// 这种先和左侧元素比较的思路固然可以，但是导致后续需要分析的情况非常多
// 如果先和right的元素比较，那么会简单很多，代码见后
#ifndef OPTIMITION
class Solution {
public:
    int findMin(vector<int>& nums);
    int findMin(vector<int>& nums, int left, int right);
};

int Solution::findMin(vector<int>& nums, int left, int right) {
    int mid;
    int ret = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[left] > nums[mid]) {
            right = mid;     // 这种情况下，可以判断一定存在实际发生过旋转，并且旋转点在左侧
        } else if (nums[left] < nums[mid]) {
            // 仅仅知道left元素更小，无法进一步判断是否存在实际的旋转以及位置，还需要和right元素比
            if (nums[mid] <= nums[right]) {
                ret = nums[left];    // 此时，nums[left]<nums[mid]<=nums[right]，说明整个子数组的有序
                break;
            } else {
                left = mid + 1;  // 此时可以判断断点存在于右侧
            }
        } else {
            // 此时nums[mid]==nums[left]
            if (nums[mid] < nums[right]) {
                ret = nums[left];  // 此时nums[left]<nums[right]数组是非降序的
                break;
            } else if (nums[mid] > nums[right]) {
                left = mid + 1; // 最小值点一定在右侧
            } else {
                // 三者相同时，无法判断，直接线性查找最小值
                ret = nums[left];
                for (int i = left; i <= right; i++) {
                    if (ret > nums[i]) {
                        ret = nums[i];
                    }
                }
                break;
            }
        }
    }
    return ret;
}

int Solution::findMin(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    return findMin(nums, 0, nums.size() - 1);
}
#else
class Solution {
public:
    int findMin(vector<int>& nums);
};

int Solution::findMin(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    // 首先和右侧元素比较
    int left = 0, right = nums.size() - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (nums[mid] > nums[right])
            left = mid + 1;
        else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            right--;
        }
    }
    return nums[left];
}
#endif


int main(void) {
    vector<int> nums;
    string line;
    Solution slu;
    while (getline(cin, line)) {
        istringstream input(line);
        int val;
        while (input >> val) {
            nums.push_back(val);
        }
        cout << slu.findMin(nums) << endl;
        nums.clear();
    }
    return 0;
}



