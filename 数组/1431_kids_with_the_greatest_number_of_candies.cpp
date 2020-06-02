#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies);
};

vector<bool> Solution::kidsWithCandies(vector<int>& candies, int extraCandies) {
    vector<bool> ret;
    int maxcandies = INT_MIN;
    for (auto num: candies) maxcandies = max(maxcandies, num);
    for (auto num: candies) ret.push_back((num + extraCandies >= maxcandies) ? true : false);
    return ret;
}