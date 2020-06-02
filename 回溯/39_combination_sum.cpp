#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// 直接回溯就可以
// 其实这里可以不用set，因为保证了其中的元素都不会重复，那么每次凑tareget的时候，只使用当前
// index及其之后的元素，而不是用之前的元素即可避免重复
// 理解为何会出现重复的情况
// 当然无脑set也可以的，但是效率比较低
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target);
    void dfs(set<multiset<int>> &ret, vector<int> &candidates, vector<int> &curr, int sum, int target);
};

vector<vector<int>> Solution::combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ans;
    if (candidates.empty()) return ans;
    set<multiset<int>> ret; vector<int> curr;
    dfs(ret, candidates, curr, 0, target);
    for (auto s: ret) ans.push_back(vector<int>(s.begin(), s.end()));
    return ans;
}

void Solution::dfs(set<multiset<int>> &ret, vector<int> &candidates, vector<int> &curr, int sum, int target) {
    if (sum > target) return;
    if (sum == target) { ret.insert(multiset<int> (curr.begin(), curr.end())); return; }
    for (auto val: candidates) {
        if (val + sum <= target) {
            curr.push_back(val);
            dfs(ret, candidates, curr, sum + val, target);
            curr.pop_back();
        }
    }
}

// 不使用set去重，效率更高
// 但要注意选值的范围只能begin以及之后的元素
class Solution2 {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target);
    void dfs(vector<vector<int>> &ret, vector<int> &candidates, vector<int> &curr, int sum, int target, int begin);
};

vector<vector<int>> Solution2::combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ret;
    if (candidates.empty()) return ret;
    vector<int> curr;
    dfs(ret, candidates, curr, 0, target, 0);
    return ret;
}

void Solution2::dfs(vector<vector<int>> &ret, vector<int> &candidates, vector<int> &curr, int sum, int target, int begin) {
    if (sum > target) return;
    if (sum == target) { ret.push_back(curr); return; }
    for (int i = begin; i < candidates.size(); i++) {
        if (candidates[i] + sum <= target) {
            curr.push_back(candidates[i]);
            dfs(ret, candidates, curr, sum + candidates[i], target, i);
            curr.pop_back();
        }
    }
}