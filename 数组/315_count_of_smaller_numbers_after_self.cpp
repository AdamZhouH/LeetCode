#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> countSmaller(vector<int>& nums);
	void mergeCount(vector<pair<int,int>>& nums, int start, int end, vector<int>& count);
};

// 这题其实是一个统计逆序对的题目的变形
// 添加一个数组，统计对应位置的逆序数对即可

// 线段树、树状数组亦可以实现
// 给出三种算法的实现

// 1.归并排序统计每个位置处的逆序数
// 归并竟然在最后一个测试用例超时？看来要优化一下
void Solution::mergeCount(vector<pair<int,int>>& nums, int start, int end, vector<int>& count) {
	if (start >= end) return;
	int mid = start + (end - start) / 2;
	mergeCount(nums, start, mid, count);
	mergeCount(nums, mid+1, end, count);
    // 加一个剪枝试试？提交后发现仍然不行
    if (nums[mid].first <= nums[mid+1].first) return;
	vector<pair<int,int>> left(nums.begin()+start, nums.begin()+mid+1);
	vector<pair<int,int>> right(nums.begin()+mid+1, nums.begin()+end+1);
    // 先对每个left数组中的元素统计右侧更小的元素的个数，然后再merge
    // 时间复杂度为O(n)
    int i = 0, j = 0;
    for (;i < left.size() ; i++) {
        while (i < left.size() && j < right.size() && left[i].first > right[j].first) j++;
        count[left[i].second] += j;
    }
    
	i = 0, j = 0;
    int idx = start;
    // 时间复杂度为O(n)
	while (i < left.size() && j < right.size()) {
		if (left[i].first <= right[j].first) nums[idx++] = left[i++];
		else {
			nums[idx++] = right[j++];
            // 应该是这里导致的超时，因为有个for循环，非常耗时，如何优化？
            // for (int k = i; k < left.size(); k++)
			//     count[left[k].second]++;
		}
	}
    while (i < left.size()) nums[idx++] = left[i++];
    while (j < right.size()) nums[idx++] = right[j++];
}

vector<int> Solution::countSmaller(vector<int>& nums) {
	if (nums.empty()) return {};
	if (nums.size() == 1) return {0};
	vector<pair<int,int>> numbers;
    vector<int> count(nums.size(), 0);
	for (int i = 0; i < nums.size(); i++) 
        numbers.push_back({nums[i], i});
	mergeCount(numbers, 0, nums.size() - 1, count);
	return count;
}
