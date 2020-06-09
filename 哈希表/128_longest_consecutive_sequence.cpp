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

// 并查集思路，将能连续的元素看成是连通分量，求数组中各个连通分量的最大size即为所求
// 因此，对于每个数字，找左侧元素和右侧元素，如果存在，则分别和左侧右侧元素union，同时
// 更新联通分量的大小
class Solution2 {
public:
	int find(int x, unordered_map<int,int> &uf);
	int merge(int x, int y, unordered_map<int,int> &uf, unordered_map<int,int> &sz);
	int longestConsecutive(vector<int> &nums);
};

int Solution2::longestConsecutive(vector<int> &nums) {
	if (nums.empty()) return 0;
	unordered_map<int,int> uf, sz;
	for (auto num: nums) uf[num] = num, sz[num] = 1;
	int ans = 1;
	for (auto num: nums) {
		if (num != INT_MIN && uf.count(num-1))
			ans = max(ans, merge(num, num-1, uf, sz));
		if (num != INT_MAX && uf.count(num+1))
			ans = max(ans, merge(num, num+1, uf, sz));
	}
	return ans;
}

int Solution2::find(int x, unordered_map<int,int> &uf) {
	if (uf[x] == x) return x;
	uf[x] = find(uf[x], uf);
	return uf[x];
}

int Solution2::merge(int x, int y, unordered_map<int,int> &uf, unordered_map<int,int> &sz) {
	x = find(x, uf), y = find(y, uf);
	if (x == y) return sz[x];
	uf[x] = y;
	sz[y] += sz[x];
	return sz[y];
}