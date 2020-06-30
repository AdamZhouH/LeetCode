#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // 这题考虑到整除的话，实际上可以考虑余数，只要两个数字的modk后相加的和modk为0
    // 则这对数字就能够凑成满足要求的一组数
    // 因此主要考虑互补余数的个数是否匹配即可，注意i==0和i==k-i的情况，这两种情况下，只需要判断自身是否是偶数即可
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> cnt;
        for (auto val: arr) {
            cnt[(val%k+k)%k]++;
        }
        for (int i = 0; i <= k/2; i++) {
            if (i == 0 ) { if (cnt[i] % 2) return false; continue; }
            if (i == k - i) { if (cnt[i] % 2) return false; continue; }
            if (cnt[i] != cnt[k-i]) return false;
        }
        return true;
    }
};
