#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B);
};

// 题目保证答案存在
// 实际上就是先找到diff
// 然后针对A中每个元素，查看对应的元素在B中是否存在，存在则说明找到，直接返回即可
vector<int> Solution::fairCandySwap(vector<int>& A, vector<int>& B) {
	int sumOfA = accumulate(A.begin(), A.end(), 0);
	int sumOfB = accumulate(B.begin(), B.end(), 0);
	int diff = (sumOfA - sumOfB) / 2;
	unordered_set<int> elemOfB(B.begin(), B.end());
	for (auto val: A) {
		if (elemOfB.find(val - diff) != elemOfB.end()) 
            return {val, val - diff};
	}
	return {};
}