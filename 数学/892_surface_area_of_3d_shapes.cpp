class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid);
};
#ifndef OPTIMIZE
// 计算立体结构的表面积，因为内部一些暴露的表面可能会被某侧的视图挡住
// 这部分面积在计算各个侧面视图时可能并没有计算计入，因此计算方法不准确
// 而应该计算的时接触面的个数，每当存在一个接触面，则导致面积-2
// 计算接触面从xyz轴三个方向考虑（考虑z轴上每层都可能存在接触面积）
int Solution::surfaceArea(vector<vector<int>>& grid) {
    if(grid.empty()) return 0;
    // 扫描x方向上的接触面个数时候可以同时计算每层z方向上的接触面个数
    int contactx = 0, contacty = 0, contactz = 0;
    int n = grid.size(), total = 0;
    for (int i =  0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] > 0) { total += grid[i][j]; contactz += grid[i][j] - 1; }
            if ((j-1) >= 0) contactx += min(grid[i][j], grid[i][j-1]);
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if ((i-1) >= 0) contacty += min(grid[i][j], grid[i-1][j]);
        }
    }
    return total * 6 - (contactx + contacty + contactz) * 2;
}
#else
// 上面是非常蠢的做法，因为遍历了两遍，实际上整体思路没问题，就是减去接触的面积
// 但实际上可以把每个格子的立方体当成一个整体，即一个柱体来看待
// 每次遍历到某个格子，则减去这个格子上的柱体和它左边以及上边的接触面积
// 接触面结显然就是两个柱体高度的最小值*2
int Solution::surfaceArea(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    int ret = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] > 0) {
                ret += (grid[i][j] << 2) + 2;
                if (i > 0) ret -= min(grid[i-1][j], grid[i][j]) * 2;
                if (j > 0) ret -= min(grid[i][j-1], grid[i][j]) * 2;
            }
        }
    }
    return ret;
}
#endif