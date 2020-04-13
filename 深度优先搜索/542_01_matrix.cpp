#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

// 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
// 两个相邻元素间的距离为 1 

// 算法思路
// 首先想到的，这是一个距离更新问题，能够想到DIJKSTRA算法，但是，由于只有01
// 所以，其实每个0都是一个bfs遍历的起点，如果考虑从每个0都执行一次，然后更新距离
// 那么时间复杂度达到O(n^3)，显然，需要优化
// 考虑，首先把遍历一矩阵，把每个为0的点，放入bfs队列
// 从队首元素开始，向四个方向中的合理的位置，开始更新距离，如果某个方向的原来保存的距离更大
// 则更新之，然后放入队列（因为从这个节点开始，他四周的点到第一个0的距离可以缩短，因此，之后需要从这个点开始bfs一次）
// 如果原来距离更小，则不用理会

class Solution {
public:
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
public:
	typedef pair<int, int> Point;
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix);
};

vector<vector<int>> Solution::updateMatrix(vector<vector<int>> &matrix) {
	int m = matrix.size(), n = matrix[0].size();
	vector<vector<int>> ret(m, vector<int>(n, INT_MAX));
	queue<Point> q;
	// 首先遍历矩阵，把所有为0的点放入队列，并且更新ret中对应的距离
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 0) {
				q.push({i, j});
				ret[i][j] = 0;
			}
		}
	}
	// 开始bfs遍历的过程
	while (!q.empty()) {
		auto p = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int idx = p.first + dx[i];
			int idy = p.second + dy[i];
			// 节点合法，同时距离上满足更新的条件
			if (idx >= 0 && idx < m && idy >= 0 && idy < n && ((ret[idx][idy]) > (ret[p.first][p.second] + 1))) {
				ret[idx][idy] = ret[p.first][p.second] + 1;
				q.push({idx, idy});
			}
		}
	}
	// bfs遍历完毕后，直接返回结果
	return ret;
}

int main(void) {
	Solution solu;
	vector<vector<int>> matrix = {
		{0,0,0},
		{0,1,0},
		{1,1,1}
	};
	auto ret = solu.updateMatrix(matrix);
	for (auto &it : ret) {
		for (auto &val : it)
			cout << val << ' ';
		cout << endl;
	}
	return 0;

}