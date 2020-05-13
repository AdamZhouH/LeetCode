#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int superPow(int a, vector<int>& b);
    int superPow(int a, vector<int>& b, int end);
    int myPow(int a, int b);
};

// 做这题之前，需要明白的一点：(a*b)%c=((a%c)*(b%c))%c
// 之后就是通过递归思想来做了，用了快速幂的算法
// 快速幂思想求解a^bMOD1377的结果
// 由于a b为正整数，因此情况简化了很多

int Solution::myPow(int a, int b) {
    if (b == 1) return a % 1337;
    int ans = 1, base = a;
    while (b) {
        if (b%2) ans = ((ans % 1337 ) * (base % 1337)) % 1337;
        base = ((base % 1337) * (base % 1337)) % 1337;
        b /= 2;
    }
    return ans;
}

int Solution::superPow(int a, vector<int>& b, int end) {
    if (end == 0)
        return myPow(a, b[end]);
    return ((myPow(a, b[end]) % 1337 ) * (myPow(superPow(a, b, end-1), 10) % 1337)) % 1337;
}

int Solution::superPow(int a, vector<int> &b) {
    if (b.empty()) return 1;
    return superPow(a, b, b.size()-1);
}
