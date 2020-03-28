#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <sstream>
using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums);
private:
    int findMin(vector<int> &nums, int start, int end);
};

int Solution::findMin(vector<int> &nums, int start, int end) {
    int mid;
    int ret = 0;
    // 寻找最小元素时，可能最后走到一个完全升序的子序列中（由于元素均不相同，可以很好判断）
    while (start <= end) {
        if (nums[start] <= nums[end]) {
            ret =  nums[start];   // 递增的子数组，最小元素即首元素
            break;
        }
        mid = start + (end - start) / 2;
        if (nums[start] < nums[mid]) {
            start = mid + 1;
        }else if (nums[start] > nums[mid]) {
            end = mid;
        } else {
            ret = min(nums[start], nums[end]);
            break;
        }
    }
    return ret;
}

int Solution::findMin(vector<int> &nums) {
    assert(!nums.empty());
    if (nums.size() == 1) return nums[0];
    return findMin(nums, 0, nums.size() - 1);
}

int main(int argc, char *argv[]) {
    vector<int> nums;
    string line;
    Solution slu;
    while (getline(cin, line)) {
        istringstream input(line);
        int val;
        while (input >> val)
            nums.push_back(val);
        cout << slu.findMin(nums)  << endl;
        nums.clear();
    }
    return 0;
}
