#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

// LRU缓存算法的实现
// 由于需要再O(1)时间内完成get 和 put 操作，因此除了链表之外
// 还需要一个map用于加速get的查找过程
// 具体的思路如下（本质上考察的是LRU的思想和链表的操作，期间需要注意到的一些问题）
// 针对get操作，存在则返回value，不存在则返回-1，直接从map中寻找
// 由于要保证LRU特性，因此，每次被访问到的节点，需要移动到链表的首部
// 针对于put操作，如果已经存在key，那么直接更改对应的value值
// 如果这个key本身不存在，那么需要插入到链表中
// 如果当前的空间没有满，直接插入到链表的首部，同时更新map中的值
// 如果链表此时空间已经满，那么需要移除链表中最后一个节点，同时map中也需要移除
// 然后更新链表，并插入链表的首部，然后更新map中存储的数值

// 这个是在leetcode上看到的，利用了lambda表达式和全局变量的初始化，把代码写在lambda表达式中
// 由于x是全局的静态变量，会先执行初始化操作，因此会执行这个lambda表达式，很巧秒的方法

static int x = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class LRUCache {
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
    ~LRUCache();
private:
	typedef struct Node {
		int key;
		int value;
		Node *prev, *next;
		Node(int k, int v, Node *p, Node *q) 
			: key(k), value(v), prev(p), next(q) { }
	} Node;
private:
	void adjust(Node *node);
	void insertToFirst(int key, int value);
private:
	Node *head, *tail;
	map<int, Node *> records;
	int num;
	int cap;
};

LRUCache::LRUCache(int capacity) : head(nullptr), tail(nullptr), cap(capacity), num(0) { }

LRUCache::~LRUCache() {
	while (head) {
		auto temp = head;
		head = head->next;
		delete temp;
	}
}

void LRUCache::adjust(Node *node) {
	assert(head); assert(tail), assert(node);
	if (node == head)
		return;
	if (node == tail) {
		tail = node->prev;
		tail->next = nullptr;
		node->next = head;
		head->prev = node;
		node->prev = nullptr;
		head = node;
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = head;
		node->prev = nullptr;
		head->prev = node;
		head = node;
	}
}

void LRUCache::insertToFirst(int key, int value) {
	Node *node = new Node(key, value, nullptr, nullptr);
	if (!head) {
		head = tail = node;
	} else {
		head->prev = node;
		node->next = head;
		head = node;
	}
	num++;
	records[key] = node;
}

int LRUCache::get(int key) {
	auto it = records.find(key);
	if (it != records.end()) {
		int val = it->second->value;
		adjust(it->second);
		return val;
	} else {
		return -1;
	}
}

void LRUCache::put(int key, int value) {
	auto it = records.find(key);
	if (it != records.end()) {
		it->second->value = value;
		adjust(it->second);		
	} else {
		if (num < cap) {
			insertToFirst(key, value);
		} else {
			records.erase(tail->key);
			tail->key = key;
			tail->value = value;
			records[key] = tail;
			adjust(tail);
		}
	}
}

int main(void) {
 	LRUCache cache(2);
 	string op;
 	int key, value;
 	while (cin >> op) {
 		if (op == "get") {
 			cin >> key;
 			cout << cache.get(key);
 		} else if (op == "put") {
 			cin >> key >> value;
 			cache.put(key, value);
 		}
 	}
 	return 0;
 }
