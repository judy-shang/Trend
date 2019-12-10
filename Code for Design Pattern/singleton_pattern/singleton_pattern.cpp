// singleton_pattern.cpp : Defines the entry point for the console application.
//
/*
单例模式
1. 简单单例模式；
2. 加锁双重判断模式；
3. 静态变量模式；
*/
//注意 static成员变量不能在类定义里边初始化，只能在class body外初始化。
//继承 https://blog.csdn.net/a435262767/article/details/91040549
#include "stdafx.h"
#include<string>
#include<iostream>
#include<mutex>
#include <functional>
using namespace std;
/*
创建型模式: 单例模式，工厂模式
旨在将系统与它的对象创建、结合、表示的方式分离。这些设计模式在对象创建的类型、主体、方式、时间等方面提高了系统的灵活性
*/

/*
单例模式
What
    单例模式，也叫单子模式，是一种常用的软件设计模式。
    在应用这个模式时，单例对象的类必须保证只有一个实例存在。

Why
    许多时候整个系统只需要拥有一个的全局对象，这样有利于我们协调系统整体的行为。比如在某个服务器程序中，该服务器的配置信息存放在一个文件中，这些配置数据由一个单例对象统一读取，然后服务进程中的其他对象再通过这个单例对象获取这些配置信息。这种方式简化了在复杂环境下的配置管理。
    在一些场景下也可以进行一些权限控制或者避免暴露一些细节
How
在以下情况下可以使用单例模式：
    系统只需要一个实例对象，如系统要求提供一个唯一的序列号生成器，或者需要考虑资源消耗太大而只允许创建一个对象。
    客户调用类的单个实例只允许使用一个公共访问点，除了该公共访问点，不能通过其他途径访问该实例。
    在一个系统中要求一个类只有一个实例时才应当使用单例模式。反过来，如果一个类可以有几个实例共存，就需要对单例模式进行改进，使之成为多例模式。
*/
/*
Double-checked双重检查
What
  双重检查锁定模式（也被称为"双重检查加锁优化"，"锁暗示"（Lock hint）是一种软件设计模式用来减少并发系统中竞争和同步的开销。双重检查锁定模式首先验证锁定条件(第一次检查)，只有通过锁定条件验证才真正的进行加锁逻辑并再次验证条件(第二次检查)。
Why
  它通常用于减少加锁开销，尤其是为多线程环境中的单例模式实现“惰性初始化”。惰性初始化的意思是直到第一次访问时才初始化它的值
How
  如果指针是由C++关键字volatile定义的，那么双重检查锁可以在Visual C++ 2005 或更高版本中实现。Visual C++ 2005 保证volatile变量是一种内存屏障，阻止编译器和CPU重新安排读入和写出语义
  在J2SE 1.4或更早的版本中使用双重检查锁有潜在的危险，有时会正常工作：区分正确实现和有小问题的实现是很困难的。取决于编译器，线程的调度和其他并发系统活动，不正确的实现双重检查锁导致的异常结果可能会间歇性出现。重现异常是十分困难的。
  在J2SE 5.0中，这一问题被修正了。volatile关键字保证多个线程可以正确处理单件实例。

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

//简单模式
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
SingletonSimple* SingletonSimple::singleton = new SingletonSimple(); //不论是否使用都先初始化

//双重if判断模式
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
            m.lock();//加锁双重判定
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

//设置为静态变量形式
class SingletonStaticVar : public Singleton
{
public:
    static SingletonStaticVar* getInstance() {
        static SingletonStaticVar* instance = new SingletonStaticVar();
        return instance;
    }
};

//测试代码
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

