#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// 这题的考点：
// 1.可以用堆排序（或者直接用STL中的小根堆来做）
// 2.可以用partition的思想（快排中的partition）

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k);
    int findKthLargest(vector<int>& nums, int begin, int end, int k);
    int partition(vector<int> &nums, int begin, int end);
};

void swap(vector<int>&nums, int a, int b) { int tmp = nums[a]; nums[a] = nums[b]; nums[b] = tmp; }
// 写partition一定要注意边界情况
int Solution::partition(vector<int> &nums, int begin, int end) {
    if (begin == end) return begin;
    int pivot = nums[begin];
    int i = begin - 1, j = begin;
    for (; j <= end; j++) {
        if (nums[j] <= pivot) {
            swap(nums, i+1, j);
            i++;
        }
    }
    swap(nums, begin, i);
    return i;
}
int Solution::findKthLargest(vector<int>& nums, int begin, int end, int k) {
    int ret = partition(nums, begin, end);
   if (ret == k) {return nums[ret];}
    if (ret < k) return findKthLargest(nums, ret+1, end, k);
    else return findKthLargest(nums, begin, ret-1, k);
}

int Solution::findKthLargest(vector<int>& nums, int k) {
    return findKthLargest(nums, 0, nums.size()-1, nums.size()-k);
} 

// 写一个堆实现
int findKthLargest(vector<int> &nums, int k) {
    // 第k大，找前k大的，用小大小为k的小根堆比较方便
    priority_queue<int, vector<int>, greater<int>> q;
    for (auto val: nums) {
        if (q.size() < k) q.push(val);
        else {
            if (val > q.top()) {
                q.pop();
                q.push(val);
            }
        }
    }
    return q.top();
}


