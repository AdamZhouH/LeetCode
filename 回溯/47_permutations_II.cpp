#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums);
    void permuteUnique(vector<int>& nums, int idx, set<vector<int>>& ret);
};

// 简单的暴力方法，使用set对vector<int>进行去重
inline void swap(vector<int>& nums, int i, int j) {int temp = nums[i]; nums[i] = nums[j], nums[j] = temp;}

void Solution::permuteUnique(vector<int>& nums, int idx, set<vector<int>>& ret) {
    if (idx == nums.size() - 1) { ret.insert(nums); return; }
    for (int i = idx; i < nums.size(); i++) {
        swap(nums, i, idx);
        permuteUnique(nums, idx+1, ret);
        swap(nums, i, idx);
    }
}

vector<vector<int>> Solution::permuteUnique(vector<int>& nums) {
    vector<vector<int>> ret;
    if (nums.empty()) return ret;
    set<vector<int>> ans;
    permuteUnique(nums, 0, ans);
    return vector<vector<int>> (ans.begin(), ans.end());
}

// 给出回溯+剪枝的做法，同时，先排序，使得方便剪枝
// 考虑重复出现的原因，是因为当前位置的元素不能重复使用，比如当前元素选择了2，那么同一个循环中的下一次迭代
// 这个位置的元素不能再次选择， 这里就是剪枝的地方
// 因此用一个set<int>来记录即可
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums);
    void permuteUnique(vector<int> nums, int idx, vector<vector<int>>& ret);
};

inline void swap(vector<int>& nums, int i, int j) {int temp = nums[i]; nums[i] = nums[j], nums[j] = temp;}

void Solution::permuteUnique(vector<int> nums, int idx, vector<vector<int>>& ret) {
    if (idx == nums.size() - 1) { ret.push_back(nums); return; }
    set<int> s;
    for (int i = idx; i < nums.size(); i++) {
        if (s.find(nums[i]) != s.end()) continue;
        swap(nums, idx, i);
        permuteUnique(nums, idx+1, ret);
        swap(nums, idx, i);
        s.insert(nums[i]);
    }
}

vector<vector<int>> Solution::permuteUnique(vector<int>& nums) {
    vector<vector<int>> ret;
    if (nums.empty()) return ret;
    sort(nums.begin(), nums.end());
    permuteUnique(nums, 0, ret);
    return ret;
}

