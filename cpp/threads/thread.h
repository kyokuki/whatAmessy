// thread.h

#include <cstdio>
#include <pthread.h>

namespace ThreadPool
{
    
    class Thread
    {
    protected:
        pthread_t       _thread_id;
        int             _thread_no;
        bool            _runing;
        
    public:
        Thread(const int thread_no = -1);
        virtual ~Thread();
        int thread_no() const { return _thread_no; }
        void set_thread_no(const int n);
        void create(const bool detached = false);
        virtual void run() = 0;
        void detach();
        void join();
        void cancel();
        void reset_running() { _runing = false; }
    protected:
        void exit();
        void sleep(const double sec);
    };
}