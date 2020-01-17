class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops);
};

int Solution::maxCount(int m, int n, vector<vector<int>>& ops) {
//  vector<vector<int>> matrix(m, vector<int> (n, 0));
// 开始没有考虑到ops为空的情况
    if (ops.empty())
        return m * n;
/*
    // 模拟行为
    // 直接模拟，内存超出限制
    int maxNum = INT_MIN;
    int count = 0;
    int a, b;
    for (auto &vec : ops) {
        a = vec[0], b = vec[1];
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                matrix[i][j] += 1;
                maxNum = max(maxNum, matrix[i][j]);
            }
        }
    }
    // 统计
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == maxNum)
                count++;
        }
    }
*/ 
    
    // 实际上是统计区间交集的个数

    // 而且题目中已经保证了是正整数，因此不会出现操作失效的情况
    long long count = 0;
    int lastm, lastn;

    count = ops[0][0] * ops[0][1];
    lastm = ops[0][0];
    lastn = ops[0][1];
    
    for (int i = 1; i < ops.size(); i++) {
        lastm = min(ops[i][0], lastm);
        lastn = min(ops[i][1], lastn);
    }
    return lastm * lastn;
}