#include <string>
#include <vector>
using namespace std;


class Solution {
public:
    string addBinary(string a, string b) {
        if (a.empty() && b.empty()) return "0";
        if (a.empty()) return b;
        if (b.empty()) return a;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        string ret;
        int flag = 0;
        for (int i = 0; i < a.size() || i < b.size(); i++) {
            int curr = (i < a.size() ? a[i]-'0' : 0) +
                       (i < b.size() ? b[i]-'0' : 0) +
                       flag;
            if (curr < 2) { ret.push_back(curr+'0'); flag = 0;}
            else if (curr == 2) { ret.push_back('0'); flag = 1;}
            else { ret.push_back('1'); flag = 1; }
        }
        if (flag) ret.push_back('1');
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
