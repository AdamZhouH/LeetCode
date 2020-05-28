#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 想清楚后，其实是很简单的题
// 亮的灯全部为蓝色的条件就是当前最远处亮着的灯的位置等于
// 当前亮灯的个数即可
// 从开始到某处，连续亮着灯，并且之后的位置没有亮灯
class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int cnt = 0, ans = 0;
        int lastpos = INT_MIN;
        for (int i = 0; i < light.size(); i++) {
            lastpos = max(lastpos, light[i]), cnt++;
            if (lastpos == cnt) ans++;
        }
        return ans;
    }
};