// LeetCode 26
// 删除有序数组中的重复元素，要求空间复杂度为O(1)

// 思路
// 思路还是比较清晰的，一个指针遍历数组元素
// 另一个指针处理过后的不重复元素的下一个可插入位置
// 遍历指针遇到不重复元素，则不重复指针处插入这个元素
// 同时，记得保存之前的元素，判断当前元素和之前元素是否重复

// 注意处理边界条件
// 注意处理边界条件
// 注意处理边界条件
// 空数组和大小为1的数组

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int removeDuplicates(vector<int> &nums);
}; 

int Solution::removeDuplicates(vector<int> &nums) {
        if (nums.empty())
        return 0;
	if (nums.size() == 1)
		return 1;

	int preNum = nums[0];
	int currIndex = 1;
	int length = nums.size();
	int insertableIndex = 1;

	for (; currIndex < length; currIndex++) {
		if (nums[currIndex] == preNum)
			continue;
		else {
			preNum = nums[currIndex];
			nums[insertableIndex++] = preNum;
		}
	}

	return insertableIndex;
}

int main(void) {
	vector<int> vec = {1,1,2,2,3,4,5,5,5,6};
	Solution solution;
	cout << solution.removeDuplicates(vec) << endl;
	return 0;
}
