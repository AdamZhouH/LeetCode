/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */


bool operator < (const Interval &lhs, const Interval &rhs) {
    return lhs.end < rhs.end;
}


class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if (intervals.size() <= 1)
            return 0;
        sort(intervals.begin(), intervals.end());
        int total = intervals.size();
        // 贪心选择过程
        Interval prev = intervals[0];
        Interval curr;
        int count = 1;
        for (int i = 1; i < total; i++) {
            curr = intervals[i];
            if (curr.start >= prev.end) {
                count++;
                prev = curr;
            }
        }
        return total - count;
    }
};