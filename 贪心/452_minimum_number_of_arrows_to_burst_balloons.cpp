#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points);
};

// 求尽可能多的球重叠的公共区域的个数
int Solution::findMinArrowShots(vector<vector<int>> &points) {
    if (points.size() <= 1) return points.size();
    sort(points.begin(), points.end(), [](vector<int>&lhs, vector<int>&rhs){
        return lhs[1]==rhs[1] ? lhs[0]<rhs[0] : lhs[1]<rhs[1];
    });
    int cnt = 1, left = points[0][0], right = points[0][1];
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] <= right) left = max(left,points[i][0]), right = min(right,points[i][1]);
        else cnt++, left = points[i][0], right = points[i][1];
    }
    return cnt;
}
// 比较简洁的写法
class Solution2 {
public:
    int findMinArrowShots(vector<vector<int>>& points);
};

int Solution2::findMinArrowShots(vector<vector<int>> &points) {
    if (points.size() <= 1) return points.size();
    sort(points.begin(), points.end(), [](vector<int>&lhs, vector<int>&rhs){
        return lhs[1]==rhs[1] ? lhs[0]<rhs[0] : lhs[1]<rhs[1];
    });
    int cnt = 1;
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > points[i-1][1]) cnt++;
        else points[i][1] = points[i-1][1];
    }
    return cnt;
}
