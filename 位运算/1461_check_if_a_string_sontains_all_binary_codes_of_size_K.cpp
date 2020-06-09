#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool hasAllCodes(string s, int k);
};

// Sliding Windows and bit operation
// using sliding window to travel all of the string with length K
// and turns it into a integer and make the exist flag
// then travel the vis array if one of which has never been get, return false
bool Solution::hasAllCodes(string s, int k) {
    if (s.size() <= k) return false;
    vector<int> record((1<<k)-1, 0);
    for (int i = 0, j = k-1; j < s.size(); i++, j++) {
        string str = s.substr(i, k);
        record[stoi(str)] = 1;
    }
    for (auto flag: record)
        if (flag == 0) return false;
    return true;
}


// 利用位运算，直接获取每次的整数
bool hasAllCodes(string s, int k) {
    if (s.size() <= k) return false;
    vector<int> record(1<<k, 0);
    int mask = (1 << k) - 1;
    int curr = 0, tmp = 0;
    while (tmp < k) {
        curr = (curr<<1) & mask; 
        curr |= s[tmp++] - '0';
    }
    record[curr] = 1;
    for (int i = 1; i + k - 1 < s.size(); i++) {
        curr = (curr<<1) & mask; 
        curr |= s[i+k-1]-'0';
        record[curr] = 1;
    }
    for (auto val: record) if (val == 0) return false;
    return true;
}