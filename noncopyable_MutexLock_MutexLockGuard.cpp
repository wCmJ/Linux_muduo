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


