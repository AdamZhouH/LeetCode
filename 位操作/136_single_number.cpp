#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums);
};

// 最简单的方法就是利用位运算，异或
// 0和任何数n异或，结果都为n，两个相同数字异或则为0
// 当数组中只有一个单独的数字时，所有数字异或的结果就是这个数字
int Solution::singleNumber(vector<int>& nums) {
    int ret = 0;
    for (auto val : nums)
        ret ^= val;
    return ret;
}

// 当然也可以用hash表的方法
int singleNumber(vector<int>& nums) {
    unordered_map<int,int> record;
    for (auto val : nums) record[val]++;
    for (auto &p : record) 
        if (p.second == 1) return p.first;
    return 0;
}
