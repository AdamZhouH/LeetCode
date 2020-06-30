class DiningPhilosophers {
public:
    DiningPhilosophers();
    ~DiningPhilosophers();
    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork);
private:
    vector<pthread_mutex_t> mutexs;
};

// 关键点是并发控制，避免死锁，也就是每个哲学家都拿到了其左侧或者右侧的叉子，并导致僵持，每个人都等待其他哲学家放下叉子
// 设计多线程并发算法，避免死锁，同时记录每个哲学家的动作的数组
// 最终生成5个哲学家的进餐动作的组合(一组合理的，所有哲学家都能吃n次餐的动作组合)
// 基本思路很简单，就是五把大锁（或者性能开销太大就原子变量替换），每个哲学家尝试拿起身边两个叉子，都拿到才能吃，如果只能拿一个，就放下，继续等待
DiningPhilosophers::DiningPhilosophers() : mutexs(5) {
    for (int i = 0; i < 5; i++) pthread_mutex_init(&mutexs[i], nullptr);
}

DiningPhilosophers::~DiningPhilosophers() {
    for (int i = 0; i < 5; i++) pthread_mutex_destroy(&mutexs[i]);
}

void DiningPhilosophers::wantsToEat(int philosopher,
                                    function<void()> pickLeftFork,
                                    function<void()> pickRightFork,
                                    function<void()> eat,
                                    function<void()> putLeftFork,
                                    function<void()> putRightFork) {
    while (true) {
        if (pthread_mutex_trylock(&mutexs[(philosopher+5-1)%5]) == 0) pickLeftFork();
        else continue;
        if (pthread_mutex_trylock(&mutexs[(philosopher+1)%5]) == 0) pickRightFork();
        else {
            putLeftFork();
            pthread_mutex_unlock(&mutexs[(philosopher+5-1)%5]);
            continue;
        }
        eat();
        putLeftFork();
        putRightFork();
        pthread_mutex_unlock(&mutexs[(philosopher+5-1)%5]);
        pthread_mutex_unlock(&mutexs[(philosopher+1)%5]);
        return;
    }
}
