#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        string maxPrefix = "";
        int minLength = strs[0].size();
        for_each(strs.begin(), strs.end(), [&minLength] (const string &s) { 
            if (s.size() < minLength)
                minLength = s.size();
        });
        for (int i = 0; i < minLength; i++) {
            bool flag = true;
            char currChar = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != currChar) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                maxPrefix.append(1, currChar);
            else
                break;
        }
        return maxPrefix;
    }
};

int main(void) {
//    vector<string> vec = {"flower","flow","flight"};
    vector<string> vec = {"dog","racecar","car"};
    Solution solution;
    cout << solution.longestCommonPrefix(vec) << endl;
    return 0;
}