#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
using namespace std;

// 删除相邻两个重复的字符，直到不能再删除任何一对字符，求最终的字符串
// 类似于消消乐
// 做多了medium题和hard题，把这种easy题想复杂了
// 其实只用栈模拟即可
// 还是要仔细思考
// 不应该想不到用栈来模拟啊！！！！
class Solution {
public:
    string removeDuplicates(string S) {
        if (S.size() <= 1) return S;
        stack<char> stk;
        for (int i = 0; i < S.size(); i++) {
            if (stk.empty() || stk.top() != S[i]) stk.push(S[i]);
            else stk.pop();
        }
        string ret = "";
        while (!stk.empty()) {
            ret.push_back(stk.top());
            stk.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};