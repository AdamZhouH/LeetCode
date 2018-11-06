#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;

// 和上一道题类似，但是重复出现的元素需要计算在两个数组中公共出现的次数
// 并加以记录
// 思路
// 考虑先排序元素，然后找到size更小的那个数组，从这个开始遍历
// 查找这个数组的元素在第一个数组中是否存在，不存在则继续，存在则分别计数
// 找到两者分别出现的次数，取最小值就是公共出现的次数，作为结果
// 这里，并不需要去重

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
};

vector<int> Solution::intersect(vector<int>& nums1, vector<int>& nums2) {
	vector<int> result;

	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());

	auto f = [&result] (vector<int>& lhs, vector<int>& rhs) {
		for (auto iter1 = lhs.begin(); iter1 != lhs.end(); ) {
			auto ret = find(rhs.begin(), rhs.end(), *iter1);
			if (ret == rhs.end()) {
				iter1++;
				continue;
			} else {
				int var = *iter1;
				int count1 = 0, count2 = 0;
				while (iter1 != lhs.end() && *iter1 == var) { count1++; iter1++; }
				while (ret != rhs.end() && *ret == var) { count2++; ret++; }
				
				for (int i = 0; i < ((count1 < count2 ? count1 : count2)); i++)
					result.push_back(var);
			}
		}
	};

	if (nums1.size() < nums2.size())
		f(nums1, nums2);
	else
		f(nums2, nums1);
	return result;
}

int main(void) {
	vector<int> arr1 = {1,2,2,1};
	vector<int> arr2 = {2,2};
	Solution solu;
	vector<int> ret = solu.intersect(arr1, arr2);
	for_each(ret.begin(), ret.end(), [] (int var) { cout << var << ' '; });
	cout << endl;
	return 0;
}