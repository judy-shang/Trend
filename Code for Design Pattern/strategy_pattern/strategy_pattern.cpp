// strategy_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std;
/*
行为模式: 策略模式，迭代器模式
目的：
    行为模式对类或者对象怎么交互或怎样分配职责进行描述

范围：
    行为型类模式使用继承描述算法和控制流比如Template Method, Interpreter 模式，而行为对象模式则描述一组对象怎样协作完成单个对象无法完成的任务
*/

/*
策略模式
What
    定义一系列的算法，把他们一个个封装起来，并且使他们可以相互替换。
    别名 Policy
Why
    Strategy使得算法的变化可以独立于使用它的客户
How 适用性
    许多相关的类仅仅是行为有异。策略提供了一种过个行为中的一个行为来配置一个类的方法
    需要使用一个算法的不同变体。定义一些反应不同空间、时间权衡的算法。
    算法使用客户不应该知道的数据。可以避免暴露复杂的与算法相关的数据结构
    一个类有很多行为，可以将不同的行为定义成不同的子类，SRP.
*/
class Transportation
{
public: 
    virtual string GoDestination() = 0;
};
class Car:public Transportation {
public:
    string GoDestination() {
        return "By Car";
    }
};
class Bike :public Transportation {
public:
    string GoDestination() {
        return "By Bike";
    }
};
class Train :public Transportation {
public:
    string GoDestination() {
        return "By Train";
    }
};
class NullTrans :public Transportation {
public:
    string GoDestination() {
        return "Null, error!";
    }
};
enum DesType {
    DesType_ROAD,
    DesType_RIVER,
    DesType_SKY,
    DesType_Max
};
enum Distance {
    Distance_short = 0,
    Distance_medium,
    Distance_far,
    Distance_Max
};
class GoSomeWherePlan
{
protected:
    shared_ptr<Transportation> m_tranportation[Distance_Max];
public:
    virtual string GoSomeWhere(Distance distance) = 0;
};
class GoRoadPlan : public GoSomeWherePlan
{
public:
    GoRoadPlan() {
        m_tranportation[Distance_short] = make_shared<Bike>();
        m_tranportation[Distance_medium] = make_shared<Car>();
        m_tranportation[Distance_far] = make_shared<Train>();
        m_tranportation[Distance_Max] = make_shared<NullTrans>();
    }
    string GoSomeWhere(Distance distance)
    {
        return m_tranportation[distance]->GoDestination();
    }
};
class GoPlan {
private:
    shared_ptr<GoSomeWherePlan> m_goSomeWherePlan[DesType_Max];
public:
    GoPlan() {
        m_goSomeWherePlan[DesType_ROAD] = make_shared<GoRoadPlan>();

    }
    string GoSomeWhere(DesType desType, Distance distance) {
        return m_goSomeWherePlan[desType]->GoSomeWhere(distance);
    }
};
class Client {
private:
    shared_ptr<GoPlan> m_goPlan;
public:
    Client(shared_ptr<GoPlan> goPlan)
    {
        m_goPlan = goPlan;
    }
    string GoToSomeWhere(DesType desType, Distance distance) {
        return m_goPlan->GoSomeWhere(desType, distance);
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
    shared_ptr<GoPlan> goPlan = make_shared<GoPlan>();
    Client client(goPlan);
    do_test(client.GoToSomeWhere(DesType_ROAD, Distance_short), "By Bike");
    do_test(client.GoToSomeWhere(DesType_ROAD, Distance_medium), "By Car");
    do_test(client.GoToSomeWhere(DesType_ROAD, Distance_far), "By Train");
    do_test(client.GoToSomeWhere(DesType_ROAD, Distance_Max), "Null, error!");
}
int main()
{
    Test();

    system("pause");
    return 0;
}
