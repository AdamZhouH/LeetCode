class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2);
};

// 判断两个矩形的左右上下位置关系
// 若其中一个矩形完全在另一个矩形的上方或者下方或者左方或者右方，则一定不会相交

bool Solution::isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
    if (rec1.empty() || rec2.empty())
        return false;
    if (rec1[0] >= rec2[2] ||
        rec1[2] <= rec2[0] ||
        rec1[3] <= rec2[1] ||
        rec1[1] >= rec2[3])
        return false;
    return  true;
}