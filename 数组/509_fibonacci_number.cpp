#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int fib(int N);
};

int Solution::fib(int N) {
    if (N <= 1) return N;
    int a = 0, b = 1;
    for (int i = 2; i <= N; i++) {
        int tmp = a + b;
        a = b;
        b = tmp;
    }
    return b;
}
