#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

// 使用蓄水池抽样算法
// 遍历一次数组
// 每次当遇到和target相同的值时，使用蓄水池抽样思路
class Solution {
public:
	Solution(vector<int> &nums);
	int pick(int target);
private:
	default_random_engine e;
	vector<int> &vec;
};

// 初始化列表中不能出现this指针，因为这时候对象还没有构造完成
// 并不存在this指针
Solution::Solution(vector<int> &nums) : vec(nums) { };

int Solution::pick(int target) {
	int i = 0;
	int ret;
	// 找到第一个target的下标位置
	for (; i < vec.size(); i++) {
		if (vec[i] == target) {
			ret = i;
			break;
		}
	}
	// 蓄水池抽样即可
	int j = i + 1;
	int cnt = 2;
	while (j < vec.size()) {
		if (vec[j] == target) {
			uniform_int_distribution<unsigned> u(1, cnt);
			int var = u(e);
			if (var == 1) {
				ret = j;
			}
			cnt++;
		}
		j++;
	}
	return ret;
}

int main(int argc, char *argv[]) {
	vector<int> vec{1, 2, 3, 3, 3};
	int target;
	Solution solution(vec);
	while (cin >> target) {
		cout << solution.pick(target) << endl;
	}
	return 0;
}
