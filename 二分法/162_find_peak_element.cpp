#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums);
};

// 题目中规定
int Solution::findPeakElement(vector<int>& nums) {
    if (nums.size() == 1) return 0;
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[mid+1]) low = mid + 1;
        else high = mid;
    }
    return low;
}
