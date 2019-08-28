// 交替打印 0 奇数 偶数
// A线程调用打印0 B线程调用打印奇数 C线程调用打印偶数
// 例子，当n=2，打印结果为0102, 共2n个数

// 思路
// 锁+条件变量
// 0线程打印完后通知奇数线程
// 奇数线程打印完后通知0线程
// 0程打印完后通知偶数线程
// 偶数线程打印完后再通知0线程
//		最开始0线程先判断条件变量，满足条件后打印0，然后激活非0线程

#include <iostream>
#include <pthread.h>
#include <vector>
#include <functional>

using namespace std;

class ZeroEvenOdd {
	private:
		int n;
	
		int number;
		bool zeroFlag = true;
		bool evenFlag = false;
		pthread_mutex_t mutexlock;
		pthread_cond_t conds[3];

	public:
		ZeroEvenOdd(int n);
		void zero(function<void (int)> printNumber);
		void even(function<void (int)> printNumber);
		void odd(function<void (int)> printNumber);
};

ZeroEvenOdd::ZeroEvenOdd(int n) {
	this->n = n;
	pthread_mutex_init(&mutexlock, nullptr);
	for (int i = 0; i < 3; i++) {
		pthread_cond_init(&conds[i], nullptr);
	}
}

void ZeroEvenOdd::zero(function<void (int)> printNumber) {
	for (int i = 1; i <= n; i++) {
		pthread_mutex_lock(&mutexlock);
		while (!zeroFlag)
			pthread_cond_wait(&conds[0], &mutexlock);
		printNumber(0);
		if (evenFlag)
			pthread_cond_signal(&conds[1], &mutexlock);
		else
			pthread_cond_signal(&conds[2], &mutexlock);
		pthread_mutex_unlock(&mutexlock);
	}
}

void ZeroEvenOdd::even(function<void (int)> printNumber) {
	for (int i = 1; i <= n; i += 2) {
	}

}

void ZeroEvenOdd::odd(function<void (int)> printNumber) {
	for (int i = 1; i <= n; i += 2) {
		pthread_mutex_lock(&mutexlock);
		while ()
	}

}

const int N = 5;

ZeroEvenOdd obj(N);

function<void (int)> printNumber = [] (int n) {
	cout << n << endl;
};

void *ProcOne(void *) {
	obj.zero(printNumber);
}

void *ProcTwo(void *) {
	obj.even(printNumber);
}

void *ProcThree(void *) {
	obj.odd(printNumber);
}



// Test

int main(int argc, char *argv[]) {
	pthread_t threads[3];
	pthread_create(&threads[0], nullptr, ProcOne, nullptr);
	pthread_create(&threads[1], nullptr, ProcTwo, nullptr);
	pthread_create(&threads[3], nullptr, ProcThree, nullptr);
	for (int i = 0; i < 3; i++) {
		pthread_join(threads[0], nullptr);
	}
	return 0;
}
