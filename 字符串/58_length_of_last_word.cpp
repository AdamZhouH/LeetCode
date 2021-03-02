#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int cnt = 0;
        for (auto it = s.rbegin(); it != s.rend(); it++) {
            if (!isspace(*it)) {
                cnt++;
            } else if (cnt) {
                return cnt;
            }
        }
        return cnt;
    }
};
