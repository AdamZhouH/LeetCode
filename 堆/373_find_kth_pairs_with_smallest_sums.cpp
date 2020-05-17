#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k);
};

// 大根堆比较

struct Cmp {
    bool operator()(const pair<int,int>&lhs, const pair<int,int>&rhs) {
        return lhs.first+lhs.second < rhs.first+rhs.second;
    }
};

vector<vector<int>> Solution::kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    vector<vector<int>> ret;
    priority_queue<pair<int,int>, vector<pair<int,int>>, Cmp> q;
    for (int i = 0; i < nums1.size(); i++) {
        for (int j = 0; j < nums2.size(); j++) {
            auto p = make_pair(nums1[i], nums2[j]);
            // 注意剪枝
            if (q.size() >= k && !Cmp()(p, q.top())) break;
            if (q.size() >= k) q.pop();
            q.push(p);
        }
    }
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        ret.push_back({p.first, p.second});
    }
    return ret;
}