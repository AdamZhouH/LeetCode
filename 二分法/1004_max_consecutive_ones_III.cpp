#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

// 解题思路思考：
// 1.二分查找
// 2.滑动窗口
// 涉及一些常见的算法思想：前缀和（本质上是一种动态规划的优化方法，空间换时间）
//
// 1.二分查找思路
// 需要尽可能连续的1的子数组，考虑一段[left, right]内的数组元素，如果K的个数不少于区间内的
// 0的个数，显然整个区间都可以变成连续的1的数组，记数组vector<int> p，p[i]表示[0,i]区间内0的个数
// 数组p可以通过动态规划获取，并且数组p显然是一个非递减数组，这样，区间[left, right]内的0的个数
// 就非常方便拿到，为p[right]-p[left-1]，而不用在区间内通过遍历来拿到，前缀和是一种预处理思想
// 满足条件的区间则需要保证 p[right]-p[left-1] <= K，即
// p[left-1] >= p[right] - K
// left取0-n-1，但当left为0，left-1为-1，避免这种情况，求前缀和数组p时，考虑整体右移一位，则需要空出p[0]
// 即p[left] >= p[right] - K，其中left从0-n-1，而right从1-n，并且right始终要>left（left其实是letf-1的整体换元）
// 针对每一个right，都尝试找到最小的left，满足p[left] >= p[right] - K
// 由于p显然是一个非递减数组，因此查找left可以使用二分思路
// C++利用lower_bound查找第一个满足p[left] >= p[right]-K的left，针对每个right，都找到一个left
// 然后取最大的区间长度即可
// 时间复杂度显然为nlogn

class Solution {
public:
    int longestOnes(vector<int> &A, int K);
};

int Solution::longestOnes(vector<int> &A, int K) {
    vector<int> presum(A.size() + 1, 0);
    for (int i = 1; i <= A.size(); i++) {
        presum[i] = presum[i-1] + (A[i-1] == 0 ? 1:0);
    }
    int maxConsecutiveCnt = 0;
    for (int i = 1; i <= A.size(); i++) {
        auto result = lower_bound(presum.begin(), presum.begin() + i, presum[i] - K);
        if (result != (presum.begin() + i)) {
            maxConsecutiveCnt = max(maxConsecutiveCnt, 
                                    static_cast<int>(presum.begin() + i - result));
        }
    }
    return maxConsecutiveCnt;
}

// 2.滑动窗口思路
// p[left] >= p[right] - K
// 右侧是递增函数，那么左侧的满足条件的最小left显然随着right的增加而增加
// 考虑维护一个滑动窗口，当右侧right移动时，同步左侧left移动，找到第一个满足条件的left，也就是最小left
// 然后继续移动right，直到right到达数组最后
// 显然，这种方式的时间复杂度为O(n)，因为最多的情况就是两个指针都完整遍历一次数组
// 空间复杂度为O(1)，
// 首先是两个指针，left和right
// 其次，需要记录一下left，right区间内的0的个数，因此需要两个变量lsum和rsum（实际上是代替了presum数组）
// 分别表示left左侧的0个数和right左侧的0的个数
// right往右边移动，同时更新rsum，并判断当前区间是否是满足条件的区间，直到不满足，让right停下
// 此时移动左侧的left，同时更新lsum，直到满足条件，此时更新一下最大区间长度
// 继续移动右侧right指针，迭代上述过程，直到right指针到达终点
int longestOnes(vector<int> &A, int K) {
    int maxCnt = 0;
    int left = 0, right = 0;
    int lsum = 0, rsum = 0;
    // 实际上这里rsum是包括了right下标自身，而lsum是不包括下标left的
    // 我们要的也是这个效果
    // 针对每个right，都算到了最左边的left，因此答案肯定不会遗漏
    while (right < A.size()) {
        rsum += 1 - A[right];
        while (rsum - lsum > K) {
            lsum += 1- A[left++];
        }
        maxCnt = max(maxCnt, right - left + 1);
        right++;
    }
    return maxCnt;
}
