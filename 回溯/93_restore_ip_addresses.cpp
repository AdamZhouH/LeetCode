#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 回溯，递归
// 针对一个长的字符串，先选择第一部分，然后剩下的字符串，再去选择第二部分，第三部分，第四部分
// 递归地完成每个部分的选择
// 基准情况，已经选择到达了第四部分，判断剩下的字符串能够构成合法的第四部分，可以，则放入结果，然后回溯回去
// 不可以，则直接回溯上一层


class Solution {
public:
    vector<string> restoreIpAddresses(string s);
    // 参数类型
    // 最终结果集，原始字符串，当前开始选择的起始位置，当前选择的部分是合法ip的第几部分，当前可能合法的ip地址
    void dfs(vector<string> &ret, const string &orig, int pos, int idx, string ip);
};

vector<string> Solution::restoreIpAddresses(string s) {
    vector<string> ret;
    if (s.size() < 4)
        return ret;
    dfs(ret, s, 0, 1, "");
    return ret;
}

void Solution::dfs(vector<string> &ret, const string &orig, int pos, int idx, string ip) {
    // 判断是第几部分
    if (idx == 4) {
        // pos是否合法
        if (pos < orig.size()) {
            // 超过3个字符说明剩下的字符数过多
            if (orig.size() - pos > 3)
                return;
            // 判断首个字符是否是0，如果是并且长度超过1，则不能算合法字符
            if (orig[pos] == '0' && pos != orig.size() - 1)
                return;
            int val = stoi(orig.substr(pos));
            if (val <= 255 && val >= 0) {
                ret.push_back(ip + "." + orig.substr(pos));
            }
        } else {
            // 说明第四部分已经没有字符串可选择，不能构成合法ip
            return;
        }
    } else {
        // 并不是选择最后一部分，而是选择其他部分
        // 根据情况，选择1 2 3个字符作为当前的合法ip的某个部分，然后递归下去
        if (pos < orig.size()) {
            for (int i = 0; i < 3 && pos + i < orig.size(); i++) {
                // 如果当前选择的长度不为1，但是首个字符为0，那么按照题目意思，是非法的，因此这种情况不需要递归
                if (orig[pos] == '0' && i != 0)
                    break;
                if (ip.empty()) {
                    // 当长度为3，需要判断是否合法
                    if (i != 2 || (stoi(orig.substr(pos, 3))>= 0 && stoi(orig.substr(pos, 3)) <= 255))
                        dfs(ret, orig, pos + i + 1, idx + 1, ip + orig.substr(pos, i + 1));
                } else {
                    if (i != 2 || (stoi(orig.substr(pos, 3))>= 0 && stoi(orig.substr(pos, 3)) <= 255))
                        dfs(ret, orig, pos + i + 1, idx + 1, ip + "." + orig.substr(pos, i + 1));
                }
            }
        } else {
            return;
        }
    }
}


int main(void) {
    Solution solu;
    string s;
    while (cin >> s) {
        auto ret = solu.restoreIpAddresses(s);
        for_each(ret.begin(), ret.end(), [] (const string &s) { cout << s << endl; });
    }
    return 0;
}
