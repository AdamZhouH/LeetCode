#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums);
};

// #define VOTE
// 投票法
#ifdef VOTE
int Solution::majorityElement(vector<int>& nums) {
    int count = 0, ret;
    for (auto var : nums) {
        if (count == 0) ret = var;
        if (ret == var) 
            count++;
        else 
            count--;
    }
    return ret;
}
#else
// 哈希表统计频率法
int Solution::majorityElement(vector<int>& nums) {
    int major, maxcnt = INT_MIN;
    unordered_map<int, int> imap;
    for (auto num : nums) {
        imap[num]++;
        if (imap[num] >maxcnt) {
            major = num;
            maxcnt = imap[num];
        }
    }
    return major;
}
#endif
