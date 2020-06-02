#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
using namespace std;

// 第一次碰到这种ConvecHull问题(凸包问题)
// 使用graham算法解决
// 1.找到左下角的点，以此为基准，将其他节点按照旋转角度大小（利用叉乘判断顺时针还是逆时针旋转）和距离进行排序
// 2.初始两个节点放入到stack中，然后从第三个节点开始遍历，每当遇到和前两个节点构成凹形状时，就把当前top节点pop掉，直到遇到满足构成凸形状，然后将当前节点入栈
// 3.注意最后一个节点和初始节点的直线上可能存在其他的节点，这些节点显然要加入凸包中，但是如果按照最开始排序的距离
//   将会是从距离小的节点开始一直到最后一个节点，通过简单的例子可以知道，这样会导致这些共线点只保留了距离最远的那个
//   而这些距离近的点就漏掉，因此，对于最后一条边以及在这些边上的点，需要从距离最远的，也就是最后一个点开始处理
//   这里，对sort后的Point数组处理，将共线在最后一条凸边上的点的顺序逆序，然后再开始遍历，从而避免这种情况
using Point = pair<int, int>;
class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>> &points);
	int crossMul(const Point &p1, const Point &p2, const Point &p3);
	int distance(const Point &p1, const Point &p2);
};

int Solution::distance(const Point &p1, const Point &p2) {
	int x = p1.first - p2.first;
	int y = p1.second - p2.second;
	return x * x + y * y;
}

int Solution::crossMul(const Point &p1, const Point &p2, const Point &p3) {
	int ax = p2.first - p1.first, ay = p2.second - p1.second;
	int bx = p3.first - p1.first, by = p3.second - p1.second;
	return ax * by - ay * bx;
}

vector<vector<int>> Solution::outerTrees(vector<vector<int>> &points) {
	vector<vector<int>> ret;
	if (points.size() < 4) { for (auto &vec: points) ret.push_back(vec); return ret; }
 
    vector<Point> spots;
	for (auto &vec: points) spots.push_back({vec[0], vec[1]});

	Point p0 = spots[0];
	for (auto p: spots) { 
		if (p.second < p0.second) p0 = p;
		else if (p.second == p0.second && p.first < p0.first) p0 = p; 
	}
 
    sort(spots.begin(), spots.end(), [=](const Point &p1, const Point &p2) -> bool {
		int ans = crossMul(p0, p1, p2);
		if (ans > 0) return true;
		else if (ans == 0) return distance(p0, p1) < distance(p0, p2);
		else return false; });
	
	int pos = spots.size() - 1;
	while (pos >= 1 && crossMul(p0, spots[pos], spots[pos-1]) == 0) pos--;
	reverse(spots.begin() + pos, spots.end());

	stack<Point> stk; stk.push(spots[0]); stk.push(spots[1]);
	for (int i = 2; i < spots.size(); i++) {
		Point p1 = stk.top(); stk.pop();
		while (crossMul(stk.top(), p1, spots[i]) < 0) {p1 = stk.top(); stk.pop();}
		stk.push(p1);
		stk.push(spots[i]);
	}
	while (!stk.empty()) { ret.push_back({stk.top().first, stk.top().second}); stk.pop(); }
	return ret;
}