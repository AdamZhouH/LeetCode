#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool equationsPossible(vector<string>& equations);
    void merge(char x, char y, unordered_map<char, char>& uf);
    char find(char x, unordered_map<char, char>& uf);
};

char Solution::find(char x, unordered_map<char, char> &uf) {
    if (uf[x] == x) return x;
    return uf[x] = find(uf[x], uf);
}

void Solution::merge(char x, char y, unordered_map<char, char>& uf) {
    x = find(x,uf), y = find(y,uf);
    if (x != y)
        uf[x] = y;
}

bool Solution::equationsPossible(vector<string>& equations) {
    unordered_map<char, char> uf;
    for (auto &v: equations) {
        if (!uf.count(v[0])) uf[v[0]] = v[0];
        if (!uf.count(v[3])) uf[v[3]] = v[3];
    }
    for (auto &v: equations) if (v[1] == '=') merge(v[0], v[3], uf);
    for (auto &v: equations) {
        if (v[1] == '=') continue;
        if (find(v[0], uf) == find(v[3], uf)) return false;
    }
    return true;
}
