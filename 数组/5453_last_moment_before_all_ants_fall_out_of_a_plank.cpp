#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 实际上是一个脑筋急转弯，嗯
// 蚂蚁掉头或者不掉头，其实一样的
// 掉头的话，可以看成这两者蚂蚁的身份交换了，然后实际上等于继续往前走没有掉头（替身）
// 所有的蚂蚁其实都互相不影响
class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int ans = 0;
        for (auto val: left) ans = max(ans, val);
        for (auto val: right) ans = max(ans, n-val);
        return ans;
    }
};
