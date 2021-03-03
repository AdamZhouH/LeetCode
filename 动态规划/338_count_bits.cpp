#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> countBits(int num);
};
// 暴力思路
vector<int> Solution::countBits(int num) {
    vector<int> ret;
    for (int i = 0; i <= num; i++) {
        int cnt = 0;
        int temp = i;
        while (temp) { cnt++; temp &= (temp-1); }
        ret.push_back(cnt);
    }                     
    return ret;
}

// 空间换时间的O(n)思路
// 考虑一个数字，不管是奇数还是偶数，将i>>1得到的这个数字的1的个数肯定是我们计算过的，因为i>>1比
// i要更小，有了i>>1的个数就很好办，如果i是奇数，那么i>>1，如果i是偶数，那么i>>1 + 1
// 因此有以下的解法
vector<int> countBits(int num) {
    vector<int> ret(num+1, 0);
    for (int i = 1; i <= num; i++) {
        ret[i] = ret[i>>1] + (i&1);
    }   
    return ret;
}




