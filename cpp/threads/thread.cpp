// thread.cpp

#include "thread.h"
#include <iostream>
#include <string.h>
#include <cmath>
#include <time.h>


namespace ThreadPool
{
    
    extern "C" void * _run_thread(void *arg) {
        if (arg != NULL) {                      //arg参数是派生类的对象实例地址
            ((Thread *)arg)->run();             // run方法是虚方法，利用多态特性会调用传过来的对象实例的run方法
            ((Thread *)arg)->reset_running();
        }
        return NULL;
    }
    
    Thread::Thread(const int thread_no): _runing(false), _thread_no(thread_no) {
        ;
    }
    
    Thread::~Thread() {
        if (_runing) {
            ;
        }
    }
    
    void Thread::set_thread_no(const int n) {
        _thread_no = n;
    }
    
    void Thread::create(const bool detached) {
        if (!_runing) {
            int status;
            pthread_attr_t thread_attr;
            
            if ((status = pthread_attr_init(&thread_attr)) != 0) {
                std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
                return;
            }
            
            if (detached) {
                if ((status = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED)) != 0) {
                    std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
                    return;
                }
            }
            
            if ((status = pthread_create(&_thread_id, &thread_attr, _run_thread, this)) != 0) {
                 std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
                 return;
            } else {
                _runing = true;
            }
            
            pthread_attr_destroy(&thread_attr);
        } else {
            std::cout << "thread_no = " << _thread_no << "already running" << std::endl;
        }
    }
    
    void Thread::detach() {
        if ( _runing ) {
            int status;
            if ((status = pthread_detach(_thread_id)) != 0) {
                std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
            }
        }
    }
    
    void Thread::join()
    {
        if ( _runing ) {
            int status;
            if ((status = pthread_join(_thread_id, NULL)) != 0) {
                std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
            }
            _runing = false;
        }
    }
    
    void Thread::cancel() {
        if (_runing) {
            int status;
            if ((status = pthread_cancel(_thread_id)) != 0) {
                std::cerr <<  __FILE__ << ":" << __LINE__ << " : " << strerror(status) << std::endl; 
            }
        }
    }
    
    void Thread::exit() {
        if (_runing && pthread_self() == _thread_id) {
            void *rt = NULL;
            pthread_exit(rt);
            _runing = false;
        }
    }
    
    void Thread::sleep(const double sec) {
        if ( _runing ) {   
                struct timespec  interval;

                if ( sec <= 0.0 ) {   
                interval.tv_sec  = 0;
                interval.tv_nsec = 0;
                } else {   
                    interval.tv_sec  = time_t( std::floor( sec ) );
                    interval.tv_nsec = long( (sec - interval.tv_sec) * 1e6 );
                }   
                nanosleep( & interval, 0 );
        }   
    }

}