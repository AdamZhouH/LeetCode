#include <string>
using namespace std;


// 就是一个很简单的26进制转换
class Solution {
public:
    int titleToNumber(string s);
};

const int Mod = 26;
// 26进制数据的转换
int Solution::titleToNumber(string s) {
    int ret = 0;
    for (auto c : s) {
        ret = ret * Mod + (c - 'A' + 1);
    }
    return ret;
}
