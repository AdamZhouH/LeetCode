/*
// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};
*/
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee *> record;
        for (auto ptr: employees) {
            record[ptr->id] = ptr;
        }
        return dfs(record, id);
    }
    
    int dfs(unordered_map<int, Employee *> &record, int id) {
        Employee *curr = record[id];
        int ret = curr->importance;
        for (auto id: curr->subordinates) {
            ret += dfs(record, id);
        }
        return ret;
    }
};