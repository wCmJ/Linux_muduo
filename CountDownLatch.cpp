class CountDownLatch:public noncopyable{
public:
    CountDownLatch(int count):count_(count){}
    void wait(){
        MutexLockGuard lock(mutex_);
        while(count_ > 0)
        {
            condition_.wait();
        }
    }
    void countDown(){
        MutexLockGuard lock(mutex_);
        --count_;
        if(count_ == 0)
            condition_.notifyAll();
    }
private:
    MutexLock mutex_;
    Condition condition_;
    int count_;
};
