#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k);
};

// 暴力思路：动态规划，滚动数组
// 考虑只有一行的情况，则选择当前行第k小的数字即可
// 如果再加一行，那么组合起来可以很多，当前行的没个数字和上一行的没个数字作为一个组合
// 然后取前k个最小数字（不足k个则全部保存）保存，这就是前两行能够组合起来的前k小的和
// 此时再加一行进来，那么前两行的前k小数字分别和当前行的每个元素组合，得到前三行的最小数字组合
// 以此类推
// 类似于滚动数组
// 题目也类似于leetcode求丑数那道题
// 题目保证了数据范围，因此这里暂时不做检查
// 时间复杂度比较大
int Solution::kthSmallest(vector<vector<int>>& mat, int k) {
    int m = mat.size(), n = mat[0].size();
    vector<int> nums = mat[0];
    if (nums.size() > k) nums.resize(k);
    for (int i = 1; i < m; i++) {
        vector<int> tmp;
        for (int j = 0; j < n; j++) {
            for (auto val : nums) tmp.push_back(val+mat[i][j]);
        }
        sort(tmp.begin(), tmp.end());
        if (tmp.size() > k) tmp.resize(k);
        nums.swap(tmp);
    }
    return nums[k-1];
}