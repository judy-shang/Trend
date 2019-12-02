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
��Ϊģʽ: ����ģʽ��������ģʽ
Ŀ�ģ�
    ��Ϊģʽ������߶�����ô��������������ְ���������

��Χ��
    ��Ϊ����ģʽʹ�ü̳������㷨�Ϳ���������Template Method, Interpreter ģʽ������Ϊ����ģʽ������һ���������Э����ɵ��������޷���ɵ�����
*/

/*
����ģʽ
What
    ����һϵ�е��㷨��������һ������װ����������ʹ���ǿ����໥�滻��
    ���� Policy
Why
    Strategyʹ���㷨�ı仯���Զ�����ʹ�����Ŀͻ�
How ������
    �����ص����������Ϊ���졣�����ṩ��һ�ֹ�����Ϊ�е�һ����Ϊ������һ����ķ���
    ��Ҫʹ��һ���㷨�Ĳ�ͬ���塣����һЩ��Ӧ��ͬ�ռ䡢ʱ��Ȩ����㷨��
    �㷨ʹ�ÿͻ���Ӧ��֪�������ݡ����Ա��Ⱪ¶���ӵ����㷨��ص����ݽṹ
    һ�����кܶ���Ϊ�����Խ���ͬ����Ϊ����ɲ�ͬ�����࣬SRP.
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
