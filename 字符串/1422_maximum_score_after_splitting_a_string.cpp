#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int maxScore(string s) {
        vector<int> cnt0(s.size() + 1, 0);
        vector<int> cnt1(s.size() + 1, 0);
        for (int i = 1; i <= s.size(); i++) {
            cnt0[i] = cnt0[i-1] + '1' - s[i-1];
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            cnt1[i] = cnt1[i+1] + s[i] - '0';
        }
        int maxScore = 0;
        for (int i = 0; i < s.size() - 1; i++) {
            maxScore = max(maxScore, cnt0[i+1] + cnt1[i+1]);
        }
        return maxScore;
    }
};
