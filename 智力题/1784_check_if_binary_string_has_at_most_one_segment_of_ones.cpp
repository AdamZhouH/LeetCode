#include <string>
#include <vector>
using namespace std;

lass Solution {
public:
    // 原来是一道脑经急转弯!
    // 题目翻译有问题，没有说清楚，开头的1也算连续的一段1
    // 这样的话，其实就是如果出现了0，那么0后面不能为1                                    
    bool checkOnesSegment(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                if (i+1 < s.size() && s[i+1] == '1')
                    return false;
            }
        } 
        return true;
    }
};