#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k);
};

// 这道题目其实只要仔细分析，没有想象中那么困难
// 抓住关键点：
// 每一组都是k个连续的数字，那么假如这个数组可以按照题目要求划分成若干组这样的每组k个数字的组
// 那么显然，当前最小的那个数字，一定是某个组的开头的数字按照这种规则，那么剩下k-1个数字一定存在
// 然后从nums中拿完这一组后，同样，剩下的是数字中找到最小的数字，按照同样的方法
// 那么最终能够分完所有的数字，说明数字可以这样分，不能的话则不行
// 实际上是一个贪心算法的应用
//
// 先上自己的笨方法
bool Solution::isPossibleDivide(vector<int>& nums, int k) {
    if (nums.size() < k || (nums.size() % k)) return  false;
    // 利用map记录每个数字的出现次数，并且map本身是按照key的顺序排序的
    // 因此每次能拿到当前的最小数字
    map<int, int> record;
    for_each(nums.begin(), nums.end(), [&] (int val) { record[val]++; });
    while (!record.empty()) {
        auto it = record.begin();
        for (int i = 1; i < k; i++) {
            auto ret = record.find(it->first + i);
            if (ret == record.end()) return false;
            if (--ret->second == 0) record.erase(ret);
        }
        if (--it->second == 0) record.erase(it);
    }
    return true;
}

