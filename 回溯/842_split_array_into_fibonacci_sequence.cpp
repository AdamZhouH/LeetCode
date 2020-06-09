#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> splitIntoFibonacci(string S);
    vector<int> judge(long a, long b, string S);
};

// Fibonacci序列的特点在于，只要确定了前两项，那么可以直接推导出后面的所有数字
// 因此，实际上是考虑如何确定前两个数字，然后在此基础上，判断后续的字符串能够构成斐波那契序列
// 考虑特殊的一点，0不能作为数字的开头，除非单独作为一个数字
// 因此这题可以考虑利用迭代选择前两个数字，然后在此基础上，判断后续的字符串能否构成Fibonacci数列
// 注意点
// 1.0不能作为开头，除非数字为0本身
// 2.不能越界，超过INT_MAX，否则也不是合理的Fibonacci数列

vector<int> Solution::splitIntoFibonacci(string S) {
    vector<int> ret;
    if (S.empty() || S.size() < 3) return ret;
    int n = S.size();
    for (int i = 0; i < n - 2 && stol(S.substr(0,i+1)) < INT_MAX; i++) {
        for (int j = i + 1; j < n - 1 && stol(S.substr(i+1,j-i)) < INT_MAX; j++) {
            string s1 = S.substr(0,i+1), s2 = S.substr(i+1,j-i);
            if (s1.size() > 1 && s1[0] == '0' || s2.size() > 1 && s2[0] == 0) continue;
            long a = stol(s1), b = stol(s2);
            if (a + b > INT_MAX) break;
            ret = judge(a,b,S.substr(j+1));
            if (!ret.empty()) return ret;
        }
    }
    return ret;
}

vector<int> Solution::judge(long a, long b, string S) {
    vector<long> ret = {a, b};
    while (!S.empty()) {
        long c = ret[ret.size()-1] + ret[ret.size()-2];
        if (c > INT_MAX) break;
        string str = to_string(c);
        auto pos = S.find(str);
        if (pos == string::npos || pos != 0) break;
        else { 
            ret.push_back(c);
            S = S.substr(str.size()); 
        }
    }
    return S.empty() ? vector<int>(ret.begin(), ret.end()) : vector<int>();
}

