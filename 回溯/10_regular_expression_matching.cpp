
// 这道题主要考察有限自动状态机中各个状态的转换，字符串匹配过程中下一个状态的选择和相应的条件

// 字符串的正则匹配，涉及到每个匹配状态的转换，可以涉及到有限状态自动机
// 考虑两个指针，分别指向matcher字符串和pattern的当前字符
// 同时，匹配当前字符的同时，必然需要考虑下一个字符是否是*元字符
// 如果下一个字符是*，即使当前字符并不匹配，那么可以视为pattern中的当前字符并不出现
// pattern的指针直接+2，进入下一个字符匹配的状态，macher的指针+1
// 同时考虑，pattern的当前字符也可能是.，那么这一步匹配可选择性就很多

// 这种情况下，pattern两个字符是.*，可选择的匹配状态转换有：
// 1.matcher的当前字符去匹配当前的pattern的.，然后matcher指针+1，pattern的指针+2，表示当前字符匹配一次
// 2.matcher的当前字符并不匹配pattern的.，表示忽略，然后matcher指针不变，pattern指针+2
// 3.matcher的当前字符不止一次的匹配pattern的.，然后matcher指针+1，pattern指针不变，表示还停留在.的匹配过程中

// 考虑pattern的两个字符是 '普通字符'* 的形式
// 1.匹配一次之后就转换到下一个字符的匹配状态，然后matcher指针+1，pattern指针+2
// 2.停在匹配多次的状态，每次只要mattern指针+1，然后pattern的指针不变
// 3.当前字符不匹配，但是可以忽略掉，所以仍然是合法的匹配，此时matcher指针不变，pattern指针+2

// 如果下一个字符不是*，则考虑当前字符匹配
// 具体情况和上面分析差不多
// 当前字符都是普通字符，直接返回匹配结果(递归)
// 如果pattern当前字符是元字符，则可以匹配任何一种情况

// 采用递归的写法，注意基准情况，当pattern完毕，matcher还没完毕，那么匹配必然是失败的
// 同理，pattern还没完毕，matcher已经走完，那么匹配也是失败的
// 如果同时走到字符串结尾，那么必然是成功的
// 其余情况则递归判断

// 综合以上情况给出算法实现代码
// 代码正确但是超时，说明写的很丑陋，需要进一步优化逻辑流程
// 结果就是，DFS算法严重超时，应当使用动态规划的方法去思考

// 子问题 dp[i][j] 表示 s[0-i] 和p[0-j]是否匹配
// 然后考虑边界情况

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p);
    bool dfs_(string matcher, string pattern);
    bool dp_mathod(string matcher, string pattern);
};

bool Solution::isMatch(string s, string p) {
    return dfs_(s, p);
}

bool Solution::dfs_(string matcher, string pattern) {
    // 基准情况，当pattern和matcher同时为空，匹配完成
    // 当pattern为空，但是matcher不为空，匹配失败
    if (pattern.empty())
        return matcher.empty();
    // 考虑pattern的当前字符的下一个字符不是*，下一个字符也可能并不存在
    if (pattern.size() == 1 || pattern[1] != '*') {
        if (matcher.empty())
            return false;
        if (pattern[0] == '.' || matcher[0] == pattern[0])
            return dfs(matcher.substr(1), pattern.substr(1));
        return false;
    } 
    // 说明pattern下一个字符一定存在并且为*通配字符
    // 则考虑当前matcher字符可以乎略，可以匹配一次，也可以匹配多次
    if (matcher.empty())
        return dfs(matcher, pattern.substr(2));

    if (pattern[0] != '.' && pattern[0] != matcher[0])
        return dfs(matcher.substr(1), pattern.substr(2));
    else
        return dfs(matcher.substr(1), pattern.substr(2)) ||
               dfs(matcher.substr(1), pattern) ||
               dfs(matcher, pattern.substr(2));
}

int main(void) {
    string matcher, pattern;
    Solution solution;
    while (cin >> matcher >> pattern)
        cout << solution.isMatch(matcher, pattern) << endl;
    return 0;
}