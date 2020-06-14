#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findNthDigit(int n) {
        if (n <= 9) return n;
        long k = 0, sum = 0;
        while (sum < n)
            k++, sum += 9 * pow(10, k-1) * k;
        // 分别判断数字有几位，是哪个数字，在该数字的第几位
        int left = n - (sum - 9 * pow(10, k-1) * k);
        int num = left % k == 0 ? left / k + pow(10, k-1) - 1 : left / k + pow(10, k-1);
        left = left % k == 0 ? k : left % k;
        left = k - left;
        int ans = num % 10;
        while (left--) {
            num /= 10;
            ans = num % 10;
        }
        return ans;
    }
};
