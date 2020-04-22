#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 暴力和双指针，先用暴力，再用双指针滑动窗口
    int numberOfSubarrays(vector<int>& nums, int k);
};

// 暴力超时
/*
int Solution::numberOfSubarrays(vector<int>& nums, int k) {
    if (nums.empty() || k > nums.size()) return 0;
    vector<int> dp(nums.size(), 0);
    vector<int> help;

    dp[0] = (nums[0] % 2 ? 1:0);
    if (dp[0] >= k) help.push_back(0);

    for (int i = 1; i < dp.size(); i++) {
        dp[i] = dp[i-1] + (nums[i] % 2 ? 1:0);
        if (dp[i] >= k) help.push_back(i);
    }
    int ans = 0;
    for (auto index : help) {
        for (int j = 0; j <= index; j++) {
            int temp = dp[index] - dp[j] + (nums[j]%2 ? 1:0);
            if (temp == k) {ans++;}
            else if (temp < k) break;
        }
    }
    return ans;
}
*/

// 双指针滑动窗口尝试一下
// 先从第一个奇数元素开始，找到k个奇数的满足条件的连续子数组，然后分别计算左右指针左右两侧的偶数元素个数
// 然后将ij都往右滑动，并且移动到下一个元素都为奇数的状态

int Solution::numberOfSubarrays(vector<int>& nums, int k) {
    if (nums.empty() || k > nums.size()) return 0;
    int i = 0, j = 0, count = 0;
    while (i < nums.size() && nums[i]%2 == 0) i++;
    if (i >= nums.size()) return 0;
    j = i;
    while (j < nums.size() && count < k) {
        if (nums[j] % 2) {
            count++;
            if (count == k)
                break;
        }
        j++;
    }
    if (count < k) return 0;

    int ans = 0;
    while (i <= j && j < nums.size()) {
        // cout << i << ' ' << j << ' ';
        // 分别计算i左侧，j右侧的偶数元素个数
        int counti = 0, countj = 0;
        int k = i-1;
        while (k >= 0 && nums[k]%2 == 0) k--;
        counti = i - k;
        k = j+1;
        while (k < nums.size() && nums[k]%2 == 0) k++;
        countj = k - j;
        // 计算当前区间可以组成的优美子数组个数
        ans += counti * countj;
        // 将ij移动到下一个合法的都指向奇数的状态
        if (k >= nums.size()) break;
        else j = k;
        i = i + 1;
        while (i <= j && nums[i]%2 == 0) i++;
        if (i > j) break;
    }
    return ans;
}

// 非常不优雅的做法，实际上可以用一个数组，记录每个奇数元素出现的下标位置
// 那么这个数组的第i个元素和第i+k-1个元素之间就恰好存在k个奇数，并且可以计算两个位置的左侧以及右侧
// 的前一个奇数的位置，从而知道间隔了多少个偶数
//
// 其实，还有一个前缀和的思想，利用hashmap，类似于two sum的做法，更加快速地求解
// dp数组，dp[i]表示[0-i]的元素中，奇数元素的个数
// 那么对于i<=j，满足dp[j]-dp[i-1]=k的一对(i,j)就是一个合法的优美子数组
//
// 以下分别给出两种做法
//
//
int numberOfSubarrays(vector<int>& nums, int k) {
    if (nums.empty() || nums.size() < k) return 0;
    vector<int> dp;
    // 由于需要知道第一个元素之前的奇数元素的位置以及最后一个元素之后的奇数位置
    // 实际上均不存在，为了避免条件判断，前后都设置一个哨兵元素，并从1开始遍历
    dp.push_back(-1);
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i]&0x1)
            dp.push_back(i);
    }
    dp.push_back(nums.size());
    int ans = 0;
    for (int i = 1; i + k < dp.size(); i++) {
        ans += (dp[i] - dp[i - 1]) * (dp[i + k] - dp[i + k - 1]);
    }
    return ans;
}
// 方法二：前缀和
int numOfSubarrays2(vector<int> &nums, int k) {
    
}
