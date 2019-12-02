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
�ṹģʽ��Adapter Pattern, Proxy Pattern
Ŀ�ģ�
�ṹģʽ��������߶�������

��Χ��
�ṹ����ģʽʹ�ü̳л�������������Adapter�����ṹ����ģʽ�������˶������װ��ʽ����Adapter�������Ľṹģʽ
*/

/*
������ģʽ
��������ģʽ�����ؼ̳�ʵ������
����������ģʽ���ӿڼ̳�ʵ������
What
    Adapter ��һ����Ľӿ�ת���ɿͻ�ϣ���������һ���ӿ�
Why
    Adapterģʽʹ��ԭ�����ڽӿڲ����ݲ���һ��������Щ�����һ����
How������
    ��ͼʹ��һ���Ѿ����ڵ��࣬�����Ľӿڲ��������Ҫ��
    ��ͼ����һ�����Ը��õ��࣬�����������������ص�����߲���Ԥ������Эͬ����
    ��ͼʹ��һЩ�Ѿ����ڵ����࣬���ǲ����ܶ�ÿһ�����������໯��ƥ�����Ľӿڣ����������������������ĸ���ӿڡ���������adapter����ģʽ

*/


//��������
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
// ������
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
//���Դ���
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


