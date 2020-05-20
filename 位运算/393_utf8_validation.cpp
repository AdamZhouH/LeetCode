#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    bool validUtf8(vector<int>& data);
    bool validUtf8(vector<int>& data, int pos);
};

bool Solution::validUtf8(vector<int>& data, int pos) {
    if (pos == data.size())
        return true;
    // 判断第一个utf编码是否合法，剩下的同归递归来判断，考虑utf8编码最多是四个字节，第一位为0
    unsigned flag = 0x80;
    if (!(flag & data[pos])) {
        return validUtf8(data, pos + 1);
    } else {
        // 第一位不为0，判断连续的1的个数
        int cnt = 0;
        while (flag & data[pos]) {
            cnt++;
            flag >>= 1;
        }
        if (cnt == 1 || cnt > 4)
            return false;
        // 判断剩余字节的每个字节的开头部分是否合法
        flag = 0xC0;
        for (int i = 1; i <= cnt - 1; i++) {
            if (pos + i >= data.size() || ((data[pos + i] & flag) != 0x80))
                return false;
        }
        return validUtf8(data, pos + cnt);
    }
}

bool Solution::validUtf8(vector<int>& data) {
    if (data.size() <= 0)
        return false;
    return validUtf8(data, 0);
}