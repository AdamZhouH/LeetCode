#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
	int longestConsecutive(vector<int> &nums);
};

/**
 * 题目如果用排序的话，O(Nlog(N))的事件复杂度可以搞定，先排序，然后遍历即可找到最大连续数字的长度
 * 但是题目要求算法时间复杂度在O(N)，并且数组本身是无序的，因此想到用哈希表(STL中的unordered部分的关联容器)
 * 
 * */
