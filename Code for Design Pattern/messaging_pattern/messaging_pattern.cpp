// messaging_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include <functional>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include <List>
#include <mutex>
#include <windows.h>
using namespace std;
/*
Messaging
What
  Message queue
  是一种进程间通信或同一进程的不同线程间的通信方式，软件的贮列用来处理一系列的输入，通常是来自用户。
  消息队列提供了异步的通信协议，每一个贮列中的纪录包含详细说明的数据，包含发生的时间，输入设备的种类，以及特定的输入参数，也就是说：消息的发送者和接收者不需要同时与消息队列交互。消息会保存在队列中，直到接收者取回它。
Why
  解耦合，不关心语言和通讯协议
  无差别的Process/Machine/Service/Task通信
  此外有些Message Service还提供额外的功能
  事件驱动的程序设计

Types:
  List
  Array
  Map
  Set
Standards and protocols
 JMS
 AMQP
 STOMP
 MQTT
*/
/*
JMS
   Java消息服务（Java Message Service，JMS）应用程序接口是一个Java平台中关于面向消息中间件（MOM）的API，用于在两个应用程序之间，或分布式系统中发送消息，进行异步通信。Java消息服务是一个与具体平台无关的API，绝大多数MOM提供商都对JMS提供支持。
Java消息服务应用程序结构支持两种模型：
   点对点或队列模型
   发布/订阅模型
在点对点或队列模型下，一个生产者向一个特定的队列发布消息，一个消费者从该队列中读取消息。这里，生产者知道消费者的队列，并直接将消息发送到消费者的队列。这种模式被概括为：
   只有一个消费者将获得消息
   生产者不需要在接收者消费该消息期间处于运行状态，接收者也同样不需要在消息发送时处于运行状态。
   每一个成功处理的消息都由接收者签收
发布者／订阅者模型支持向一个特定的消息主题发布消息。0或多个订阅者可能对接收来自特定消息主题的消息感兴趣。在这种模型下，发布者和订阅者彼此不知道对方。这种模式好比是匿名公告板。这种模式被概括为：
   多个消费者可以获得消息
   在发布者和订阅者之间存在时间依赖性。发布者需要创建一个订阅（subscription），以便客户能够购订阅。订阅者必须保持持续的活动状态以接收消息，除非订阅者创建了持久的订阅。在那种情况下，在订阅者未连接时发布的消息将在订阅者重新连接时重新发布。
使用Java语言，JMS提供了将应用与提供数据的传输层相分离的方式。同一组Java类可以通过JNDI中关于提供者的信息，连接不同的JMS提供者。这一组类首先使用一个连接工厂以连接到队列或主题，然后发送或发布消息。在接收端，客户接收或订阅这些消息。
*/
/*
AMQP
  高级消息队列协议即Advanced Message Queuing Protocol（AMQP）是一个用于统一面向消息中间件实现的一套标准协议，其设计目标是对于消息的排序、路由（包括点对点和订阅-发布）、保持可靠性、保证安全性。
  高级消息队列协议保证了由不同提供商发行的客户端之间的互操作性。与先前的中间件标准（如Java消息服务），在特定的API接口层面和实现行为进行了统一不同，高级消息队列协议关注于各种消息如何作为字节流进行传递。因此，使用了符合协议实现的任意应用程序之间可以保持对消息的创建、传递。
  应用： RabbitMQ
*/
/*
Azure Service Bus
  Microsoft Azure Service Bus是一个完全托管的企业集成消息代理。
  消息为二进制格式，可以包含JSON，XML或仅包含文本。

  消息传递：传输业务数据，例如销售或采购订单，日记帐或库存移动。
  解耦应用程序：提高应用程序和服务的可靠性和可伸缩性（客户端和服务不必同时处于联机状态）。
  主题和订阅：启用发布者和订阅者之间的1：n关系。
  消息会话：实现需要消息排序或消息延迟的工作流。
功能：
  Message Session
  Auto-Forwarding
  Dead-lettering
  Scheduled delivery
  Message deferral
  Batching
  Transactions
  Filtering and actions
  Auto-delete on idle
  Duplicate detection
*/
//测试代码
bool do_test(const int src1, const int src2)
{
    if (src1 == src2)
    {
        std::cout << "Success\n" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed\n" << std::endl;
        return false;
    }
}

void Test()
{

}
int main()
{
    Test();

    system("pause");
    return 0;
}

