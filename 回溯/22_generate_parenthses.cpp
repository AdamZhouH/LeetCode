#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

// 基本思路就是在构造合法括号序列的过程中
// 保证左括号的数目不会少于右边括号的数目
// 并且第一个括号一定是左括号
// 然后递归回溯即可

class Solution {
public:
    vector<string> generateParenthesis(int n);
    // 左边括号的数目，右边括号的数目，当前字符串，结果字符串集，总体字符串对数n
    void generateParenthesis(int cntl, int cntr, string curr, vector<string> &ret, int n);
};

void Solution::generateParenthesis(int cntl, int cntr, string curr, vector<string> &ret, int n) {
    // 基准情况
/*    if (cntl == n && cntr == n) {
        ret.push_back(curr);
    } else {
        if (cntl == n && cntr < n) {
            generateParenthesis(cntl, cntr + 1, curr + ')', ret, n);
        } else {
            generateParenthesis(cntl + 1, cntr, curr + '(', ret, n);
            if (cntl > cntr) {
                generateParenthesis(cntl, cntr, curr + ')', ret, n);
            }
        }
    }
*/
    if (cntl < n && cntl < n) {
        if (cntl >= cntr) {
            generateParenthesis(cntl + 1, cntr, curr + '(', ret, n);
        } 
        if (cntl > cntr) {
            generateParenthesis(cntl, cntr + 1, curr + ')', ret, n);
        }
    } else if (cntl == n) {
        if (cntr == n) {
            ret.push_back(curr);
        } else if (cntr < n) {
            generateParenthesis(cntl, cntr + 1, curr + ')', ret, n);
        }
    } 


}

vector<string> Solution::generateParenthesis(int n) {
    vector<string> ret;
    if (n <= 0)
        return ret;
    generateParenthesis(0, 0, "", ret, n);
    return ret;
}

int main(void) {
    Solution solu;
    int n;
    cin >> n;
    vector<string> ret = solu.generateParenthesis(n);
    for (auto & s: ret) {
        cout << s << endl;
    }
    return 0;
}
