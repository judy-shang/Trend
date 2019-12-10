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
concurrency pattern����ģʽ
Reactor
Thread pool
Read-write lock
Double-checked locking
*/
/*
Reactor��Ӧ��ģʽ
What
  ��Ӧ�����ģʽ(Reactor pattern)��һ��Ϊ����������󲢷� �ύ��һ�����߶�������������¼����ģʽ��
  ������ִ�󣬷��������ʹ�ý��·������ԣ�Ȼ��ͬ�����ɷ���Щ��������ص����������
Why
  ��Ӧ��ģʽ����ȫ��������ض����룬����ζ��Ӧ�ÿɷ�Ϊģ�黯�ģ��ɸ��õ���������⣬��������Ĵ��������ͬ�����ã���Ӧ��ģʽ������򵥴���������������Ӷ��̲߳���ϵͳ�ĸ����ԡ�
How
  ��ԴResources�� �ɹ�ϵͳ������������Դ��
  ͬ���¼����·�� Synchronous Event Demultiplexer�� ʹ��һ���¼�ѭ�� ������ֹ���е���Դ������������һ��ͬ�������ϵ���Դ������������·�ֽ���������Դ���ַ�����
  �ַ��� Dispatcher�� ������������ע���ע��������Դ�ַ�����صĴ������.
  �������� Request Handler �� Ӧ�ó���������������������Դ��
Disadvantage�����ӵĵ��ԺͲ���
���ڷ�������̿��ƣ���Ӧ��ģʽ�ȹ���ģʽ�����Ե��� 
���⣬��Ϊ��������ֻ�ᱻͬ�����ã���˻����Ʒ�Ӧ��ģʽ����󲢷������ر����ڶԳƶദ��Ӳ������Ӧ��ģʽ�Ŀ���չ�ԣ���������������������ͬ�����ã�ͬʱҲ�ܽ��·������
*/
/*
Thread Pool�̳߳�
What
  �̳߳أ�һ���߳�ʹ��ģʽ
  �̳߳�ģʽһ���Ϊ���֣�HS/HA��ͬ��/���첽ģʽ��L/F�쵼���������ģʽ
Why
  �̹߳����������ȿ���������Ӱ�컺��ֲ��Ժ��������ܡ�
  ���̳߳�ά���Ŷ���̣߳��ȴ��żල�����߷���ɲ���ִ�е�������������ڴ����ʱ������ʱ�����������̵߳Ĵ��ۡ�
  �̳߳ز����ܹ���֤�ں˵ĳ�����ã����ܷ�ֹ���ֵ��ȡ������߳�����Ӧ��ȡ���ڿ��õĲ������������������ںˡ��ڴ桢����sockets�ȵ������� ���磬�߳���һ��ȡcpu����+2�ȽϺ��ʣ��߳�������ᵼ�¶�����߳��л�������
How
  ���ʿ��ƣ�DB
  ������/������ģʽ����������ģʽ
  �̳߳������Ѿ����ɵ����������У����еĲ��������������������ʹ�ã�������workflow�д���IO֮���ƿ����task��
Types��
HS/HA��ͬ��/���첽ģʽ
  ��ͬ��/���첽ģʽ�ֳ�Ϊ������������ģʽ���ǱȽϳ�����ʵ�ַ�ʽ���Ƚϼ򵥡�
  ��Ϊͬ���㡢���в㡢�첽�����㡣
  ͬ��������̴߳��������񲢴��빤�����У������̴߳ӹ�������ȡ��������д��������������Ϊ�գ���ȡ��������Ĺ����߳̽������״̬��
  �����̼߳�������ͨ�ţ���˲����ڴ������������ĳ��ϡ�
L/F�쵼���������ģʽ
  �쵼�߸�����ģʽ�����̳߳��е��߳̿ɴ���3��״̬֮һ���쵼��leader��׷����follower������processor��
  �κ�ʱ���̳߳�ֻ��һ���쵼���̡߳��¼�����ʱ���쵼���̸߳�����Ϣ���룬���Ӵ���׷�����߳���ѡ��һ�����������쵼�ߣ�Ȼ����������Ϊ������״̬ȥ���ø��¼���
  ������Ϻ������߳̽������״̬��Ϊ׷���ߡ�
  ��һģʽʵ�ָ��ӣ����������̼߳佻���������ݣ������CPU cache�����ԡ���ACE(Adaptive Communication Environment)�У��ṩ���쵼�߸�����ģʽʵ�֡�
Disadvantage
  �̳߳ص������Զ������нϴ��Ӱ��(scale in/out)
  ����̫���̣߳������˷�һ������Դ����Щ�߳�δ�����ʹ�á�
  ����̫���̣߳�������֮���˷�ʱ���ٴδ������ǡ�
  �����߳�̫�������ᵼ�³�ʱ��ĵȴ������ܱ�
  �����߳�̫�������������߳���Դ������
*/
/*
Read-write lock
What
  Allows concurrent read access to an object, but requires exclusive access for write operations.
  ��д���Ǽ��������Ĳ������Ƶ�һ��ͬ�����ƣ�Ҳ�ơ�����-���������������-��д������[1]���������[2]����push lock��[3]) ���ڽ����д���⡣
  �������ɲ������룬д�����ǻ���ġ�
Why
  �ڱ�֤��Դ���ʰ�ȫ������£����̶��ϵ������Դ�������ʣ�����������
How
  ʹ�����ѻ�����
  ʹ�����������뻥����
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
//���Դ���
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
