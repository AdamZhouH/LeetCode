// n个人，相互之前可以发送好友请求，ages[i]表示i的年龄
// x如果同时满足下面三个条件，那么就会向y发送请求
//     age[y] > 0.5*age[x]+7
//     age[y] <= age[x]
//     age[y] <= 100 || age[x] >= 100
// 第三个条件实际上蕴含在前两个条件中
// 假如age[x] < 100，由于age[y]要小于等于age[x]，所以age[y]<=100一定成立
// 综上，在前两个条件满足的情况下，第三个条件恒成立，因此直接考虑前两个条件约束的范围即可
// 针对数组中每个人（即x），找到相应的y的个数，并计数
// 显然，age[x]已知，并且可以找到age[y]的相应范围
// 首先，我们可以将数组ages排序，按照年龄从小到大
// 那么：在ages中搜索时，则可以使用二分来加快查找，从而迅速找到age[y]的范围
// 由于统计请求个数是包括双向的，因此针对每个元素都需要查找一次

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    int numFriendRequests(vector<int>& ages);
};

int Solution::numFriendRequests(vector<int>& ages) {
    if (ages.size() <= 1) return 0;
    int ret = 0;
    sort(ages.begin(), ages.end());

    for (int i = 0; i < ages.size(); i++) {
        int low = upper_bound(ages.begin(), ages.end(), ages[i]*0.5+7) - ages.begin();
        int high = upper_bound(ages.begin(), ages.end(), ages[i]) - ages.begin();
        ret += max(0, high - low - 1);
    };
    return ret;
}
