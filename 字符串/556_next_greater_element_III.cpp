#include <vector>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    // 注意几种特殊情况
    // 1.下一个更大的数字溢出，那么不存在
    // 2.本身就是这几个字符能够组成的最大数字，那么也不存在下一个数字
    int nextGreaterElement(int n) {
        if (n < 10) return -1;
        string str = to_string(n);
        // p1 p2分别指向两个要交换的数字的为止
        int p1 = str.size()-2;
        while (p1 >= 0 && str[p1]>=str[p1+1]) p1--;
        if (p1 < 0) return -1;
        int p2 = str.size()-1;
        while (p2 > p1 && str[p2] <= str[p1]) p2--;
        char tmp = str[p2]; str[p2] = str[p1]; str[p1] = tmp; // 交换
        reverse(str.begin()+p1+1, str.end()); // 逆序
        long ret = stol(str);
        return ret > INT_MAX ? -1:ret;
    }
};
