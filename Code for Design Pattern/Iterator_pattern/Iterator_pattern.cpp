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
��Ϊģʽ: ����ģʽ��������ģʽ
Ŀ�ģ�
��Ϊģʽ������߶�����ô��������������ְ���������

��Χ��
��Ϊ����ģʽʹ�ü̳������㷨�Ϳ���������Template Method, Interpreter ģʽ������Ϊ����ģʽ������һ���������Э����ɵ��������޷���ɵ�����
*/
/*
What
    �ṩһ��˳�����һ���ۺ϶����еĸ�Ԫ�أ�������Ҫ��¶�ö�����ڲ���ʾ
Why
    һ���ۺ϶��󣬱���list��map��Ӧ���ṩһ�ַ������ñ��˿��Է�������Ԫ�أ������ֱ�¶�����ڲ��ṹ��
    �������Բ�ͬ�ķ�ʽ����һ���ۺ�
    �򻯾ۺϵĽӿ�
    ��ͬһ���ۺ��Ͽ����ж��������
How ������
    ����һ���ۺ϶�������ݣ��ֲ���¶�ڲ�ϸ��
    ֧�־ۺ϶���Ķ��ֱ���
    Ϊ��ͬ�ı��������ṩͬͳһ�Ľӿڣ���̬������
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
//���Դ���
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


