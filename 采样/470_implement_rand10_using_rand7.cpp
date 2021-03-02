#include <vector>
#include <iostream>
using namespace std;

// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    // 这道题主要是考察分布的利用
    // rand7是1-7的均匀分布，只有7个数字，不够10个数字
    // 因此想办法扩大生成的数字的个数，同时保证数字出现的概率的均等性
    // 常用的办法就是先凑处0～n-1个数字，然后通过*n+[1~n]构造出
    // 从1-n*n个均等概率出现的数字(1,2,3...n*n)   
    // 因此，这道题就是用(rand7()-1)*+rand7()
    // 由于生成49个数，而我们只需要10个数字，实际上我们取前40个即可，最后9个去掉                                    
    int rand10() {
        int num = (rand7() - 1) * 7 + rand7();
        while (num > 40) {
            num = (rand7() - 1) * 7 + rand7();
        }
        return num % 10 + 1;
    }
};
