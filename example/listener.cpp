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
#include "LCMMessageHandler.h"
#include "ROSMessageHandler.h"
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

void signalHandler( int a )
{
    cout << "\nYou have pressed Ctrl+C. Exiting..." << endl;
    exit(0);
}

int main(int argc, char** argv)
{
    int type = LCM;
    CMessageHandlerFactory * pMHFactory = new CMessageHandlerFactory();
    CMessageHandler * pMessageHandler = pMHFactory->CreateMessageHandler(type);
    pMessageHandler->init(argc, argv, "listener");

    signal(SIGINT, signalHandler);

    std::string channel = "EXAMPLE";
    // 使用默认回调函数，由pMessageHandler存储最新数据.
    pMessageHandler->subscribe(channel);
    //pMessageHandler->subscribe(channel, handleMessage);
    //pMessageHandler->spin();
    while(true) {
        pMessageHandler->spinOnce();
        handleMessage(channel, pMessageHandler->getData(channel));
    }

    return 0;
}
