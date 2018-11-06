#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;

// 思路很简单，就是利用set不保存重复元素的性质，并且set底层利用RB数实现，因此查找效率非常高
// 先把数组1的元素存放到set中，然后遍历数组2中的元素

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2);
};

vector<int> Solution::intersection(vector<int>& nums1, vector<int>& nums2) {
	vector<int> result;
	// 先进行排序
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());
	// 去重
	auto end_unique1 = unique(nums1.begin(), nums1.end());
	nums1.erase(end_unique1, nums1.end());
	auto end_unique2 = unique(nums2.begin(), nums2.end());
	nums2.erase(end_unique2, nums2.end());
	// 利用set不保存重复元素这个特性
	set<int> s(nums1.begin(), nums1.end());
	for (int i = 0; i < nums2.size(); i++)
		if (s.find(nums2[i]) != s.end())
			result.push_back(nums2[i]);

	return result;
}

int main(void) {
	vector<int> arr1 = {1,2,2,1};
	vector<int> arr2 = {2,2};
	Solution solu;
	vector<int> ret = solu.intersection(arr1, arr2);
	for_each(ret.begin(), ret.end(), [] (int var) { cout << var << ' '; });
	cout << endl;
	return 0;
}