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
/*
������ģʽ: ����ģʽ������ģʽ
ּ�ڽ�ϵͳ�����Ķ��󴴽�����ϡ���ʾ�ķ�ʽ���롣��Щ���ģʽ�ڶ��󴴽������͡����塢��ʽ��ʱ��ȷ��������ϵͳ�������
*/

/*
����ģʽ
What
    ����ģʽ��Ҳ�е���ģʽ����һ�ֳ��õ�������ģʽ��
    ��Ӧ�����ģʽʱ���������������뱣ֻ֤��һ��ʵ�����ڡ�

Why
    ���ʱ������ϵͳֻ��Ҫӵ��һ����ȫ�ֶ�����������������Э��ϵͳ�������Ϊ��������ĳ�������������У��÷�������������Ϣ�����һ���ļ��У���Щ����������һ����������ͳһ��ȡ��Ȼ���������е�����������ͨ��������������ȡ��Щ������Ϣ�����ַ�ʽ�����ڸ��ӻ����µ����ù���
    ��һЩ������Ҳ���Խ���һЩȨ�޿��ƻ��߱��Ⱪ¶һЩϸ��
How
����������¿���ʹ�õ���ģʽ��
    ϵͳֻ��Ҫһ��ʵ��������ϵͳҪ���ṩһ��Ψһ�����к���������������Ҫ������Դ����̫���ֻ������һ������
    �ͻ�������ĵ���ʵ��ֻ����ʹ��һ���������ʵ㣬���˸ù������ʵ㣬����ͨ������;�����ʸ�ʵ����
    ��һ��ϵͳ��Ҫ��һ����ֻ��һ��ʵ��ʱ��Ӧ��ʹ�õ���ģʽ�������������һ��������м���ʵ�����棬����Ҫ�Ե���ģʽ���иĽ���ʹ֮��Ϊ����ģʽ��
*/

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

