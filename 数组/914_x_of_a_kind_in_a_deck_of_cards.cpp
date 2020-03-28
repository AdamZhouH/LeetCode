#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
using namespace std;

class Solution {
public:
    bool hasGroupsSizeX(vector<int>& deck);
};

int gcd(int x, int y) {
    if (x < y) return gcd(y, x);
    if (y == 0) return x;
    return gcd(x % y, y);
}

// 每组牌个数相同，并且每组牌的面值也相同
// x必须为所有频率的最大公约数的一个约数
// 并且x>= 2
bool Solution::hasGroupsSizeX(vector<int>& deck) {
    unordered_map<int,int> help;
    for (auto num : deck) help[num]++;
    // 计算所有频率的最大公约数
    int var = help[deck[0]];
    for (auto &p : help) {
        var = gcd(var, p.second);
        if (var <= 1) return false;
    }
    return true;
}
