#include <iostream>
#include <string>
using namespace std;

#define OPTIMIZE
class Solution {
public:
    string intToRoman(int num);
};
// 很蠢萌的写法
#ifndef OPTIMIZE
unordered_map<int, char> help = {
    {1,'I'}, {5,'V'}, {10,'X'}, {50,'L'}, {100,'C'}, {500,'D'}, {1000,'M'},
};

string Solution::intToRoman(int num) {
    if (num == 0) return "";
    string ret = "";
    // 处理千位
    if (num >= 1000) {
        ret += string(num/1000, help[1000]);
        num %= 1000;
    }
    // 处理百位
    if (num >= 900) {
        ret += "CM";
        num %= 100;
    } else if (num >= 500) {
        ret += "D";
        ret += string((num-500)/100, help[100]);
        num %= 100;
    } else if (num >= 400) {
        ret += "CD";
        num %= 100;
    } else if (num >= 100) {
        ret += string(num/100, help[100]);
        num %= 100;
    }
    // 处理十位
    if (num >= 90) {
        ret += "XC";
        num %= 10;
    } else if (num >= 50) {
        ret += "L";
        ret += string((num - 50)/10, help[10]);
        num %= 10;
    } else if (num >= 40) {
        ret += "XL";
        num %= 10;
    }  else if (num >= 10) {
        ret += string(num/10, help[10]);
        num %= 10;
    }
    // 处理个位
    if (num == 9) {
        ret += "IX";
        return ret;
    } else if (num >= 5) {
        ret += "V";
        ret += string(num-5, help[1]);
        return ret;
    } else if (num == 4) {
        ret += "IV";
        return ret;
    } else {
        ret += string(num, help[1]);
    }
    return ret;
}
#else
// 更加好的枚举思路
const string arr[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM"}
};

string Solution::intToRoman(int num) {
    string ret;
    ret += arr[3][num/1000];
    ret += arr[2][(num%1000)/100];
    ret += arr[1][(num%100)/10];
    ret += arr[0][num%10];
    return ret;
}
#endif
int main(void) {
    Solution slu;
    int var;
    while (cin >> var) {
        cout << slu.intToRoman(var) << endl;
    }
    return 0;
}