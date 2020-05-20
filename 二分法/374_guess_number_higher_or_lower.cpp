/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


// 理解好题目意思，非常基础的二分查找算法
class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int ret = guess(mid);
            if (ret == 0) return mid;
            if (ret == 1) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};