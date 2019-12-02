// adapter_patter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std;
/*
结构模式：Adapter Pattern, Proxy Pattern
目的：
结构模式处理类或者对象的组合

范围：
结构类型模式使用继承机制来组合类比如Adapter，而结构对象模式则描述了对象的组装方式比如Adapter和其他的结构模式
*/

/*
适配器模式
类适配器模式：多重继承实现适配
对象适配器模式：接口继承实现适配
What
    Adapter 将一个类的接口转换成客户希望的另外的一个接口
Why
    Adapter模式使得原本由于接口不兼容不能一起工作的那些类可以一起工作
How适用性
    意图使用一个已经存在的类，而它的接口不符合你的要求
    意图创建一个可以复用的类，该类可以与其他不相关的类或者不可预见的类协同工作
    意图使用一些已经存在的子类，但是不可能对每一个都进行子类化以匹配他的接口，对象适配器可以适配他的父类接口。仅适用于adapter对象模式

*/


//对象适配
class Adaptee {
public:
    virtual string run() = 0;
};
class SmallAdaptee:public Adaptee {
public:
    string run() {
        return "SmallAdaptee";
    }
};
class BigAdaptee:public Adaptee {
public:
    string run() {
        return "BigAdaptee";
    }
};
class Adapter {
private:
    shared_ptr<Adaptee> m_adaptee;
public:
    Adapter(shared_ptr<Adaptee> adaptee) {
        m_adaptee = adaptee;
    }
    string Move() {
        return m_adaptee->run();
    }
    void set_adaptee(shared_ptr<Adaptee> adaptee) {
        m_adaptee = adaptee;
    }
};
class Client {
private:
    shared_ptr<Adapter> m_adapter;
public:
    Client(shared_ptr<Adapter> adapter) {
        m_adapter = adapter;
    }
    string doWork() {
        return m_adapter->Move();
    }

};
// 类适配
class SmallAdaptee_Cls {
public:
    string run_small() {
        return "SmallAdaptee_Cls";
    }
};
class BigAdaptee_Cls {
public:
    string run_big() {
        return "BigAdaptee_Cls";
    }
};

class Adapter_Cls:public SmallAdaptee_Cls, public BigAdaptee_Cls {
public:
    string Move() {
        //return run_small();
        return run_big();
    }
};
class Client_Cls {
private:
    shared_ptr<Adapter_Cls> m_adapter;
public:
    Client_Cls(shared_ptr<Adapter_Cls> adapter) {
        m_adapter = adapter;
    }
    string doWork() {
        return m_adapter->Move();
    }

};
//测试代码
bool do_test(const std::string& src1, const std::string& src2)
{
    if (src1 == src2)
    {
        std::cout << "Success" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed" << std::endl;
        return false;
    }
}
void Test()
{
    shared_ptr<Adaptee> smallAdaptee = make_shared<SmallAdaptee>();
    shared_ptr<Adaptee> bigAdaptee = make_shared<BigAdaptee>();
    shared_ptr<Adapter> adapter = make_shared<Adapter>(smallAdaptee);
    Client client(adapter);
    do_test(client.doWork(), "SmallAdaptee");
    adapter->set_adaptee(bigAdaptee);
    do_test(client.doWork(), "BigAdaptee");

    shared_ptr<Adapter_Cls> adapter_cls = make_shared<Adapter_Cls>();
    Client_Cls client_cls(adapter_cls);
    //do_test(client_cls.doWork(), "SmallAdaptee_Cls");
    do_test(client_cls.doWork(), "BigAdaptee_Cls");
}
int main()
{
    Test();

    system("pause");
    return 0;
}


