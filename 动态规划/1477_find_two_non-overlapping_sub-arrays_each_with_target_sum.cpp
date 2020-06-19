#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // 时间换空间，从左往右遍历，计算每个节点左侧和为sum的最短长度
    // 从右往左遍历，计算每个节点右侧的和为sum的最短长度
    // 分治思路，计算以每个节点为分界点时的最短长度和，总体的最短长度即为所求
    // 而快速的计算sum则利用到了前缀和以及用map解决two sum问题的思路
    // 因为sum[i:j] = sum[j]-sum[i-1]，对于每个j判断sum[i]-target是否存在即可
    // 注意要求的是最短长度，因此，还需要记录sum最近出现时候的下标
    int minSumOfLengths(vector<int>& arr, int target) {
        if (arr.empty()) return -1;
        if (target == 0) return 0;
        unordered_map<int, int> presum; presum[0] = -1;
        vector<int> predp(arr.size(), INT_MAX);
        int sum = 0, minlength = INT_MAX;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            if (presum.count(sum - target)) {
                minlength = min(minlength, i-presum[sum-target]);
            }
            presum[sum] = i;
            predp[i] = minlength;
        }
        unordered_map<int, int> sufsum; sufsum[0] = arr.size();
        vector<int> sufdp(arr.size(), INT_MAX);
        sum = 0, minlength = INT_MAX;
        for (int i = arr.size() - 1; i >= 0; i--) {
            sum += arr[i];
            if (sufsum.count(sum - target)) {
                minlength = min(minlength, sufsum[sum-target]-i);
            }
            sufsum[sum] = i;
            sufdp[i] = minlength;
        }
        int mincomsum = INT_MAX;
        for (int i = 0; i < arr.size() - 1; i++) {
            if (predp[i] != INT_MAX && sufdp[i+1] != INT_MAX)
                mincomsum = min(mincomsum, predp[i] + sufdp[i+1]);
        }
        return mincomsum == INT_MAX ? -1 : mincomsum;
    }
};
