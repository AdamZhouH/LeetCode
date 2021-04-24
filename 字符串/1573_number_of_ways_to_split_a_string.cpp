#include <string>
#include <vector>
#include <algorithm>
using namespace std;


// 考虑分割的三个部分s1 s2 s3
// 其实更像一个组合问题，实际上只需要拿到s1和s2之间0的个数、s2和s3之间0的个数
// 然后两者组合即可得到总体的方案数
// 提交时候被一例子卡住了，考虑溢出的情况，这里用long比较好

class Solution {
public:
    const int MOD = 1e9+7;
    
    int numWays(string s) {
        int cntOf1 = 0;
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') cntOf1++;   
        }
        if (cntOf1 % 3) return 0;
        if (cntOf1 == 0) return ((((s.size()-1)%MOD)*((s.size()-2)%MOD))/2)%MOD;
        int cntOfCurr1 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') cntOfCurr1++;
            else {
                if (cntOfCurr1 == (cntOf1 / 3)) cnt1++;
                if (cntOfCurr1 == (cntOf1 / 3 * 2)) cnt2++;
            }
        }
        return ((long(cnt1+1)%MOD)*(long(cnt2+1)%MOD))%MOD;
    }
};