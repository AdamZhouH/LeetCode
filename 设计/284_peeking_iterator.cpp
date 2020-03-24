// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.

// 比较简单，因为Iterator不提供实际的peek操作，需要我们模拟
// 调用时，如果是此前没有缓存peek的值，则调用next取出一个值，放在缓存中
// 当调用next时，先判断是否存在缓存值，存在则直接返回，而不是调用实际的Iterator::next()
// hasNext同理，先判断是否存在缓存
// 同理其他接口的实现

class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
        isCached = false;
	}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        if (isCached)
            return cache;
        if (hasNext()) {
            cache = next();
            isCached = true;
            return cache;
        } else
            return -1;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
	    if (isCached) {
            isCached = false;
            return cache;
        }
        return Iterator::next();
	}

	bool hasNext() const {
	    if (isCached)
            return true;
        return Iterator::hasNext();
	}
private:
    int cache;
    bool isCached;
};
