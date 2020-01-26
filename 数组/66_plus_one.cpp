#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Solution {
public:
	vector<int> plusOne(vector<int> &digits);
};

vector<int> Solution::plusOne(vector<int> &digits) {
	if (digits[digits.size() - 1] != 9) {
		digits[digits.size() - 1] += 1;
		return digits;
	}
	std::reverse(digits.begin(), digits.end());
	digits[0] = 0;
	int carry = 1;
	for (int i = 1; i < digits.size(); i++) {
		int var = digits[i] + carry;
		carry = var / 10;
		if (var >= 10) {
			digits[i] = var % 10;
		} else {
			digits[i] = var;
			break;
		}
	}
	if (carry)
		digits.push_back(carry);
	std::reverse(digits.begin(), digits.end());
	return digits;
}
