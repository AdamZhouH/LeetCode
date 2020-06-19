#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <queue>
using namespace std;

class Solution {
public:
    int racecar(int target) {
        // 先用BFS做一下，结果BFS果断超时了
        // 现在考虑怎么去优化一下，发现只要限制pos的距离不超过2*target以及后续的保证大于0即可
        if (target == 0) return 0;
        int cnt = 0;
        queue<pair<long, long>> q; q.push({0,1});
        set<pair<long, long>> vis; vis.insert({0,1});
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [pos, speed] = q.front(); q.pop();
                if (pos == target) return cnt;
                vector<pair<long,long>> candi = {{pos+speed, speed * 2}, {pos, speed > 0 ? -1:1}};
                for (auto &[p, s] : candi) {
                    if (!vis.count({p,s}) && p > 0 && p < 2 * target) {
                        q.push({p,s});
                        vis.insert({p,s});
                    }
                }
            }
            cnt++;
        }
        return cnt;
    }
};

// 本质上是BFS的变形，现在考虑如何用动态规划的思路来解决问题
