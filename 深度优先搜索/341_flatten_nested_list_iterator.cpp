#include <vector>
#include <iostream>
using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

// 可以想办法先把元素全部拆开，做一个预处理，存放到vector中
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        build(nestedList);
    }
    
    int next() {
        return elems[idx++];
    }
    
    bool hasNext() {
        return idx < elems.size();
    }
private:
    void build(vector<NestedInteger> &nestedList) {
        for (int i = 0; i < nestedList.size(); i++) {
            if (nestedList[i].isInteger()) {
                elems.push_back(nestedList[i].getInteger());
            } else { 
                build(nestedList[i].getList()); 
            } 
        }
    }
    
    vector<int> elems;
    
    int idx = 0;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
