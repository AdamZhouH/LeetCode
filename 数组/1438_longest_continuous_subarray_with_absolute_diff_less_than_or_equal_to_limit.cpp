#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <deque>
#include <map>
#include <cmath>
using namespace std;

/**
 * 在数组nums中找到连续最长的数组，保证数组中任意两个元素的绝对值差不超过limit
 * 思路：实际上只要数组中的最大值和最小值的差的绝对值不超过limit那么任意两个元素的
 * 绝对值差也不会超过limit，因此判断一个连续子数组是否满足条件只需要得到子数组当前的最大值和最小值
 * 显然可以用分治法，找到最大元素，目标数组可能在左侧，可能在右侧，或者跨越最大值，比较三者情况即可
 * 但是分治的时间复杂度不够稳定，最差情况下达到O(n^2)，因此可能会超时
 * 需要另外一种思路
 * 这种题目应该可以联想到滑动窗口（在一个数组中，维护当前最大值和最小值，同时要求较低的时间复杂度）
 * 基本的思路如下：
 *      1.从第一个元素为起点，此时左右边界都指向第一个元素，然后开始移动右边界（++j）如果满足条件，则继续向右边扩大窗口
 *      2.直到遇到一个不满足条件的元素，此时应该将左边界i往右移动到适当的位置，哪里是适当的位置呢？
 *        将左边界一直往右移动，每移动一次就计算当前窗口的最大值和最小值，如果满足条件则停止移动，然后继续第一步，移动右边界
 *  因此，题目的关键是实时保存滑动窗口中的最大值和最小值
 *  首先想到可以使用单调队列，这里用两个单调队列，维护滑动窗口的最大值和最小值（一个单调增，一个单调减），思路类似于剑指offer
 *  那道题的单调栈维护方法，因为这里需要判断队列左侧元素是否滑出窗口，因此需要两头都能操作，因此用deque
 *  同时，deque中存放index而不是具体的元素值
 * */
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit);
};

int Solution::longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxdeq, mindeq;
    int left = 0;
    int maxlen = INT_MIN;
    for (int right = 0; right < nums.size(); right++) {
        // 将不可能成为最大元素和最小元素的元素下标分别从两个队列中移除
        while (!maxdeq.empty() && nums[maxdeq.back()] < nums[right]) maxdeq.pop_back();
        while (!mindeq.empty() && nums[mindeq.back()] > nums[right]) mindeq.pop_back();
        maxdeq.push_back(right), mindeq.push_back(right);
        // 判断当前滑动窗口是否满足条件，如果满足则更新maxlen，否则将窗口左侧往右边移动直到满足条件
        // 注意移动边界时，需要将大小队列的不在滑动窗口中的元素的下标都剔除掉
        if (nums[maxdeq.front()] - nums[mindeq.front()] <= limit) {
            maxlen = max(maxlen, right - left + 1);
            continue;
        }
        while (nums[maxdeq.front()] - nums[mindeq.front()] > limit) {
            left++;
            while (!maxdeq.empty() && maxdeq.front() < left) maxdeq.pop_front();
            while (!mindeq.empty() && mindeq.front() < left) mindeq.pop_front();
        }
    }
    return maxlen;
}

// 或者不用双端队列，而用一个map，保存滑动窗口中的数字亦可
int longestSubarray(vector<int>& nums, int limit) {
    map<int,int> record;
    int left = 0, right = 0;
    int maxlen = INT_MIN;
    while (right < nums.size()) {
        record[nums[right]]++;
        // 若当前滑动窗口不满足条件，则一直移动滑动窗口的左侧，直到满足条件的位置
        while (record.rbegin()->first - record.begin()->first > limit) {
            record[nums[left]]--;
            if (record[nums[left]] == 0) 
                record.erase(nums[left]);
            left++;
        }
        maxlen = max(maxlen, right - left + 1);
        right++;
    }
    return maxlen;
}

