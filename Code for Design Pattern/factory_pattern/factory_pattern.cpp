// factory_pattern.cpp : Defines the entry point for the console application.
//
/*
工厂模式
定义一个创建对象的接口，但让实现这个接口的类来决定实例化哪个类。工厂方法让类的实例化推迟到子类中进行
*/
#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std;
/*
创建型模式: 单例模式，工厂模式
旨在将系统与它的对象创建、结合、表示的方式分离。这些设计模式在对象创建的类型、主体、方式、时间等方面提高了系统的灵活性
*/

/*
What
    工厂方法模式（英语：Factory method pattern）是一种实现了“工厂”概念的面向对象设计模式。
    就像其他创建型模式一样，它也是处理在不指定对象具体类型的情况下创建对象的问题。
    工厂方法模式的实质是“定义一个创建对象的接口，但让实现这个接口的类来决定实例化哪个类。
    工厂方法让类的实例化推迟到子类中进行
Why
    首先，工厂模式是为了解耦：把对象的创建和使用的过程分开。就是Class A 想调用 Class B ，那么A只是调用B的方法，而至于B的实例化，就交给工厂类。
    其次，工厂模式可以降低代码重复。如果创建对象B的过程都很复杂，需要一定的代码量，而且很多地方都要用到，那么就会有很多的重复代码。
    我们可以这些创建对象B的代码放到工厂里统一管理。既减少了重复代码，也方便以后对B的创建过程的修改维护。
How
下列情况可以考虑使用工厂方法模式：
    创建对象需要大量重复的代码。
    创建对象需要访问某些信息，而这些信息不应该包含在复合类中。
    创建对象的生命周期必须集中管理，以保证在整个程序中具有一致的行为。
    工厂方法模式常见于工具包和框架中，在这些库中可能需要创建客户端代码实现的具体类型的对象。
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
//测试代码
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

