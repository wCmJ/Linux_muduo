#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name")
class noncopyable{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
private:
    noncopyable() = default;
    ~noncopyable() = default;
};

class MutexLock: public noncopyable{
public:
    MutexLock(){
        pthread_mutex_init(&mutex_, NULL);    
    }
    ~MutexLock(){
        pthread_mutex_destroy(&mutex_);
    }
    void lock()
    {
        pthread_mutex_lock(&mutex_);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }
private:
    pthread_mutex_t mutex_;

};

class MutexLockGuard:public noncopyable{
public:
    MutexLockGuard(MutexLock& mutex):mutex_(mutex){
        mutex_.lock();
    }
    ~MutexLockGuard(){
        mutex_.unlock();
    }
private:
    MutexLock& mutex_;
};

class Condition{
    explicit Condition(MutexLock& mutex):mutex_(mutex){
        pthread_cond_init(&pcond_, NULL);   
    }
    ~Condition(){
        pthread_cond_destroy(&pcond_);   
    }
    void wait(){
        pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
    }
    void notify(){
        pthread_cond_signal(&pcond_);   
    }
    void notifyAll(){
        pthread_cond_broadcast(&pcond_);   
    }
    
private:    
    MutexLock& mutex_;
    pthread_cond_t pcond_;
};

