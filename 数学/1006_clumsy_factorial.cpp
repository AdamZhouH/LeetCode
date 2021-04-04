#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    int clumsy(int N);
};

// 暴力递归
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

// 用栈模拟加减乘除计算，这里由于存在优先级问题，因此遇到乘除法必须先计算到一个结果，然后放入栈
// 如果符号是减，则将元素的相反数放入栈中（其实总体来看和计算器处理一样，加减先不计算，先计算优先级高的乘除法）
// 最后栈内所有元素求和即可
int clumsy(int N) {
    if (N == 3) return 6;
    if (N <= 2) return N;
    int op = 0;
    int ret = 0;
    stack<int> stk; stk.push(N); N--;
    while (N >= 1) {
        if (op == 0) { // *
            int lhs = stk.top(); stk.pop();
            stk.push(lhs*N);
        } else if (op == 1) { // /
            int lhs = stk.top(); stk.pop();
            stk.push(lhs/N);
        } else if (op == 2) { // +
            stk.push(N);
        } else { // -
            stk.push(-N);
        }
        op = (op + 1) % 4;
        N--；
    }
    while (!stk.empty()) {
        ret += stk.top();
        stk.pop();
    }
    return ret;
}
