// singleton_pattern.cpp : Defines the entry point for the console application.
//
/*
����ģʽ
1. �򵥵���ģʽ��
2. ����˫���ж�ģʽ��
3. ��̬����ģʽ��
*/
//ע�� static��Ա�����������ඨ����߳�ʼ����ֻ����class body���ʼ����
//�̳� https://blog.csdn.net/a435262767/article/details/91040549
#include "stdafx.h"
#include<string>
#include<iostream>
#include<mutex>
#include <functional>
using namespace std;


class Singleton
{
protected:
    static int count;
    Singleton() {
        count++;
        cout << "Singleton create, count: " << count << endl;
    }
public:
    static bool checkSingleton(int num) {
        if (count <= num)
        {
            cout << "OK" << endl;
            return true;
        }
        else
        {
            cout << "Not Singleton" << endl;
            return false;
        }
    }
};
int Singleton::count = 0;

//��ģʽ
class SingletonSimple :public Singleton
{
private:
    static SingletonSimple* singleton;
public:
    static SingletonSimple* getInstance()
    {
        return singleton;
    }
};
SingletonSimple* SingletonSimple::singleton = new SingletonSimple(); //�����Ƿ�ʹ�ö��ȳ�ʼ��

//˫��if�ж�ģʽ
mutex m;
class SingletonDoubleCheck:public Singleton
{
private:
    static SingletonDoubleCheck* singleton;
public:
    static SingletonDoubleCheck* getInstance()
    {
        if (singleton == NULL)
        {
            m.lock();//����˫���ж�
            if (singleton == NULL)
            {
                singleton = new SingletonDoubleCheck();
            }
            m.unlock();
        }
        return singleton;
    }
};
SingletonDoubleCheck* SingletonDoubleCheck::singleton = NULL;

//����Ϊ��̬������ʽ
class SingletonStaticVar : public Singleton
{
public:
    static SingletonStaticVar* getInstance() {
        static SingletonStaticVar* instance = new SingletonStaticVar();
        return instance;
    }
};

//���Դ���
void Test(std::function<void()> test_func, std::function<bool(int)> test_check, int num)
{
    const int thread_num = 10;
    std::thread thread[thread_num];
    for (int i = 0; i < thread_num; ++i)
    {
        thread[i] = std::thread(test_func);
    }
    for (int i = 0; i < thread_num; ++i)
    {
        thread[i].join();
    }
    test_check(num);
}
int main()
{
    int num = 0;
    num++;
    Test(SingletonSimple::getInstance, Singleton::checkSingleton, num);
    num++;
    Test(SingletonDoubleCheck::getInstance, Singleton::checkSingleton, num);
    num++;
    Test(SingletonStaticVar::getInstance, Singleton::checkSingleton, num);
    system("pause");
    return 0;
}

