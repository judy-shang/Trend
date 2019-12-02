// factory_pattern.cpp : Defines the entry point for the console application.
//
/*
����ģʽ
����һ����������Ľӿڣ�����ʵ������ӿڵ���������ʵ�����ĸ��ࡣ�������������ʵ�����Ƴٵ������н���
*/
#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std;
/*
������ģʽ: ����ģʽ������ģʽ
ּ�ڽ�ϵͳ�����Ķ��󴴽�����ϡ���ʾ�ķ�ʽ���롣��Щ���ģʽ�ڶ��󴴽������͡����塢��ʽ��ʱ��ȷ��������ϵͳ�������
*/

/*
What
    ��������ģʽ��Ӣ�Factory method pattern����һ��ʵ���ˡ����������������������ģʽ��
    ��������������ģʽһ������Ҳ�Ǵ����ڲ�ָ������������͵�����´�����������⡣
    ��������ģʽ��ʵ���ǡ�����һ����������Ľӿڣ�����ʵ������ӿڵ���������ʵ�����ĸ��ࡣ
    �������������ʵ�����Ƴٵ������н���
Why
    ���ȣ�����ģʽ��Ϊ�˽���Ѷ���Ĵ�����ʹ�õĹ��̷ֿ�������Class A ����� Class B ����ôAֻ�ǵ���B�ķ�����������B��ʵ�������ͽ��������ࡣ
    ��Σ�����ģʽ���Խ��ʹ����ظ��������������B�Ĺ��̶��ܸ��ӣ���Ҫһ���Ĵ����������Һܶ�ط���Ҫ�õ�����ô�ͻ��кܶ���ظ����롣
    ���ǿ�����Щ��������B�Ĵ���ŵ�������ͳһ�����ȼ������ظ����룬Ҳ�����Ժ��B�Ĵ������̵��޸�ά����
How
����������Կ���ʹ�ù�������ģʽ��
    ����������Ҫ�����ظ��Ĵ��롣
    ����������Ҫ����ĳЩ��Ϣ������Щ��Ϣ��Ӧ�ð����ڸ������С�
    ����������������ڱ��뼯�й����Ա�֤�����������о���һ�µ���Ϊ��
    ��������ģʽ�����ڹ��߰��Ϳ���У�����Щ���п�����Ҫ�����ͻ��˴���ʵ�ֵľ������͵Ķ���
*/

class Button
{
public:
    string m_type;
    Button(string type) : m_type(type) {

    }
    string getType() {
        return m_type;
    }
    virtual string getTypeString() = 0;
};
class WinButton :public Button {
public:
    WinButton(string type) :Button(type) {

    }
    string getTypeString()
    {
        return "WinButton";
    }
};
class MacButton :public Button {
public:
    MacButton(string type) :Button(type) {

    }
    string getTypeString()
    {
        return "MacButton";
    }
};
class ButtonFactory { 
public:
    string m_type;
    ButtonFactory(string type) :m_type(type) {

    }
    virtual boost::shared_ptr<Button> CreateButton() = 0;
    bool CheckButton(boost::shared_ptr<Button> button) {
        if (button->getType() == m_type)
        {
            cout << "ok" << endl;
            return true;
        }
        else
        {
            cout << "error" << endl;
            return false;
        }

    }
};
class WinButtonFactory : public ButtonFactory {
    
public:
    WinButtonFactory(string type) :ButtonFactory(type) {
    }
    boost::shared_ptr<Button> CreateButton() {
        return boost::make_shared<WinButton>(m_type);
    } 
};
class MacButtonFactory : public ButtonFactory {

public:
    MacButtonFactory(string type) :ButtonFactory(type) {
    }
    boost::shared_ptr<Button> CreateButton() {
        return boost::make_shared<MacButton>(m_type);
    }
};
//���Դ���
void Test()
{
    string type1 = "Win";
    boost::shared_ptr<ButtonFactory> winButtonFactory = boost::make_shared<WinButtonFactory>(type1);
    boost::shared_ptr<Button> button1 = winButtonFactory->CreateButton();
    winButtonFactory->CheckButton(button1);
    cout << button1->getTypeString() << endl;

    string type2 = "Mac";
    boost::shared_ptr<ButtonFactory> macButtonFactory = boost::make_shared<MacButtonFactory>(type2);
    boost::shared_ptr<Button> button2 =  macButtonFactory->CreateButton();
    macButtonFactory->CheckButton(button2);
    cout << button2->getTypeString() << endl;
}
int main()
{
    Test();

    system("pause");
    return 0;
}

