// abstract_interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
/* class 1
TDD:  测试驱动开发，先写测试代码，再动手写服务代码
原则： 高内聚，低耦合
SOLID: 
      SRP  single responsiblity principle：微服务化
      OCP  open-close principle：代码是可扩展的，而不是可修改的——底层“原子类”可修改，业务不需要修改
      LSP  liskov substitution principle
      ISP  interface segregation principle
      DIP  dependency inversion principle：抽象接口而不是依赖于具体实现
*/

//注意用 智能指针替代普通指针
/*
反模式：【警惕这些不良的习惯】
1. 大泥球（Big ball of mud）——没有清晰结构的系统；
2. 循环依赖（Circle dependency）
3. 硬编码
4. 魔数
*/
class Worker {
public:
    virtual std::string work() = 0;
    std::string m_type;
    Worker(std::string type) :m_type(type) {}
};
class CommonWorker:public Worker { //注意公有继承
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

