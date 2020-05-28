#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string decodeString(string s);
};

// 由于存在嵌套的情况，这题目用递归比较方便
// 每次解最内层的嵌套（替换）然后递归即可
string Solution::decodeString(string s) {
    if (s.empty() || s.find('[') == string::npos) return s;
    auto p1 = s.find_last_of('[');
    auto p2 = s.find_first_of(']', p1);
    // fetch repeat times
    auto p3 = p1;
    while (p3 > 0 && isdigit(s[p3 - 1])) p3--;
    int repeats = stoi(s.substr(p3, p1 - p3));
    string tmp;
    while (repeats--) tmp += s.substr(p1 + 1, p2 - p1 - 1);
    return decodeString(s.substr(0, p3) + tmp + s.substr(p2 + 1));
}
