#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);
};

// 下一个更大的元素，很明显的单调栈的使用
// 加上一个hash，用于记录nums1中的元素的值和对应的下标，从而减少时间复杂度，避免遍历nums1寻找某个元素
vector<int> Solution::nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ret(nums1.size(), -1);
    unordered_map<int,int> idxOfValue;
    for (int i = 0; i < nums1.size(); i++) { idxOfValue[nums1[i]] = i; }
    stack<int> stk; // 单调递减栈
    for (int i = 0; i < nums2.size(); i++) {
        while (!stk.empty() && nums2[stk.top()] < nums2[i]) {
            int idx = stk.top(); stk.pop();
            if (idxOfValue.count(nums2[idx])) ret[idxOfValue[nums2[idx]]] = nums2[i];
        }
        stk.push(i);
    }
    return ret;
}

