// 面向测试用例编程
// 几个奇葩的测试用例
// "1    "    true
// "+.8"      true        // 第一次知道这种也能是true?
// ".-4"      false
// "-."       false       // 我真的服了你了 第1480个用例
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        // 不要漏了处理掉前缀部分的空格字符或者后缀部分的空格字符
        int i = 0, j = s.size()-1;
        while (i < s.size() && isblank(s[i])) i++;
        while (j >= 0 && isblank(s[j])) j--;
        if (i > j) return false;
        else s = s.substr(i, j-i+1);
        // 科学计数判断（左侧为小数或者整数，右侧为整数）
        // 小数判断（则小数点左侧右侧必须为整数或者左侧为空或者右侧为空）
        // 整数判断
        if (s.find('e') != string::npos) return isSicenceNotation(s);
        else if (s.find('.') != string::npos) return isDecimal(s);
        else return isInteger(s);
    }

    bool isSicenceNotation(string s) {
        auto pos = s.find_first_of('e');
        assert(pos != string::npos);
        string left = s.substr(0, pos);
        string right = s.substr(pos + 1);
        return (isInteger(left) || isDecimal(left)) && isInteger(right);
    }

    bool isDecimal(string s) {
        auto pos = s.find_first_of('.');
        if (pos == string::npos) return false;
        string left = s.substr(0, pos);
        string right = s.substr(pos + 1);
        if (left.empty()) return isInteger(right) && isdigit(right[0]);
        if (right.empty()) return isInteger(left);
        return (isInteger(left) || left == "+" || left == "-") && isInteger(right) && isdigit(right[0]);
    }

    bool isInteger(string s) {
        if (s.empty()) return false;
        bool flag = true;
        int start = 0;
        if (!isdigit(s[0]) && s[0] != '+' && s[0] != '-') return false;
        else {
            if (!isdigit(s[0])) {
                if (s.size() == 1) return false;
                else start = 1;
            }
        }
        for (; start < s.size(); start++) {
            if (!isdigit(s[start])) return false;
        }
        return true;
    }
};
