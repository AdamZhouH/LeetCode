class Foo {
public:
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int i = 0;
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        pthread_mutex_lock(&mutex);
        while (i) 
            pthread_cond_wait(&cond, &mutex);
        printFirst();
        i = (i + 1) % 3;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
       pthread_mutex_lock(&mutex);
        while (i != 1) 
            pthread_cond_wait(&cond, &mutex);
        printSecond();
        i = (i + 1) % 3;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        pthread_mutex_lock(&mutex);
        while (i != 2) 
            pthread_cond_wait(&cond, &mutex);
        printThird();
        i = (i + 1) % 3;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
};
