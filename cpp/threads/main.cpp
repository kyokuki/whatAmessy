#include <iostream>
#include "thread.h"
#include <unistd.h>
using namespace ThreadPool;

class TestThread : public Thread {
    void run() {
    std::cout << "int thread runing ...." << std::endl;
    std::cout << "sleep for 2 secs...." << std::endl;
    this->join();
    this->sleep(0.000002);
    std::cout << "recomming...." << std::endl;
    }
};

int main(int argc, char **argv) {
    
    std::cout << "Hello, world!" << std::endl;
    
    TestThread t;
    t.create();
    
    sleep(4);
    return 0;
}
