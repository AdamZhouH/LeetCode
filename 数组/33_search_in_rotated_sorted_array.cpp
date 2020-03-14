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

#define VERSION2020_03_13

#ifndef VERSION2020_03_13
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
#else
/**
 * 另外的思路则是，不直接寻找旋转点，而是直接使用二分查找，但是在二分查找的过程中
 * 由于存在一个旋转点，导致不能根据单一的一个条件，即nums[mid]于target的关系
 * 得到下次二分在左侧区间还是右侧区间，因此还需判断nums[left]和nums[mid]的关系
 * 以及target和nums[mid] nums[left] nums[right]的关系在判断下次查找在左侧还是右侧区间
 * 可能都会用到
 * 具体的情况可以通过画图来体现
*/
class Solution {
public:
	int search(vector<int> &nums, int target);
};

int Solution::search(vector<int> &nums, int target) {
	// 由于存在旋转点，需要多个条件确定下一次target的查找区间
	int left = 0, right = nums.size() - 1;
	int mid = 0;
	while (left <= right) {
		mid = left + (right - left) / 2;

		if (target == nums[mid])
			return mid;
		// 根据nums[mid]和nums[left]的情况判断最小值点(旋转点)在哪一侧
		else if (nums[left] <= nums[mid]) {  // 最小值点在右侧
			// 根据target和nums[mid]的关系，判断下次查找在哪一侧

			// 若target > nums[mid]，则在右侧查找
			// 若target < nums[mid] && target >= nums[left]，则在左侧查找
			// 若target < nums[mid] 但是 target <= nums[left]，则仍在右侧查找
			if (target < nums[mid] && target >= nums[left])
				right = mid - 1;
			else
				left = mid + 1;
		} else {  // 最小值点在左侧
			// 若target < nums[mid]，则在左侧查找
			// 若target > nums[mid] && target <= nums[right]，则在右侧查找
			// 若target > nums[mid] 但是 target >= nums[right]，则在左侧查找
			if (target > nums[mid] && target <= nums[right])
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	return -1;
}
#endif

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
