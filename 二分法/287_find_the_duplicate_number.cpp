#include <iostream>
#include <vector>
using namespace std;

// 之前审题不清楚，使用了哈希检测法，虽然时间空间复杂度都满足要求，但是改变了
// 原数组，而题目要求不能更改原始数组
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == i + 1) continue;
            int j = i;
            while (nums[j] != j + 1) {
                if (nums[j] == nums[nums[j]-1]) return nums[j];
                else {
                    int tmp = nums[nums[j]-1];
                    nums[nums[j]-1] = nums[j];
                    nums[j] = tmp;
                }
            }
        }
        return -1;
    }
};

// 双指针算法
// 将数组元素视为链表中的元素，若出现重复元素则肯定是一个环状链表
// 使用快慢指针可以判断是否存在环，并且找到环的入口
// 这里，每个元素的值就是下一个
class Solution2 {
	int findDuplicate(vector<int> &nums) {

	}
};

// 二分查找算法
// 思路分析
// 数组中的元素都在1-n范围内，并且只有一个元素重复的
// 加入这个重复的元素为i，那么数组中不超过i的元素的个数一定大于i
// 并且随着i的增加，不超过i的元素的个数也在增加，因此使用二分查找
// 针对某个值k，查找数组中小于等于k的元素个数，如果元素个数小于k，则说明这个重复元素
// 一定比k要大，如果个数大于等于k，则说明这个重复的元素不小于k
// 类似于用二分查找找到一个数字的左边界，第一个满足小于等于k的元素个数大于k的k
class Solution3 {
	int findDuplicate(vector<int> &nums) {
        int left = 1, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int count = 0;
            for (auto val : nums) if (val <= mid) count++;
            if (count <= mid)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
	}
};
