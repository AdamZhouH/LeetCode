#include <iostream>
#include <vector>
#include <string>

#define FSPTR 1

// O(1)空间复杂度下，原址移出数组中和val的值相同的元素
// 因为题目说明了顺序可以是乱序的，因此考虑双指针
// 左边指针，指向第一个和val相同的值
// 然后和最后一个元素交换交换，同时数组长度-1（释放最后一个元素）

// 解法二：
// 利用快慢指针
// 第一个块指针用于遍历数组元素
// 第二个慢指针用于插入非val值的元素，也即指向可以插入非val元素的位置
// 快指针指向数组当前元素
// 慢指针始终指向当前可以放置非val元素的位置，开始时候，快慢指针是同步的
// 当快指针遇到了val元素时候，慢指针停止走，指向这个val元素（val元素可以视为空元素，供下一个非val元素插入）
// 而快指针继续走，当快指针指向的元素为非val元素，则插入慢指针指向的那个位置，然后慢指针也可以往前移动一步
// 每遇到一个val元素，快慢指针就相差一步，相当于整体往左平移了一个元素
// 当快指针全部遍历完元素时，则处理完全部的元素了（val元素全部被挪动到了数组的尾部）

using namespace std;

class Solution {
	public:
		int removeElement(vector<int> &nums, int val);
};

#ifdef FSPTR // 快慢指针
int Solution::removeElement(vector<int> &nums, int val) {
	int i = 0, j = 0;
	for (; j < nums.size(); j++) {
		if (nums[j] != val) {
			nums[i] = nums[j];
			i++;
		}
	}
	return i;
}
#else // 首尾指针
int Solution::removeElement(vector<int> &nums, int val) {
	int n = nums.size();
	int i = 0;
	while (i < n) {
		if (nums[i] == val) {
			nums[i] = nums[n - 1];
			n--;
		} else {
			i++;
		}
	}
	return n;
}
#endif
