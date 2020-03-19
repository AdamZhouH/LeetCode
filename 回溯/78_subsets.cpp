#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums);
    void subsets(vector<vector<int>>& ret, vector<int>& nums, int idx, vector<int>& currset);
};

// 递归然后回溯的典型题
// 求子集，那么nums中每个元素都可以选择放在子集中或者不放子集中，然后剩下的元素递归
// 为了减少空间复杂度，currset是以引用方式传递，因此，为了保证不影响其他递归，应该采用回溯的思路

vector<vector<int>> Solution::subsets(vector<int> &nums) {
    vector<vector<int>> ret;
    if (nums.empty())
        return ret;
    vector<int> currset;
    subsets(ret, nums, 0, currset);
    return ret;
}

void Solution::subsets(vector<vector<int>>& ret, vector<int>& nums, int idx, vector<int>& currset) {
    if (idx >= nums.size()) {
        ret.push_back(currset);      // 完成了一个子集的选取
        return;
    }
    // 递归两种情况：选择当前元素，不选择当前元素(注意在选择当前元素返回后，将当前元素pop出currset，避免影响不选择当前元素的递归情况)
    currset.push_back(nums[idx]);
    subsets(ret, nums, idx + 1, currset);
    currset.pop_back();
    subsets(ret, nums, idx + 1, currset);
}

int main(void) {
    vector<int> nums;
    int val;
    while (cin >> val)
        nums.push_back(val);    
    Solution solu;
    auto ret = solu.subsets(nums);
    for (auto &v : ret) {
        for (auto val : v)
            cout << val << ' ';
        cout << endl;
    }
    return 0;
}