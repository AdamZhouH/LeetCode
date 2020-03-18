class Solution {
public:
    vector<vector<int>> Solution::merge(vector<vector<int>> &intervals) {
        vector<vector<int>> ret;
        if (intervals.empty())
            return ret;
        // vector<int>可以直接比较，省去写Compare对象了
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < intervals.size();) {
            int j = i + 1;
            // 将intervals[i]作为目的区间，每次进行扩展
            while (j < intervals.size() && intervals[j][0] <= intervals[i][1]) {
                intervals[i][1] = max(intervals[i][1], intervals[j][1]);
                j++;
            }
            ret.push_back(intervals[i]);
            i = j;
        }
        return ret;
    }
};

