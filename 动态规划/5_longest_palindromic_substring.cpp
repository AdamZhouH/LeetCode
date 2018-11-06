// 5_longest_palindromic_substring.cpp

// 打印出给定字符串的一个最长回文字串
// 动态规划
// 之前，自己考虑的方向是，如何获得这个最长回文字串，其实思路已经想到了
// 但是觉得太复杂，还是要求一个二维数组，因此又往更深处去考虑
// 其实子问题是比较容易看清楚的
// 一个索引位置为i-j之间的字串，一个所以位置为i-1, j+1之间的位置的字串
// 两者考虑一种递推关系
// 如果ij为回文，则i-1 j+1是否是回文取决于i-1 j+1处的字符是否相同
// 如果相同，则i-1 j-1也是回文，否则不是
// 如果ij本身不是回文，那么必然i-1 j+1也不是回文
// 考虑完递归情况之后，考虑基准情况
// i=j 则单个字符，必然是回文， 考虑|i-j|=1，则判断两个字符是否相同
// 综上，dp[][]用于存放子问题结果，也即使ij字串是否是回文

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
	string longestPalindrome(string s);
};

string Solution::longestPalindrome(string s) {
	int n = s.size();
	// 二维数组初始化
	vector<vector<bool>> dp(n);
	for_each(dp.begin(), dp.end(), [n](vector<bool> &vec) {
		vec.resize(n, false);
// 这里说明一下为何不能在for_each中引用bool类型的变量，否则会报错
// 和bool的底层实现有关，bool不是一个完整的类型，而是依赖于其他类型，比如一般是int的实现
// 在for_each的lambda中，涉及到一个传参数的问题
// 由于vector<bool>的底层实现可能是vector<int>，因此我们在lambda中引用bool元素时，实际上引用的并不是直接的底层元素
// 而是由底层int经过类型转换之后得到的临时bool变量，而临时变量是立刻被销毁的，编译器会拒绝引用临时变量
// 因此，下面这种for_each中的lambda引用bool变量然后修改，实际上修改的是一个临时变量，编译器当然会拒绝
// 这个坑，不小心就踩到了，注意！！！
//		vec.resize(n);
//		for_each(vec.begin(), vec.end(), [] (bool &val) {
//			val = false;
//		});
	});

	int maxLength = 1;
	int start = 0;

	// 自底向上迭代，填充ij是否是回文子串的判断结果
	// 根据给出的递推公式 i==j |i-j|==1
	// 注意，实际上ij  ji都是指的同一个子串
	// 由于子串索引的两个坐标存在大小关系，并不是整个矩阵都必须填满
	// 只需要填写好上三角或者下三角部分即可
	
	for (int j = 0; j < n; j++) {
		for (int i = 0; i <= j; i++) {
			if (j - i < 2)
				dp[i][j] = (s[i] == s[j]);
			else 
				dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
			// 实时更新有关最长子串的的长度和索引的信息
			if (dp[i][j] && maxLength < (j - i + 1)) {
				maxLength = j - i + 1;
				start = i;
			}
		}
	}

	return s.substr(start, maxLength);
}

int main(void) {
	Solution solution;
	string s = "abbaabccba";
	cout << solution.longestPalindrome(s) << endl;
	return 0;
}
