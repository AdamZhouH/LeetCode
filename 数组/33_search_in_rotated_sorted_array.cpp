// 时间复杂度要求log(n)级别，因此需要借鉴二分查找的思想实现算法
// 题目要求中说明了不存在重复元素，因此问题更加简单些
// 思路
// 1.利用二分法找到旋转点，也即是数组中的最小元素所在的位置
// 2.在旋转点两侧的数组中分别利用二分查找，寻找最小元素

// 题目中假定了数组中不存在相等的元素，因此这道题还是比较好写的

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class Solution {
public:
	int findRotationPoint(vector<int> &nums);
	int binarySearch(vector<int> &nums, int low, int high, int target);
	int search(vector<int> &nums, int target);

};

int Solution::search(vector<int> &nums, int target) {
	if (nums.empty())
		return -1;
	if (nums.size() == 1)
		return (nums[0] == target) ? 0 : -1;
	int rotationPoint = findRotationPoint(nums);
	/* 实际上这一段可以优化
	int ret = binarySearch(nums, 0, rotationPoint - 1, target);
	if (ret == -1)
		return binarySearch(nums, rotationPoint, nums.size() - 1, target);
	return ret;
	*/
	if (nums[rotationPoint] == target)
		return rotationPoint;
	else if (nums[rotationPoint] < target && target <= nums[nums.size() - 1])
		return binarySearch(nums, rotationPoint + 1, nums.size() - 1, target);
	else
		return binarySearch(nums, 0, rotationPoint - 1, target);
	return -1;
}

int Solution::findRotationPoint(vector<int> &nums) {
	int left = 0;
	int right = nums.size() - 1;
	int mid;
	// 寻找旋转点
	while (left <= right) {
		int mid = left + (right - left) / 2;
		// 首先判断是否是递增数列，旋转点为0（即没有旋转的特殊情况）
		if (nums[left] <= nums[mid] && nums[mid] <= nums[right])
			return left;
		// 二分查找旋转点
		if (nums[mid] > nums[left])
			left = mid + 1;
		else if (nums[mid] < nums[left])
			right = mid;
		else if (nums[mid] == nums[left])
			break;
	}
	return (nums[left] > nums[right]) ? right : left;
}

int Solution::binarySearch(vector<int> &nums, int low, int high, int target) {
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (nums[mid] == target)
			return mid;
		else if (nums[mid] > target)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int main(int argc, char *argv[]) {
	vector<int> arr;
	string line;
	while (getline(cin, line)) {
		Solution solu;
		istringstream input(line);
		int var;
		while (input >> var) {
			arr.push_back(var);
		}
		int target = arr[arr.size() - 1];
		arr.pop_back();
		cout << "位置为: " << solu.search(arr, target) << endl;
		arr.clear();
	}
	return 0;
}
