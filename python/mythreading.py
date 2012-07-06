#/usr/bin/env python
#encoding=utf-8

import threading
import time
import random
from Queue import Queue

class MyThread(threading.Thread):

    def __init__(self, threadname=""):
        super(MyThread,self).__init__(name = threadname)
        
    def run(self):
        print "%s running thread name:%s" % (time.ctime(), self.name)
        
#---------------------------------------------------------------------

mylock = threading.RLock()
class MyThreadL(threading.Thread):

    def __init__(self, threadname=""):
        super(MyThreadL,self).__init__(name = threadname)
        
    def run(self):
        print "%s running thread name:%s" % (time.ctime(), self.name)
        print "%s geting lock: %s" % (time.ctime(), self.name)
        mylock.acquire();
        print "%s got lock :%s" % (time.ctime(), self.name)
        time.sleep(2)
        mylock.release()
        print "%s release lock: %s" % (time.ctime(), self.name)


#-------------------------------------------------------------

class Producer(threading.Thread):
    
    def __init__(self, threadname, share):
        super(Producer,self).__init__(name = threadname)
        self.share = share
    def run(self):
        for i in range(10):
            print self.name, " put ", i
            self.share.put(i)
            time.sleep(random.randrange(10)/10.0)
            print self.name, "fineshed"
    
class Consumer(threading.Thread):
    
    def __init__(self, threadname, share):
        super(Consumer, self).__init__(name = threadname)
        self.share = share
    def run(self):
        for i in range(10):
            print self.name, " get ",i
            self.share.get()
            time.sleep(random.randrange(10)/10.0)
            print self.name, "finished"


#------------------------------main
if __name__ == '__main__':
    queue = Queue()
    producer = Producer( 'Producer', queue )
    consumer = Consumer( 'Consumer', queue )
    
    print 'Starting threads ...'
    producer.start()
    consumer.start()
 
    producer.join()
    consumer.join()
 
    print 'All threads have terminated.'
        

