// concurrency_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <List>
#include <mutex>
#include <windows.h>
using namespace std;
/*
concurrency pattern并发模式
Reactor
Thread pool
Read-write lock
Double-checked locking
*/
/*
Reactor反应器模式
What
  反应器设计模式(Reactor pattern)是一种为处理服务请求并发 提交到一个或者多个服务处理程序的事件设计模式。
  当请求抵达后，服务处理程序使用解多路分配策略，然后同步地派发这些请求至相关的请求处理程序。
Why
  反应器模式可完全分离程序特定代码，这意味着应用可分为模块化的，可复用的组件。另外，由于请求的处理程序是同步调用，反应器模式可允许简单粗粒并发而不必添加多线程并发系统的复杂性。
How
  资源Resources： 可供系统输入或输出的资源。
  同步事件解多路器 Synchronous Event Demultiplexer： 使用一个事件循环 ，以阻止所有的资源。当可以启动一个同步操作上的资源不会阻塞，多路分解器发送资源到分发器。
  分发器 Dispatcher： 处理请求程序的注册和注销。将资源分发到相关的处理程序.
  请求处理器 Request Handler ： 应用程序定义的请求处理程序和相关资源。
Disadvantage：复杂的调试和测试
由于反向的流程控制，反应器模式比过程模式更难以调试 
此外，因为请求处理器只会被同步调用，因此会限制反应器模式的最大并发数，特别是在对称多处理硬件。反应器模式的可扩展性，不仅受限于请求处理器的同步调用，同时也受解多路器限制
*/
/*
Thread Pool线程池
What
  线程池：一种线程使用模式
  线程池模式一般分为两种：HS/HA半同步/半异步模式、L/F领导者与跟随者模式
Why
  线程过多会带来调度开销，进而影响缓存局部性和整体性能。
  而线程池维护着多个线程，等待着监督管理者分配可并发执行的任务。这避免了在处理短时间任务时创建与销毁线程的代价。
  线程池不仅能够保证内核的充分利用，还能防止过分调度。可用线程数量应该取决于可用的并发处理器、处理器内核、内存、网络sockets等的数量。 例如，线程数一般取cpu数量+2比较合适，线程数过多会导致额外的线程切换开销。
How
  访问控制：DB
  生产者/消费者模式，发布订阅模式
  线程池现在已经集成到各种语言中，所有的并发任务里面基本都可以使用，尤其是workflow中存在IO之类的瓶颈的task里
Types：
HS/HA半同步/半异步模式
  半同步/半异步模式又称为生产者消费者模式，是比较常见的实现方式，比较简单。
  分为同步层、队列层、异步层三层。
  同步层的主线程处理工作任务并存入工作队列，工作线程从工作队列取出任务进行处理，如果工作队列为空，则取不到任务的工作线程进入挂起状态。
  由于线程间有数据通信，因此不适于大数据量交换的场合。
L/F领导者与跟随者模式
  领导者跟随者模式，在线程池中的线程可处在3种状态之一：领导者leader、追随者follower或工作者processor。
  任何时刻线程池只有一个领导者线程。事件到达时，领导者线程负责消息分离，并从处于追随者线程中选出一个来当继任领导者，然后将自身设置为工作者状态去处置该事件。
  处理完毕后工作者线程将自身的状态置为追随者。
  这一模式实现复杂，但避免了线程间交换任务数据，提高了CPU cache相似性。在ACE(Adaptive Communication Environment)中，提供了领导者跟随者模式实现。
Disadvantage
  线程池的伸缩性对性能有较大的影响(scale in/out)
  创建太多线程，将会浪费一定的资源，有些线程未被充分使用。
  销毁太多线程，将导致之后浪费时间再次创建它们。
  创建线程太慢，将会导致长时间的等待，性能变差。
  销毁线程太慢，导致其它线程资源饥饿。
*/
/*
Read-write lock
What
  Allows concurrent read access to an object, but requires exclusive access for write operations.
  读写锁是计算机程序的并发控制的一种同步机制，也称“共享-互斥锁”、多读者-单写者锁。[1]多读者锁，[2]，“push lock”[3]) 用于解决读写问题。
  读操作可并发重入，写操作是互斥的。
Why
  在保证资源访问安全的请况下，最大程度上的提高资源的利用率，减少阻塞。
How
  使用两把互斥锁
  使用条件变量与互斥锁
*/
class ReadWriteLock
{
protected:
    shared_ptr<mutex> write;
public:
    virtual void Begin() = 0;
    virtual void End() = 0;
    ReadWriteLock(shared_ptr<mutex> write_ptr) :write(write_ptr) {

    }
};
class ReadLock: public ReadWriteLock {
    static int b;
    mutex read;
public:
    void Begin()
    {
        //cout << "Reading Begin enter now\n" << endl;
        read.lock();
        if (++b == 1)
        {
            write->lock();
            cout << "Reading Being lock now\n"<< endl;
        }
        read.unlock();
        
    }
    void End()
    {
        //cout << "Reading End enter now\n" << endl;
        read.lock();
        if (--b == 0)
        {
            write->unlock();
            cout << "Reading End unlock now\n" << endl;
        }
        read.unlock();
        
    }
    ReadLock(shared_ptr<mutex> write_ptr) :ReadWriteLock(write_ptr) {
        cout << "Reading now\n" << endl;
    }
};
int ReadLock::b = 0;
class WriteLock: public ReadWriteLock {
public:
    void Begin()
    {
        write->lock();
        Sleep(300);
        cout << "Writing Begin enter now\n" << endl;
    }
    void End()
    {
        write->unlock();
        cout << "Writing End quit now\n" << endl;
    }
    WriteLock(shared_ptr<mutex> write_ptr):ReadWriteLock(write_ptr) {
        //cout << "Writing now\n" << endl;
    }
};
//测试代码
bool do_test(const int src1, const int src2)
{
    if (src1 == src2)
    {
        std::cout << "Success\n" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed\n" << std::endl;
        return false;
    }
}

void test_func(shared_ptr<ReadWriteLock> lock)
{
    lock->Begin();
    lock->End();
}

void Test()
{
    const int thread_num = 10;
    std::thread thread[thread_num];
    shared_ptr<ReadWriteLock> locks[thread_num];
    shared_ptr<mutex> writelock = make_shared<mutex>();
    for (int i = 0; i < thread_num; ++i)
    {
        if (i % 3 != 0)
        {
            locks[i] = make_shared<ReadLock>(writelock);
        }
        else
        {
            locks[i] = make_shared<WriteLock>(writelock);
        }
        thread[i] = std::thread(test_func, locks[i]);
        //cout << "i: " << i << endl;
    }
    for (int i = 0; i < thread_num; ++i)
    {
        thread[i].join();
    }
}
int main()
{
    Test();

    system("pause");
    return 0;
}
