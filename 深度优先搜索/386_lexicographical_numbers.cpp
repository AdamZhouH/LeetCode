#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> lexicalOrder(int thresh);
	void lexicalOrder(int start, int thresh, vector<int> &ret);
};

vector<int> Solution::lexicalOrder(int thresh) {
    vector<int> ret;
	for (int i = 1; i <= 9; i++) {
		lexicalOrder(i, thresh, ret);
	}
    return ret;
}

void Solution::lexicalOrder(int start, int thresh, vector<int> &ret) {
	if (start > thresh) {
		return;
	}
//	cout << start << ' ';
    ret.push_back(start);
	for (int i = 0; i <= 9; i++) {
		lexicalOrder(start * 10 + i, thresh, ret);
	}
}

// 以上是最基本的暴力dfs方法求解
// 再次考虑时间复杂度和空间复杂度的优化的方法

// 利用迭代的方法的做法

class Question {
public:
	vector<int> lexicalOrder(int thresh);
};

vector<int> Question::lexicalOrder(int thresh) {
	int val = 1;
	vector<int> number(thresh, 0);
	for (int i = 0; i < thresh; i++) {
		number[i] = val;
		if (10 * val <= thresh) {
			val = 10 * val;
		} else {
			if (val >= thresh)
				val /= 10;
			val++;
			while (val % 10 == 0) 
				val / = 10;
		}
	}
	return number;
}

int main(void) {
	int thresh;
	Question ques;
	while (cin >> thresh) {
		auto ret = ques.lexicalOrder(thresh);
		for_each(ret.begin(), ret.end(), 
			[](int val) {
				cout << val << ' ';
			}
		);
	}
	return 0;
}