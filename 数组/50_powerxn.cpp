#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 注意n的正负
// 注意二分法的运用
// 注意数据类型和大小溢出
// 利用递归实现代码，思路比较清晰，代码也好写
// 注意递归的基准情况
class Solution {
public:
	double myPow(double x, int n);
};

double Solution::myPow(double x, int n) {
	// 基准情况
	if (n == 0)
		return 1;
	if (n == 1)
		return double(x);
	if (n < 0)
		// 边界条件 n可能是-2^31最小值，无法
		return double(1.0) / myPow(x, -(n+1)) / x;
	double ret = myPow(x, n / 2);
	if (n % 2)
		return x * ret * ret;
	else
		return ret * ret;
}

int main(int argc, char *argv[]) {
	double x;
	int n;
	Solution solution;
	while (cin >> x >> n) 
		cout << x << "的" << n << "次方为:" << solution.myPow(x, n) << endl;
	return 0;
}
