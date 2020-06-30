#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    // 先来个无脑递归，果断超时
    bool wordBreakO(string s, vector<string> &wordDict) {
        int maxlen = 0;
        for (auto word: wordDict) maxlen = max(maxlen, (int)word.size());
        unordered_set<string> dict(wordDict.begin(), wordDict.end());       
        return wordBreak(s, dict, maxlen);
    }
    
    bool wordBreakO(string s, unordered_set<string> &dict, int maxlen) {
        if (s.empty()) return true;
        for (int i = 0; i <= s.size() && i <= maxlen; i++) {
            string tmp = s.substr(0,i);
            if (dict.count(tmp)) {
                auto ret = wordBreak(s.substr(i), dict, maxlen);
                if (ret) return true;
            }
        }
        return false;
    }
    // 无奈，只能递归转动态规划,O(n^2)时间复杂度，感觉也不低啊
    // 长度剪枝优化
    bool wordBreak(string s, vector<string> &wordDict) {
        vector<int> dp(s.size() + 1, 0);
        unordered_set<string> dict;
        int maxlen = 0;
        for (auto &word: wordDict) { 
            maxlen = max(maxlen, (int)word.size());
            dict.insert(word);
        }
        dp[0] = 1;
        dp[1] = dict.count(s.substr(0,1)) ? 1:0;
        for (int i = 2; i <= s.size(); i++) {
            for (int j = i; i-j+1 <= maxlen && j >= 1; j--) {
                if (dict.count(s.substr(j-1, i-j+1))) {
                    dp[i] = dp[j-1] | dp[i];
                    if (dp[i]) break;
                }
            }
        }
        return dp[s.size()];
    }
};