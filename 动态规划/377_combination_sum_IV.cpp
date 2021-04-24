class Solution {
public:
    // 暴力递归的思路是很好想到的
    // 直接每次递归时候选择一个数字，直到剩下的和为0，那么找到一组，如果剩下的和小于0
    // 则说明这种组合没有找到
    // 但是这种递归显然会有非常多重复的子问题
    // 比如重复计算某个和的组合个数
    // 因此这里应该用动态规划的方式打表
    // 注意找一下递推方程
    // f(n) = f(n-a[0])+f(n-a[1])+...f(n-a[m])
    // f(n)表示和为n的组合个数
    // 这个方程的意思表示的是假定组合中最后一个数字可能是a[0] a[1] ... a[m]
    // 但是需要注意的是f(n-a[i])中n-a[i]>=0
    // 注意，f(0)表示和为0，应该也算一种
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> record(target+1, 0);
        record[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i-nums[j] >= 0 && 
                    record[i-nums[j]] <= INT_MAX - record[i]) {
                    record[i] += record[i-nums[j]];
                }
            }
        }
        return record[target];
    }
};
// 感觉这道题有点针对C++，因为 record[i-nums[j]] <= INT_MAX - record[i])这条件
// 不加的话，直接overflow，但是这个不太合逻辑，个人感觉，但从解题思路来看，找不到加这个条件的理由
// 只是因为题目限制了，保证结果一定在int32范围内