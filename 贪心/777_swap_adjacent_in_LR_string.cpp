#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

// 算法思路
// 观察交换的条件和交换特点，如果L左边有X，则L可以一直往左走
// 如果R右边有个X，则R可以一直往右走
// 实际上，因为LR不可能越过彼此，因此，如果把两个串的X都去掉，那么最终两个字符肯定是一致的
// 同时，由于L是往左边移动，因此L移动后，两者对应的下标的关系应该是原串更大
// 同理，对于R，那么应该是原串中的下标比第二个串的对应的R的下标小
// 以上两个条件都可以满足，那么一定可以通过这种交换规则使得原串变为目标串

class Solution {
public:
    bool canTransform(string start, string end);
};

bool Solution::canTransform(string start, string end) {
    int len = start.size();
    string s, e;
    vector<int> sl, el, sr, er;
    
    for (int i = 0; i < len; i++) {
        if (start[i] != 'X') {
            s.push_back(start[i]);
            if (start[i] == 'L')
                sl.push_back(i);
            else
                sr.push_back(i);
        }
        if (end[i] != 'X') {
            e.push_back(end[i]);
            if (end[i] == 'L')
                el.push_back(i);
            else
                er.push_back(i);
        }
    }
    
    if (s != e)
        return false;
    
    for (int i = 0; i < sl.size(); i++)
        if (sl[i] < el[i])
            return false;
    for (int i = 0; i < sr.size(); i++)
        if (sr[i] >er[i])
            return false;
    
    
	return true;
}