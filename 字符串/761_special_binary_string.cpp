#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 思路：取每一部分合法子串，然后将各部分子串排序，最后合并得到结果。
// 注意子串也可能是未排序的，因此是一个递归过程（类似于归并排序），这题的关键点是 排序+拆分递归。
// 之前排序怎么都没写对，后来一想，直接就两种拼接方式，哪种大就哪个在前，所以直接利用字符串比较。
class Solution {
public:
    string makeLargestSpecial(string S) {
        if (S.empty()) return S;
        vector<string> groups;
        for (int i = 0; i < S.size(); ) {
            int j = i, cnt = 0;
            while (j < S.size()) {
                if (S[j++] == '1') cnt++;
                else cnt--;
                if (cnt == 0) break;
            }
            groups.push_back("1"+makeLargestSpecial(S.substr(i+1, j-i-2))+"0");
            i = j;
        }
        // 排序函数有点小trick
        sort(groups.begin(), groups.end(), [](const string &lhs, const string &rhs) {
            return lhs+rhs > rhs+lhs ;
        });
        // 这样写也行
        // sort(groups.begin(), groups.end());
        // reverse(groups.begin(), groups.end());
        string ret = "";
        for (auto &str: groups) ret += str;
        return ret;
    }
};
