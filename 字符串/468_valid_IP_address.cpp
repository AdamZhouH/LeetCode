#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Solution {
public:
    string validIPAddress(string IP);
    string handleip4(string IP);
    string handleip6(string IP);
};

string Solution::validIPAddress(string IP) {
    if (IP.empty()) return "Neither";
    if (IP.find('.') != string::npos) return handleip4(IP);
    else if (IP.find(':') != string::npos) return handleip6(IP);
    else return "Neither";
}

string Solution::handleip4(string IP) {
    int dotcnt = 0;
    for (auto &c: IP) if (c == '.') c = ' ', dotcnt++;
    if (dotcnt != 3) return "Neither";
    istringstream input(IP); string tmp;
    int cnt = 0;
    while (input >> tmp) {
        cnt++;
        if (cnt > 4) return "Neither";
        assert(!tmp.empty());
        if ((tmp[0] == '0' && tmp.size() > 1) || tmp.size() > 3) return "Neither";
        for (auto c: tmp) if (!isdigit(c)) return "Neither";
        int n = stoi(tmp);
        if (n >= 256) return "Neither";
    }
    return cnt == 4 ? "IPv4" : "Neither";
}

string Solution::handleip6(string IP) {
    int dotcnt = 0;
    for (auto &c: IP) if (c == ':') c = ' ', dotcnt++;
    if (dotcnt != 7) return "Neither";
    istringstream input(IP); string tmp;
    int cnt = 0;
    while (input >> tmp) {
        cnt++;
        if (cnt > 8) return "Neither";
        assert(!tmp.empty());
        if (tmp.size() > 4) return "Neither";
        for (auto &c: tmp) {
            if (!isalnum(c)) return "Neither";
            if (isdigit(c)) continue;
            if (isalpha(c)) {
                c = tolower(c);
                if (c < 'a' || c > 'f') return "Neither";
            }
        }
    }
    return cnt == 8 ? "IPv6" : "Neither";
}