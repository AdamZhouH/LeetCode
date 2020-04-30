#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isHappy(int n);
};

bool Solution::isHappy(int n) {
    if (n == 1) return true;
    unordered_set<int> record;
    while (n != 1) {
        record.insert(n);
        int tmp = n;
        n = 0;
        while (tmp != 0) {
            n += (tmp % 10) * (tmp % 10);
            tmp /= 10;
        }
        if (record.count(n)) return false;
    }
    return true;
}
