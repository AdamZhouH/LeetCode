#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
};

//  贪心思路
//  考虑从任何一个站点出发，这里假设就从0站点开始出发
//  当走到一个站点发现不可以继续往下走的时候，则说明从前面走过的任何一个站点
//  都不可能从其中一个出发，然后到达这个站点，因此也就不可能走完整个一圈
//  这是贪心算法的使用，可以想一下，然后就能明白
//  为何，因为前面到达的每一站，剩余的油量至少都是一个非负数
//  只要能到达一个站，那么剩余油量相比前一站绝对不会变成非负数
//  也就是说，从一个点出发，一直走下去，如果都可达，那么剩余的油量肯定是不会为0的
//  上一站剩余的有油量对于到达下一站是有帮助的
//  因此实际上，只需要遍历一遍，就可以找到是否存在		

int Solution::canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
	int sum = 0;
	int n = gas.size();
	//  假设就从0站点开始出发，每次判断下一站是否可以到达，不可到达，则跳出
	//  可以到达则继续走，直到走到下起始点或者不可达
	for (int i = 0; i < n; i++) {
		sum = gas[i];
		int j = i;
		while (sum > cost[j % n] && ((j + 1) % n) != i) {
			sum += gas[(j + 1) % n] - cost[j % n];
			j++;
		}
		if (((j + 1) % n) == i && (sum - cost[j % n]) >= 0)
			return i;
	}
	return -1;
}#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
};

//  贪心思路
//  考虑从任何一个站点出发，这里假设就从0站点开始出发
//  当走到一个站点发现不可以继续往下走的时候，则说明从前面走过的任何一个站点
//  都不可能从其中一个出发，然后到达这个站点，因此也就不可能走完整个一圈
//  这是贪心算法的使用，可以想一下，然后就能明白
//  为何，因为前面到达的每一站，剩余的油量至少都是一个非负数
//  只要能到达一个站，那么剩余油量相比前一站绝对不会变成非负数
//  也就是说，从一个点出发，一直走下去，如果都可达，那么剩余的油量肯定是不会为0的
//  上一站剩余的有油量对于到达下一站是有帮助的
//  因此实际上，只需要遍历一遍，就可以找到是否存在		

int Solution::canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
	int sum = 0;
	int n = gas.size();
	//  假设就从0站点开始出发，每次判断下一站是否可以到达，不可到达，则跳出
	//  可以到达则继续走，直到走到下起始点或者不可达
	for (int i = 0; i < n; i++) {
		sum = gas[i];
		int j = i;
		while (sum > cost[j % n] && ((j + 1) % n) != i) {
			sum += gas[(j + 1) % n] - cost[j % n];
			j++;
		}
		if (((j + 1) % n) == i && (sum - cost[j % n]) >= 0)
			return i;
	}
	return -1;
}