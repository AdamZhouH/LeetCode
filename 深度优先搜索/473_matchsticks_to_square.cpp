#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    bool makesquare(vector<int>& nums);
    bool dfs(const vector<int> &nums, int i, long A, long B, long C, long D, long edge);
};

// 实际上是将数组中的元素分为四个组，每个组元素之和为正方形的边长
// 每个元素具有四种选择，可以放入任何一个组，为了避免穷尽所有的情况
// 在dfs搜索过程中，注意剪枝，当一个元素超过了边长时，不能放入任何一个组
// 此时肯定不能组成合理的四个组，返回失败，为此我们先将数组排序，先放大的元素
// 当搜索到一组成功的分组时，返回true即可，避免后续多余的dfs搜索过程
// dfs搜索过程中一定要注意剪枝，不然容易超时，同时对于不合要求的当前状态，没有必要继续dfs

bool Solution::dfs(const vector<int> &nums, int i, long A, long B, long C, long D, long edge) {
    if (i == nums.size()) {
        if (A==B && B==C && C==D && D==edge) return true;
        else return false;
    }
    if (nums[i] > edge) return false;
    if (A > edge || B > edge || C > edge || D > edge) return false;
    return dfs(nums, i + 1, A+nums[i], B, C, D, edge) ||
           dfs(nums, i + 1, A, B+nums[i], C, D, edge) ||
           dfs(nums, i + 1, A, B, C+nums[i], D, edge) ||
           dfs(nums, i + 1, A, B, C, D+nums[i], edge);
}

bool Solution::makesquare(vector<int> &nums) {
    // 对于一些明显不可能组成正方形的直接排除
    if (nums.size() < 4) return false;
    long sum = accumulate(nums.begin(), nums.end(), 0L);
    if (sum % 4) return false;
    // 将数组元素排序，从大的开始放，从而尽快减枝并且找到合理的组合
    sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
    return dfs(nums, 0, 0L, 0L, 0L, 0L, sum / 4);
}

