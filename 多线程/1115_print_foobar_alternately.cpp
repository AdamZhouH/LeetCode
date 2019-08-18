// 两个不同的线程共用一个FooBar实例
// 其中一个线程调用foo方法
// 另外一个调用bar方法
// 要求foobar被输出n次

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <functional>

using namespace std;


class FooBar {
private:
	int n;
	bool flag;
	pthread_mutex_t mutex;
	pthread_cond_t condition;
public:
	FooBar(int n) {
		this->n = n;
		flag = true;
		// 锁和条件变量的初始化
		pthread_mutex_init(&mutex, nullptr);
		pthread_cond_init(&condition, nullptr);
		// mutex = PTTHREAD_MUTEX_INITIALIZER;
		// condition = PTHREAD_COND_INITIALIZER;
	}

	void foo(function<void()> printFoo);

	void bar(function<void()> printBar);
};

// 从题目分析，foobar必选按照先后次序输出foo和bar字符串，并且一共输出10次
// 那么foo和bar函数的调用必须满足一个先后关系，必须在foo先调用，然后bar才能调用
// 定义好第一次调用foo和bar的次序好，接下来两者的调用都需要相互等待
// 考虑使用条件变量和锁，设置一个条件，用于让foo和bar函数所在的线程进行等待

void FooBar::foo(function<void()> printFoo) {
	for (int i = 0; i < n; i++) {
    	pthread_mutex_lock(&mutex);
    	while (!flag)
    		pthread_cond_wait(&condition, &mutex);
    	printFoo();
    	flag = false;
    	pthread_cond_signal(&condition);
    	pthread_mutex_unlock(&mutex);
    }
}


void FooBar::bar(function<void()> printBar) {
	for (int i = 0; i < n; i++) {
    	pthread_mutex_lock(&mutex);
    	while (flag)
    		pthread_cond_wait(&condition, &mutex);
    	printBar();
    	flag = true;
    	pthread_cond_signal(&condition);
    	pthread_mutex_unlock(&mutex);
    }
}



// 以下是测试代码

const int TIMES = 10;

FooBar globalFoobar(TIMES);

function<void()> printFoo = [](){ cout << "foo"; };
function<void()> printBar = [](){ cout << "bar"; };

void *procOne(void *) {
	globalFoobar.foo(printFoo);
}
void *procTwo(void *) {
	globalFoobar.bar(printBar);
};
// Test

const int NUM = 2;
int main(int argc, char *argv[]) {
	pthread_t threads[NUM];
	pthread_create(&threads[0], nullptr, procOne, nullptr);
	pthread_create(&threads[1], nullptr, procTwo, nullptr);
	// join
	for (int i = 0; i < NUM; i++) {
		pthread_join(threads[i], nullptr);
	}
	return 0;
}