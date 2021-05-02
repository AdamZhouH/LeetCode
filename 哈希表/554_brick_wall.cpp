#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int n = wall.size();
        unordered_map<int, int> cutRecord;
        int maxCutCnt = 0;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < wall[i].size(); j++) {
                if (j != wall[i].size()-1) {
                    sum += wall[i][j];
                    cutRecord[sum]++;
                    maxCutCnt = max(maxCutCnt, cutRecord[sum]);
                }
            }
        }
        return n - maxCutCnt;
    }
};