class Solution {
public:
    int compareVersion(string version1, string version2);
};

// 注意前导0的处理
int Solution::compareVersion(string version1, string version2) {
    for (auto &c: version1) if (c == '.') c = ' ';
    for (auto &c: version2) if (c == '.') c = ' ';
    vector<string> v1, v2;
    istringstream data1(version1), data2(version2);
    string tmp;
    while (data1 >> tmp) v1.push_back(tmp);
    while (data2 >> tmp) v2.push_back(tmp);
    // 考虑到字符串版本可能是大数，不能直接stoi或者stol
    // 还有注意处理默认版本的情况，可以将两组都拉到同一长度，不足补"0"即可
    if (v1.size() < v2.size()) {
        while (v1.size() < v2.size()) v1.push_back("0");
    } else if (v1.size() > v2.size()) {
        while (v2.size() < v1.size()) v2.push_back("0");
    }
    int i = 0;
    while (i < v1.size()) {
        // 去除前导0
        string s1, s2;
        auto pos = v1[i].find_first_not_of('0'); s1 = (pos == string::npos ? "": v1[i].substr(pos));
        pos = v2[i].find_first_not_of('0'); s2 = (pos == string::npos ? "": v2[i].substr(pos));
        // 判断一些特殊情况，比如都为0
        if (s1.empty() && s2.empty()) {i++;continue;}
        if (s1.size() > s2.size()) return 1;
        else if (s1.size() < s2.size()) return -1;
        else {
            for (int k = 0; k < s1.size(); k++) {
                if (s1[k] > s2[k]) return 1;
                else if (s1[k] < s2[k]) return -1;
            }
        }
        i++;
    }
    return 0;
}

