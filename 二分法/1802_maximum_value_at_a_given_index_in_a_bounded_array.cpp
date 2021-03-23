class Solution {
public:
    // 这道题应该用二分思路来写
    // 1.首先可以观察到，利用贪心算法，当确定了index处的最大值
    // 我们要使得总和最小的办法就是，让两边每次递减1，但是因为nums[i]为正整数
    // 那么最小也必须是1
    // 2.二分思路，可以观察到，随着index处的最大值的增加，那么sum的下限也在增加
    // 显然是一个递增关系，因此我们考虑找到最后一个使得sum小于等于给定sum的最大index处的值
    // 显然，left侧取1，right侧我们直接取给定sum
    // 二分查找右侧边界，注意细节问题
    
    int maxValue(int n, int index, int maxSum) {
        int left = 1, right = maxSum;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long sum = getMinSum(index+1, mid) + getMinSum(n-index, mid) - mid;
            if (sum <= maxSum) 
                left = mid + 1;
            else 
                right = mid - 1;
        }
        return left-1;
    }
    
    long getMinSum(int n, long val) {
        long sum = 0;
        if (val > n) {
            sum = (val + val - n + 1) * n / 2;
        } else {
            sum = (val + 1) * val / 2 + n - val; 
        }
        return sum;
    }
    // long getMinSum(int index, int n, int maxValue) {
    //     long sum = maxValue;
    //     // 超时，看来这里不能用遍历计算和
    //     // 抽一个数学公式出来计算
    //     // for (int i = 1; i+index < n; i++) {
    //     //     sum += (maxValue-i > 1) ? maxValue-i : 1;
    //     // }
    //     // for (int i = 1; index-i >= 0; i++) {
    //     //     sum += (maxValue-i > 1) ? maxValue-i : 1;
    //     // }
    //     //return sum;
    // }
};
