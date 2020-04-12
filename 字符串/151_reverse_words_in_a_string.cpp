#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string reverseWords(string s);
};

// 最简单的做法
string Solution::reverseWords(string s) {
    istringstream input(s);
    string temp, ans;
    while (input >> temp) ans = temp + ' ' + ans;
    return ans.empty() ? "" : string(ans.begin(), ans.end()-1);
}

// 空间复杂度为O(1)的思路
// 两次翻转，首先整行翻转，然后行内单词翻转，最后去掉首尾和中间的多余空格
// 在去掉多余空格的过程中可以使用双指针辅助
// 当然，由于C++必须返回一个string的右值，因此不可能空间复杂度为O(1)，只有C语言才能
// 实现真正的O(1)空间复杂度
// 思路就是，首先双指针遍历，去除首位的空格，尾部设置为空字符，然后返回首部指针
// 字符串原地翻转
// 针对行内每个单词，首先找到可插入位置，然后整体往前移动
// 可以使用双指针辅助
