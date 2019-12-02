// Iterator_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <List>
using namespace std;
/*
行为模式: 策略模式，迭代器模式
目的：
行为模式对类或者对象怎么交互或怎样分配职责进行描述

范围：
行为型类模式使用继承描述算法和控制流比如Template Method, Interpreter 模式，而行为对象模式则描述一组对象怎样协作完成单个对象无法完成的任务
*/
/*
What
    提供一种顺序访问一个聚合对象中的各元素，而不需要暴露该对象的内部表示
Why
    一个聚合对象，比如list，map，应该提供一种方法来让别人可以访问他的元素，而且又暴露他的内部结构。
    迭代器以不同的方式遍历一个聚合
    简化聚合的接口
    在同一个聚合上可以有多个迭代器
How 适用性
    访问一个聚合对象的内容，又不暴露内部细节
    支持聚合对象的多种遍历
    为不同的遍历对象提供同统一的接口（多态迭代）
*/
class Echo {
private:
    int m_num;
public:
    Echo(int i) {
        m_num = i;
    }
    int echo() {
        return m_num;
    }
};
//测试代码
bool do_test(const int src1, const int src2)
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
    list<Echo> echoList;
    const int MAX_SET = 10;
    for (int i = 0; i < MAX_SET; ++i)
    {
        echoList.push_back(Echo(i));
    }
    int j = 0;
    for (list<Echo>::iterator i = echoList.begin(); i != echoList.end(); ++i, ++j)
    {
        do_test(i->echo(), j);
    }
}
int main()
{
    Test();

    system("pause");
    return 0;
}


