// abstract_interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
/* class 1
TDD:  ����������������д���Դ��룬�ٶ���д�������
ԭ�� ���ھۣ������
SOLID: 
      SRP  single responsiblity principle��΢����
      OCP  open-close principle�������ǿ���չ�ģ������ǿ��޸ĵġ����ײ㡰ԭ���ࡱ���޸ģ�ҵ����Ҫ�޸�
      LSP  liskov substitution principle
      ISP  interface segregation principle
      DIP  dependency inversion principle������ӿڶ����������ھ���ʵ��
*/

//ע���� ����ָ�������ָͨ��
/*
��ģʽ����������Щ������ϰ�ߡ�
1. ������Big ball of mud������û�������ṹ��ϵͳ��
2. ѭ��������Circle dependency��
3. Ӳ����
4. ħ��
*/
class Worker {
public:
    virtual std::string work() = 0;
    std::string m_type;
    Worker(std::string type) :m_type(type) {}
};
class CommonWorker:public Worker { //ע�⹫�м̳�
public:
    std::string work() {
        return m_type;
    }
    CommonWorker(std::string type):Worker(type){
    }
};
class SuperWorker:public Worker {
public:
    std::string work() {
        return m_type;
    }
    SuperWorker(std::string type) :Worker(type) {
    }
};
class Manager {
public: 
    void setWorker(boost::shared_ptr<Worker> w) {
        worker = w;
    }
    std::string manage() {
        return worker->work();
    }
private:
    boost::shared_ptr<Worker> worker;
};
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
    Manager manager;
    std::string testWord1 = "CommonWorker";
    std::string testWord2 = "SuperWorker";
    boost::shared_ptr<Worker> commonworker = boost::make_shared<CommonWorker>(testWord1);
    boost::shared_ptr<Worker> superworker = boost::make_shared<SuperWorker>(testWord2);
    manager.setWorker(commonworker);
    std::string type = manager.manage();
    do_test(type, testWord1);
    manager.setWorker(superworker);

    type = manager.manage();
    do_test(type, testWord2);
}
int main()
{
    Test();
    system("pause");
    return 0;
}

