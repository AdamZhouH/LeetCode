#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

const long long MOD = 1e+9 + 7;

class Solution {
public:
    int numOfWays(int n);
};
// 思路，考虑最后一层可能的情况，只和上一层有关系
// 只要保证最后一层的颜色和上一层的颜色符合题目的规则，那么最后一层的当前配色就能满足

// 一种迭代思路
// 每次只要计算下一层可以存在的组合数即可
void dfs(const vector<int> &vec, vector<int> &curr, int cnt, map<vector<int>,int> &currlevel, int i) {
    if (i > 2) {
        currlevel[curr] = (currlevel[curr] + cnt) % MOD;
        return;
    }
    for (int val = 0; val <= 2; val++) {
        if (i == 0) {
            if (vec[i] != val) {
                curr.push_back(val);
                dfs(vec, curr, cnt, currlevel, i+1);
                curr.pop_back();
            }
        } else {
            if (vec[i] != val && curr[i-1] != val) {
                curr.push_back(val);
                dfs(vec, curr, cnt,  currlevel, i+1);
                curr.pop_back();
            }
        }
    }
}

// 记录当前层的每一种合理组合具有的方案数，那么总的方案数就是他们之和
// 这种方法超时了，虽然结果是正确的
int Solution::numOfWays(int n) {
    if (n == 1) return 12;
    // 初始化第一层，每一种组合都只有一种方案
    vector<vector<int>> record = {
        {0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, {2,1,0}, {2,0,1},
        {1,0,1}, {0,1,0}, {2,0,2}, {0,2,0}, {1,2,1}, {2,1,2}
    };
    map<vector<int>, int> prevlevel;
    for (int i = 0; i < record.size(); i++) prevlevel[record[i]] = 1;
    for (int i = 2; i <= n; i++) {
        map<vector<int>, int> currlevel;
        for (auto &p : prevlevel) {
            vector<int> curr;
            dfs(p.first, curr, p.second, currlevel, 0);
        }
        prevlevel = currlevel;
    }
    // 统计总个数
    int total = 0;
    for (auto &p : prevlevel)
        total = (total + p.second) % MOD;
    return total;
}
// 另一种思路，首先明确的是，增加一层后，能够增加的方案数只能上次的最后一层有关
// 动态规划思路，每一层的可行方案实际上分两种，用两个元素和用三个元素的
// 针对用两个元素的，也就是ABA型，在下一层可以增加
int numOfWays(int n) {
    if (n == 1) return 12;
    vector<vector<long>> dp(n, vector<long>(2,0));
    dp[0][0] = 6, dp[0][1] = 6;
    for (int i = 1; i < n; i++) {
        dp[i][0] = (dp[i-1][0] *3 + dp[i-1][1] * 2) % MOD;
        dp[i][1] = (dp[i-1][0] *2 + dp[i-1][1] * 2) % MOD;
    }
    return (dp[n-1][0] + dp[n-1][1]) % MOD;
}

int main(int argc, char *argv[]) {
    int n;
    Solution slu;
    while (cin >> n) {
        cout << slu.numOfWays(n) << endl;
    }
    return 0;
}
