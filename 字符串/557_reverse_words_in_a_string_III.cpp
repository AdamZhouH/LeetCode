#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string reverseWords(string s);
};

string Solution::reverseWords(string s) {
    if (s.empty())
        return s;
    istringstream line(s);
    string word, ret;
    while (line >> word) {
        reverse(word.begin(), word.end());
        ret.append(word);
        ret.append(1, ' ');
    }
    if (!word.empty())
        ret.pop_back();
    return ret;
}