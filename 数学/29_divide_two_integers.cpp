#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

// 首先尝试利用减法做
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == 0)
            return 0;
        int sign = 1;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0))
            sign = -1;
        int count = 0;;
        dividend = abs(dividend), divisor = abs(divisor);
        // 不能少=号(商为1的情况)
        while (dividend >= divisor) {
            count += 1;
            dividend -= divisor;
        }

        return (sign > 0 ? count : -count);
    }
};

// 特殊case没有注意到
// negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (solution.cpp)
// 需要注意输入的边界


// 显然减法的效率是非常低的，因为当被除数很大而除数很小，加入除数为1，那么是时间复杂度会很大
// 因此考虑增加被除数的大小，每次减去的数增大，考虑利用位移给除数做乘法，不断逼近被除数
// 实际上是二分法的应用

class Solution2 {
public:
	int divide(int divident, int divisor);
	int help(int divident, int divisor);
};

int Solution2::help(int divident, int divisor) {
	if (divisor > divident)
		return 0;
	int ret = 0;
    long currdivisor = divisor, currdivident = divident, mask = 1;
	while (currdivisor <= currdivident) {
		ret += mask;
		currdivident -= currdivisor;
        // 如果变量类型为int，这里可能溢出，currdivisor + currdivisor超出int类型的范围
		currdivisor += currdivisor;
		mask += mask;
	}
	return ret + help(currdivident, divisor); 
}

int Solution2::divide(int divident, int divisor) {
	// 边界判断
	if (divisor == 1)
		return divident;
	if (divident == 0)
		return 0;
	if (divisor == -1 && divident == INT_MIN)
		return INT_MAX;
	int sign = (divident ^ divisor) < 0 ? -1 : 1;
	// 当divident或者divisor为INT_MIN时，abs会导致溢出，如何解决？
	if (divisor == INT_MIN)
		return divident == INT_MIN ? 1 : 0;
	int ret;
	if (divident == INT_MIN) {
		divident += abs(divisor);
		ret = 1 + help(abs(divident), abs(divisor));
	} else {
		ret = help(abs(divident), abs(divisor));
	}
	return sign > 0 ? ret : -ret;
}

