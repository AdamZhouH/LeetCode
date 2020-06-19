#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkValidString(string s);
    bool checkValidString(const string &s, int idx, int cnt);
};

bool Solution::checkValidString(string s) {
    if (s.empty()) return true;
    return checkValidString(s, 0, 0);
}

bool Solution::checkValidString(const string &s, int idx, int cnt) {
    if (idx >= s.size()) return cnt == 0;
    if (cnt < 0) return false;
    if (s[idx] == '(') {
        return checkValidString(s, idx+1, cnt+1);
    } else if (s[idx] == ')') {
        return checkValidString(s, idx+1, cnt-1);
    } else {
        return checkValidString(s, idx+1, cnt+1) || checkValidString(s, idx+1, cnt-1) || checkValidString(s, idx+1, cnt);
    }
}
