#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
	int solution(const vector<int> &numbers);
};

int Solution::solution(const vector<int> &numbers) {
	int currRemote = 0; // 当前步数内可达的最远位置
	int preRemote = 0;  // 之前一步可达的最远位置
	int steps = 0;
	for (int i = 0; i < numbers.size() && i <= currRemote; i++) {
		if (i > preRemote) {
			steps++;
			preRemote = currRemote;
		}
		currRemote = max(currRemote, numbers[i] + i);
	}
	return steps;
}

int main(void) {
	vector<int> numbers = {1, 2, 1, 1, 1};
//	vector<int> numbers = {2, 1};	
//	vector<int> numbers = {2, 3, 1, 1, 4};
    Solution solu;
	cout << "最少需要 " << solu.solution(numbers) << "步" << endl;
	return 0;
}
