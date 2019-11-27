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
using namespace std;
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
    virtual Button* CreateButton() = 0;
    bool CheckButton(Button* button) {
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
    Button* CreateButton() {
        return new WinButton(m_type);
    } 
};
class MacButtonFactory : public ButtonFactory {

public:
    MacButtonFactory(string type) :ButtonFactory(type) {
    }
    Button* CreateButton() {
        return new MacButton(m_type);
    }
};
//���Դ���
void Test()
{
    string type1 = "Win";
    ButtonFactory* winButtonFactory = new WinButtonFactory(type1);
    Button* button1 = winButtonFactory->CreateButton();
    winButtonFactory->CheckButton(button1);
    cout << button1->getTypeString() << endl;

    string type2 = "Mac";
    ButtonFactory* macButtonFactory = new MacButtonFactory(type2);
    Button* button2 =  macButtonFactory->CreateButton();
    macButtonFactory->CheckButton(button2);
    cout << button2->getTypeString() << endl;
}
int main()
{
    Test();

    system("pause");
    return 0;
}

