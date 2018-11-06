#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 利用并查集思想

// 寻找树根
int Find(vector<int>& s, int val) {
    if (s[val] == -1)
        return val;
    else
        return Find(s, s[val]);
}
// 并集合操作
// Union并集合操作需要注意很多细节
void Union(vector<int>& s, int lhs, int rhs) {
    int a = Find(s, lhs), b = Find(s, rhs);
    if (a == b)
        return;
    else {
        // 合并两个地方，有助于减少树高度
        s[rhs] = a;
        s[b] = a;
        // 也可以合并一个地方
        // s[b] = a;
    }
}

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M);
};

int Solution::findCircleNum(vector<vector<int>>& M) {
    if (M.empty())
        return 0;
    int n = M.size();
    vector<int> s(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            } else if (M[i][j] == 1) {
                // 发现一对朋友，则把他们加入到同一个朋友圈
                Union(s, i, j);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == -1)
            cnt++;
    }
    return cnt;
}