#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int clumsy(int N);
};

// brute force
int Solution::clumsy(int N) {
    if (N <= 2) return N;
    if (N == 3) return 6;
    int sum = N*(N-1)/(N-2)+(N-3);
    N -= 4;
    while (N >= 4) {
        sum += (-N)*(N-1)/(N-2)+(N-3);
        N -= 4;
    }
    return sum - clumsy(N);

}


class Solution2 {
public:
    int clumsy(int N);
    int clumsy(int N, bool flag);
};

int Solution2::clumsy(int N, bool flag) {
    if (N == 3) return -6;
    if (N <= 2) return -N;
    return (-N)*(N-1)/(N-2)+(N-3) + clumsy(N-4, true);
}

int Solution2::clumsy(int N) {
    if (N == 3) return 6;
    if (N <= 2) return N;
    return clumsy(N, true) + 2*(N*(N-1)/(N-2));
    // return clumsy(N, true) + 2*N*(N-1)/(N-2) 这样写结果错误，因为2不能直接乘以N，这可能会扩大结果
}