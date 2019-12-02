// proxy_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace std;
/*
结构模式：Adapter Pattern, Proxy Pattern
目的：
结构模式处理类或者对象的组合

范围：
结构类型模式使用继承机制来组合类比如Adapter，而结构对象模式则描述了对象的组装方式比如Adapter和其他的结构模式
*/

/*
代理模式
What
  为其他的对象提供一个代理类以控制对这个对象的访问
Why
  控制一个队一个对象的访问
  延时创建资源对象，确保在需要的时候才创建
How 适用性：
  远程代理（Remote Proxy）为一个对象在不同的地址空间提供局部代表
  虚代理（Virtual Proxy）根据需要创建开销很大的对象，延时创建
  保护代理（Protection Proxy）控制对原始对象的访问。保护代理用于对象应该有不同的访问权限的时候。
  智能指针（Smart Reference） 取代了简单的指针，他在访问对象时执行一些附加操作。
*/
class Image {
public:
    virtual string showImage() = 0;
};
class HighResolutionImage :public Image {
public:
    HighResolutionImage()
    {
        cout << "HighResolutionImage" << endl;
    }
    string showImage() {
        return "HighResolutionImage";
    }
};
class ProxyImage :public Image {
private:
    
public:
    ProxyImage() {
        cout << "ProxyImage" << endl;
    }
    string showImage() {
        static shared_ptr<HighResolutionImage> m_highResolutionImage = 
            make_shared<HighResolutionImage>();
        return m_highResolutionImage->showImage();
    }
};
class ImageViewer {
    shared_ptr<Image> m_image;
public:
    ImageViewer(shared_ptr<Image> image) {
        m_image = image;
    }
    string See() {
        return m_image->showImage();
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
    shared_ptr<Image> image = make_shared<ProxyImage>();
    ImageViewer imageViewer(image);
    do_test(imageViewer.See(), "HighResolutionImage");
}
int main()
{
    Test();

    system("pause");
    return 0;
}
