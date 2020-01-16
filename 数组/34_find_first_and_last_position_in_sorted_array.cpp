// 二分查找的进一步拓展
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target);
    int searchLeftBound(vector<int> &nums, int target);
    int searchRightBound(vector<int> &nums, int target);
};

int Solution::searchLeftBound(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target <= nums[mid])
            right = mid - 1;
        else if (target > nums[mid])
            left = mid + 1;
    }
    if (left == nums.size())
        return -1;
    return (nums[left] == target) ? left : -1;
}

int Solution::searchRightBound(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target >= nums[mid])
            left = mid + 1;
        else if (target < nums[mid])
            right = mid - 1;
    }
    if (!left)
        return -1;
    return (nums[left - 1] == target) ? (left - 1) : -1;
}

vector<int> Solution::searchRange(vector<int> &nums, int target) {
    if (nums.empty())
        return {-1, -1};
    return {searchLeftBound(nums, target), searchRightBound(nums, target)};
}

int main(void) {
    vector<int> nums = {1,1,3,5,7,7,7};
    for_each(nums.begin(), nums.end(), [](int var) { cout << var  << ' ';});
    cout << endl;
    Solution solution;
    int value;
    while (cin >> value) {
        auto ret = solution.searchRange(nums, value);
        cout << "[" << ret[0] << "," << ret[1] << "]" << endl;
    }
    return 0;
}
