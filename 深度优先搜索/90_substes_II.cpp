#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums);
    void subsetsWithDup(vector<int>& nums, int i, vector<int> &currset, set<vector<int>> &ret);
};

void Solution::subsetsWithDup(vector<int>& nums, int i, vector<int> &currset, set<vector<int>> &ret) {
    if (i >= nums.size()) {
        ret.insert(currset);
        return;
    }
    // 选择和不选择，注意回溯
    currset.push_back(nums[i]);
    subsetsWithDup(nums, i+1, currset, ret);
    currset.pop_back();
    subsetsWithDup(nums, i+1, currset, ret);
}

vector<vector<int>> Solution::subsetsWithDup(vector<int>& nums) {
    set<vector<int>> ret;
    vector<int> currset;
    sort(nums.begin(), nums.end());
    subsetsWithDup(nums, 0, currset, ret);
    return vector<vector<int>> (ret.begin(), ret.end());
}

// 上面这种是非常笨和耗时的方法，因为递归过程中没有剪枝，而是通过set数据结构来去重
// 
// 考虑n个元素和n+1个元素的所有子集合的区别（类似动态规划的思路）
// 第n+1个元素在子集中可选或者不选，不选的部分就是n个元素的所有子集
// 选择第n+1个元素的部分就是将n个元素的所有子集都加上第n+1个元素即可，因此都可以不用递归深搜了
// 
// 对于存在重复的元素导致的重复的子集，我们可以先排序，将重复的元素放在一起
// 然后考虑此时，出现重复子集的原因是什么？
// 是因为之前一个元素和当前元素相同，则前一个元素不选择，而选择当前元素的部分，和前一个元素被选择当前元素不选择
// 这部分的子集合是重复的，因此想办法避免掉这些重复的子集合
// 当出现当前元素和前一个元素相同时，我们不能从上一步的所有结果（即ans的0到最后的所有集合）遍历
// 而应该从前一个元素会被选择到的第一个子集合开始，遍历到结尾

vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> ans;
    vector<int> v;
    ans.push_back(vector<int>());
    sort(nums.begin(), nums.end());
    int left = 0, right;
    int len;
    for (int i = 0; i < nums.size(); i++) {
        if (i != 0 && nums[i] == nums[i - 1]) left = ans.size() - len;
        else left = 0;
        right = ans.size();
        len = right - left;
        for (int j = left; j < right; j++) {
            v = ans[j];
            v.push_back(nums[i]);
            ans.push_back(v);
        }
    }
    return ans;
}
