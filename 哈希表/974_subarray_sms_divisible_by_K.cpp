#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K);
};
// 动态规划的方法很好写，但是时间复杂度O(n^2)
// 一般是用前缀和的方法解决类似的问题
// 这里sum[j] - 5*k = sum[i]主要是确定k能够取哪些值
// 观察到i在j之前，因此sum[j] - 5*k的最小值不小于之前的最小和，最大值不大于之前的最大值
// 用两个辅助变量，记录prev的和的最大值和最小值即可
// 结果仍然是超时，这是因为，两个while循环的时间复杂度可能很大
// 最好采用另外一种思路，只要sum[j]与sum[i]的mod K的值相同即可，避免while循环
// 因此，unordered_map中保存的key应该是sum mod K的余数
/*
int subarraysDivByK(vector<int>& A, int K) {
    unordered_map<long, long> record;
    record[0] = 1;
    long sum = 0;
    long ret = 0;
    long prevax = 0, prevmin = 0;
    for (auto val : A) {
        sum += val;
        int p = 0;
        while (sum - p*K >= prevmin) { if (record.count(sum-p*K)) ret += record[sum-p*K]; p++; }
        p = -1;
        while (sum - p*K <= prevmax) { if (record.count(sum-p*K)) ret += record[sum-p*K]; p--; }
        record[sum]++;
        if (sum > prevmax) prevmax = sum;
        if (sum < prevmin) prevmin = sum;
    }
    return ret;
}
*/
// 这个思路Python是可以过的，但是C++不行，因为对于负数取余的情况，C++会得到负数
// 处理一下，如果余数为负数，则转换为正数，这里有一点比较坑爹((sum%K)+K)%K
int Solution::subarraysDivByK(vector<int>& A, int K) {
    unordered_map<long, long> record;
    long sum = 0; record[0] = 1;
    int ans = 0;
    for (auto val: A) {
        sum = sum + val;
        int mod = (sum >= 0) ? sum % K : ((sum % K)+K)%K;
        if (record.count(mod)) ans += record[mod];
        record[mod]++;
    }
    return ans;
}
