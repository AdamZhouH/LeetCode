#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

/**
 * 题目如果用排序的话，O(Nlog(N))的事件复杂度可以搞定，先排序，然后遍历即可找到最大连续数字的长度
 * 但是题目要求算法时间复杂度在O(N)，并且数组本身是无序的，因此想到用哈希表(STL中的unordered部分的关联容器)
 * 将元素放入哈希表中，需要O(N)时间复杂度，但是在哈希表中查找元素的平均时间复杂度为O(1)
 * 先给出基于哈希表查找的算法一
*/

class Solution {
public:
	int longestConsecutive(vector<int> &nums);
};

// 找一个可以作为左端起始点的数作为开始计算Consective长度的数字
// 保证以本数字为左端起始点所包含的连续序列中的数字不会被重复计算
int Solution::longestConsecutive(vector<int> &nums) {
    // 为空的情况不要忘记！！！
	// PS Leetcode的提交有毒
    if (nums.empty())
        return 0;
	unordered_set<int> numbers(nums.begin(), nums.end());
	int maxLen = INT_MIN;
	for (auto x: numbers) {
		if (numbers.count(x - 1)) {
			continue;
		}
        int currNum = x;
		int currLen = 1;
		while (numbers.count(currNum + 1)) {
            currNum += 1;
            currLen++;
        }
		maxLen = max(maxLen, currLen);
	}
    return maxLen;
}