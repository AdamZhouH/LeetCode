#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // 此题的确是用排序来做，但是关键点在于算法的正确性证明
        // 首先，如果两个数字的长度一致，那么尽可能让高位数字更大的排在前面，如果高位相同，则比较次高位
        // 如果两个数字的长度不一致，假设两个数字记为lhs和rhs，则拼接的字符串可以是
        // lhs+rhs或者rhs+lhs，拼接后比较字符串对应的数字，哪个大选择哪个
        // 实际上这道题是对应了一种排序方法，关键是说明这种排序算法下
        // 组合出来的数字是最大的
        // 1.需要证明传递性
        // 2.需要证明正确性(可以考虑反证法)
        sort(nums.begin(), nums.end(), [] (const int &lhs, const int &rhs) {
            string l = to_string(lhs);
            string r = to_string(rhs);
            return l+r > r+l;
        });
        string ret;
        for (int i = 0; i < nums.size(); i++) {
            // [0,0] 这种测试用例，也太坑了吧
            ret += to_string(nums[i]);
        }
        auto idx = ret.find_first_not_of('0');
        if (idx == string::npos) return "0";
        else return ret.substr(idx);
    }
};