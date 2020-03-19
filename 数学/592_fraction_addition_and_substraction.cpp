#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:
    string fractionAddition(string expression);
    void parse(const string &expression, int idx, vector<pair<int, pair<int, int>>> &nums);
    pair<int, pair<int, int>> addTwoFraction(const pair<int, pair<int, int>> &lhs, const pair<int, pair<int, int>> &rhs); 
    int getGcd(int a, int b);
    
};

string Solution::fractionAddition(string expression) {
    vector<pair<int, pair<int, int>>> nums;
    parse(expression, 0, nums);
    pair<int, pair<int, int>> sum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        sum = addTwoFraction(sum, nums[i]);
    }
    // 构造结果字符串
    string ret;
    if (sum.first == -1)
        ret = "-";
    ret = ret + to_string(sum.second.first) + "/" + to_string(sum.second.second);
    return ret;
}

inline
void Solution::parse(const string &expression, int idx, vector<pair<int, pair<int, int>>> &nums) {
    if (idx >= expression.size())
        return;
    bool positive = true;
    if (!isdigit(expression[idx])) {
        if (expression[idx] == '-')
            positive = false;
        idx++;
    }
    // 解析出一个分数
    int i = idx;
    int x, y;
    while (i < expression.size() && expression[i] != '+' && expression[i] != '-') {
        if (expression[i] == '/') {
            x = stoi(expression.substr(idx, i - idx));
            idx = i + 1;
        }
        i++;
    }
    // idx指向分母的第一个字符，这种情况下是一定存在的，因为/符号后一定有分母
    y = stoi(expression.substr(idx, i - idx));
    nums.push_back({(positive ? 1:-1), {x, y}});
    parse(expression, i, nums);
}


pair<int, pair<int, int>> Solution::addTwoFraction(const pair<int, pair<int, int>> &lhs, const pair<int, pair<int, int>> &rhs) {
    int y = lhs.second.second * rhs.second.second;
    int x = lhs.first * lhs.second.first *rhs.second.second + rhs.first * rhs.second.first * lhs.second.second;
    bool positive = (x > 0);
    x = (x > 0) ? x: -x;
    // 化简分数 (利用辗转相除法找到分子分母的最大公约数)
    // 由于分子x可能为0，导致得到的最大公约数也是0，这时不能除，直接返回一个结果，而分母设置为1即可
    if (!x) {
        return {1, {0, 1}};
    }
    auto gcd = getGcd(y, x);
    return {(positive ? 1 : -1), {x / gcd, y / gcd}};
}

// 辗转相除法不是这么写的ok？不要太自信了
/*
int Solution::getGcd(int x, int y) {
    if (x < y)
        return getGcd(y, x);
    if (x == y)
        return x;
    else 
        return getGcd(x - y, y);
}
*/
int Solution::getGcd(int x, int y) {
    if (x < y)
        return getGcd(y, x);
    return y == 0 ? x : getGcd(y, x % y);
}

int main(void) {
    
    string expression;
    Solution solution;
    while (cin >> expression) {
        cout << solution.fractionAddition(expression) << endl;
    }

   /*
   string expression = "+1/98-1/2";
   Solution solu;
   cout << solu.fractionAddition(expression) << endl;
   */
    return 0;
}