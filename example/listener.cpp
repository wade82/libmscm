/*************************************************************************
 * File Name: listener.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 06:41:05 PM CST
 *************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "MessageHandlerFactory.h"
#include "MessageHandler.h"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

void show_data(const Document& data)
{
    cout<<"  timestamp   = "<<data["timestamp"].GetInt()<<'\n'
        <<"  position    = ";
    const Value& position = data["position"];
    for (Value::ConstValueIterator itr = position.Begin(); itr != position.End(); ++itr)
        cout<<itr->GetInt()<<"  ";
    cout<<"\n"<<"  orientation = ";
    const Value& orientation = data["orientation"];
    for (Value::ConstValueIterator itr2 = orientation.Begin(); itr2 != orientation.End(); ++itr2)
        cout<<itr2->GetInt()<<"  ";
    cout<<'\n'<<"  name        = "<<data["name"].GetString()<<'\n'
        <<"  enabled     = "<<(data["enabled"].GetBool()?"true":"false")<<endl;
}

void handleMessage(const std::string& channel, const std::string& jsonmsg)
{
    Document d;
    d.Parse(jsonmsg.c_str());
    cout<<"\n>>>Receive data (from "<<channel<<"):"<<endl;
    show_data(d);
}

void int_handler(int signum)
{
    cout << "\nreceived SIGINT, doing force shutting down.."<<endl;
    exit(0);
}

void quit_handler(int signum)
{
    cout << "\nreceived SIGQUIT, doing graceful shutting down.."<<endl;
    exit(0);
}

int main(int argc, char** argv)
{
    int type = LCM;
    CMessageHandlerFactory * pMHFactory = new CMessageHandlerFactory();
    CMessageHandler * pMessageHandler = pMHFactory->CreateMessageHandler(type);
    pMessageHandler->init(argc, argv, "listener");

    signal(SIGINT, int_handler);
    signal(SIGQUIT, quit_handler);

    std::string channel = "EXAMPLE";
    // 订阅消息，handlMessage可以省略
    pMessageHandler->subscribe(channel, handleMessage);
    //pMessageHandler->spin();
    while(true) {
        pMessageHandler->spinOnce();
        // 可以在此处获取并处理数据.
        cout<<pMessageHandler->getData(channel)<<endl;
    }

    return 0;
}
