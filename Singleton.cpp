template<typename T> 
class Singleton: public noncopyable{
public:
    static T& instance()
    {
        pthread_once(&pconce_, &Singleton::init);
        return *value_;
    }
private:
    Singleton();
    ~Singleton();
    static void init()
    {
        value_ = new T();
    }
private:
    static pthread_once_t ponce_;
    static T* value_;
};
//define pconce_ in .h
template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;
template<typename T>
T* Singleton<T>::value_ = NULL;
