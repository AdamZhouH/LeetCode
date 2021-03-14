#include <vector>
#include <utility>
#include <list>
using namespace std;

class MyHashMap {
public:
    MyHashMap() : entrySet(kSize, new Node(0,0)){}
    
    void put(int key, int value) {
    	auto result = find(key);
    	if (result.second) {
    		result.second->value = value;
    	} else {
    		Node *newNode = new Node(key, value);
    		int idx = key % kSize;
    		newNode->next = entrySet[idx]->next;
    		entrySet[idx]->next = newNode;
    	}
    }
    
    int get(int key) {
    	auto result = find(key);
    	return result.second ? result.second->value : -1;
    }
    
    void remove(int key) {
    	auto result = find(key);
    	if (result.second) {
    		result.first->next = result.second->next;
    		result.second->next = nullptr;
    	}
    }
private:
	struct Node {
		int key;
		int value;
		Node *next;
		Node(int k, int v, Node *n = nullptr) : key(k), value(v), next(n) {  }
	};

	const int kSize = 256;

	// 二义性的错误，编译器不知道是成员函数声明还是成员变量
	// 应该利用{}初始化或者到构造函数中初始化	
	//vector<Node *> entrySet(kSize, new Node(0, 0));
	vector<Node*> entrySet;

	pair<Node *, Node *> find(int key) {
		int idx = key % kSize;
		Node *prev = entrySet[idx];
		Node *curr = entrySet[idx]->next;
		while (curr) {
			if (curr->key == key) 
				return {prev, curr};
			prev = curr;
			curr = curr->next;
		}
		return {nullptr, nullptr};
	}
};

// 或者用一下标准库，不用自己写
// 标准库的链表果然很快
class HashMap {
public:
    MyHashMap(): entrySet(kCapacity) {}
                                        
    void put(int key, int value) {
        for (auto it = entrySet[hash(key)].begin(); it != entrySet[hash(key)].end(); it++) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }
        entrySet[hash(key)].push_back(make_pair(key, value));
    }

    int get(int key) {
        for (auto it = entrySet[hash(key)].begin(); it != entrySet[hash(key)].end(); it++) {
            if (it->first == key) {
                return it->second;
            }
        }
        return -1;
    }

    void remove(int key) {
        for (auto it = entrySet[hash(key)].begin(); it != entrySet[hash(key)].end(); it++) {
            if (it->first == key) {
                entrySet[hash(key)].erase(it);
                return;
            }
        }
    }
private:
    const int kCapacity = 666;

    vector<list<pair<int, int>>> entrySet;

    int hash(int key) { return key % kCapacity; }
};