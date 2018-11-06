// LeetCode 55
// 跳格子游戏

// 分析题目意思，A[i]的值表示在这个格子处可以继续往前跳的最大步数
// 我们假定可以跳到最后一个格子结点，那么必然从第一个格子出发，途径的每个格子都必须是可达的
// 很容易反证法可以证明，所以，首先明确一点的是，如果可达，那么之前的每个格子结点也是可达的
// 很显然，如果每个格子都可达，那么最后一个格子也必须是可以达到的
// 因此，两者是互为充分必要条件

// 贪心思路：
// 从第一个格子开始，我们计算当前阶段，最远可达的结点在哪里，如果到达了最后一个
// 很显然，问题解决，必然是可达
// 如果最远可达还没有到最后结点，我们继续迭代，同时维持一个变量，保存当前可达最远结点的位置
// 第二个结点，先判断这个结点是否是可达的，也即比较这个结点的位置和之前计算的最远可达结点的位置的关系
// 如果当前结点不是可达，那么break，否则，更新最远可达结点
// 按上述过程迭代
// 迭代的边界条件
// 1. 当前结点不可达到
// 2. 当前最远可达结点已经超过了最后一个结点的位置

#include <vector>
#include <iostream>
using namespace std;

class Solution {
    public:
        bool canJump(vector<int> &nums);
};

bool Solution::canJump(vector<int> &nums) {
    int i = 0;
    int currRemote = nums[i];
    for (; i < nums.size(); i++) {
        if (i > currRemote || currRemote >= nums.size() - 1)
            break;
        if (currRemote < nums[i] + i)
           currRemote = nums[i] + 1; 
    }
    if (currRemote >= nums.size() -1)
        return true;
    return false;
}

int main(void) {
    int val;
    vector<int> nums;
    Solution solution;
    while (cin >> val)
        nums.push_back(val);
    cout << (solution.canJump(nums) > 0 ? "true" : "false") << endl;
    return 0;
}