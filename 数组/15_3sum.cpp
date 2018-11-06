// 给定一个数组，给出是否存在数组中三个元素a b c 满足，a+b+c=0
// 存在给出所有的不重复结果，不存在则给出空结果

// 基本思路
// 针对每一个数，从其后面的所有数中找到两个数，和为这个数的相反数字
// 从其后面的所有数中找是为了不重复结果

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <unordered_map>  // 使用multiset，因为存在重复元素
using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum_(vector<int>& nums);
    vector<vector<int>> threeSum(vector<int> &nums);
};

vector<vector<int>> Solution::threeSum_(vector<int> &nums) {
	typedef unordered_multimap<int, int>::iterator Iterator;
	vector<vector<int>> ret;
	set<multiset<int>> result;
	if (nums.size() < 3)
		return ret;
	for (int i = 0; i < nums.size() - 2; i++) {
		int sum = -nums[i];
		unordered_multimap<int, int> numberMap;
		for (int j = i + 1; j < nums.size(); j++)
			numberMap.insert(make_pair(nums[j], j));
		// 开始遍历寻找和为sum的一对数字，找到则插入到result中，同时也要注意重复
		// 因此，对于找到的数字的下标，也要大于当前元素的下标 (从后面找)
		for (int j = i + 1; j < nums.size(); j++) {
			pair<Iterator, Iterator> range = numberMap.equal_range(sum - nums[j]);
			if(range.first != range.second) {
				// 则说明存在这样的数，进一步判断下表是否满足要求
				for (auto it = range.first; it != range.second; it++) {
					if (it->second > j)
						result.insert({nums[i], nums[j], nums[it->second]});
				}
			}
		}
	}
	for (auto &s : result) {
		vector<int> vec;
		for (auto &val : s)
			vec.push_back(val);
		ret.push_back(vec);
	}
	return ret;
}

// 这里使用了 set 的一个特性，不会插入相同的两个key，如果即将要插入的 key 已经存在，则什么也不做
// 从而保证了结果不会重复

vector<vector<int>> Solution::threeSum(vector<int> &nums) {
	if (nums.size() < 3) 
		return vector<vector<int>> ();
	set<vector<int>> result;
	sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size() -2; i++) {
		int sum = 0 - nums[i];
		int j = i + 1, k = nums.size() - 1;
		while (j < k) {
			int currSum = nums[j] + nums[k];
			if (currSum == sum) {
				result.insert({nums[i], nums[j], nums[k]});
				while (j < k && nums[j + 1] == nums[j]) j++;
				while (k > j && nums[k - 1] == nums[k]) k--;
				j++; k--;
			} else if (currSum > sum)
				k--;
			else
				j++;
		}
	}
	return vector<vector<int>> (result.begin(), result.end());
}


int main() {
    vector<int> nums = {-2,0,1,1,2};
    Solution solution;
	vector<vector<int>> result = solution.threeSum(nums);
	for_each(result.begin(), result.end(), [] (const vector<int> &vec) {
		for_each(vec.begin(), vec.end(), [] (int val) {
			cout << val << ' ';
		});
		cout << endl;
	});
}
