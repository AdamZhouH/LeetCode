#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string currprefix = strs[0];
        for (int i = 1; i < strs.size(); i++) {
            if (currprefix.empty()) break;
            int j = 0;
            for (; j < currprefix.size() && j < strs[i].size(); j++) {
                if (strs[i][j] != currprefix[j]) break;
            }
            currprefix = currprefix.substr(0,j);
        }
        return currprefix;
    }
};

int main(void) {
//    vector<string> vec = {"flower","flow","flight"};
    vector<string> vec = {"dog","racecar","car"};
    Solution solution;
    cout << solution.longestCommonPrefix(vec) << endl;
    return 0;
}
