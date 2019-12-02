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
�ṹģʽ��Adapter Pattern, Proxy Pattern
Ŀ�ģ�
�ṹģʽ��������߶�������

��Χ��
�ṹ����ģʽʹ�ü̳л�������������Adapter�����ṹ����ģʽ�������˶������װ��ʽ����Adapter�������Ľṹģʽ
*/

/*
����ģʽ
What
  Ϊ�����Ķ����ṩһ���������Կ��ƶ��������ķ���
Why
  ����һ����һ������ķ���
  ��ʱ������Դ����ȷ������Ҫ��ʱ��Ŵ���
How �����ԣ�
  Զ�̴���Remote Proxy��Ϊһ�������ڲ�ͬ�ĵ�ַ�ռ��ṩ�ֲ�����
  �����Virtual Proxy��������Ҫ���������ܴ�Ķ�����ʱ����
  ��������Protection Proxy�����ƶ�ԭʼ����ķ��ʡ������������ڶ���Ӧ���в�ͬ�ķ���Ȩ�޵�ʱ��
  ����ָ�루Smart Reference�� ȡ���˼򵥵�ָ�룬���ڷ��ʶ���ʱִ��һЩ���Ӳ�����
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
