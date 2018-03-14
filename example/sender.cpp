/*************************************************************************
 * File Name: client.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 06:41:05 PM CST
 *************************************************************************/

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <typeinfo>
#include "MessageHandlerFactory.h"
#include "LCMMessageHandler.h"
#include "ROSMessageHandler.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define random(x) (rand()%x)

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

void signalHandler( int a )    
{
    cout << "You have pressed Ctrl+C. Exiting..." << endl;
    exit(0);
}

int main(int argc, char** argv)
{
    CMessageHandlerFactory * pMHFactory = new CMessageHandlerFactory();
    CMessageHandler * pMessageHandler = pMHFactory->CreateMessageHandler(LCM);
    pMessageHandler->init(argc, argv, "sender");
    signal(SIGINT, signalHandler);

    int i;
    while (true) {
        Document my_data(kObjectType);
        Document::AllocatorType& allocator = my_data.GetAllocator();
        std::time_t result = std::time(NULL);
        std::asctime(std::localtime(&result));
        my_data.AddMember("timestamp", (uint64_t)result, allocator);
        Value position(kArrayType);
        for (i=0; i<3; i++)
            position.PushBack(random(10), allocator);
        my_data.AddMember("position", position, allocator);
        Value orientation(kArrayType);
        for (i=0; i<4; i++)
            orientation.PushBack(random(2), allocator);
        my_data.AddMember("orientation", orientation, allocator);

        my_data.AddMember("name", "example name", allocator);
        my_data.AddMember("enabled", true, allocator);

        show_data(my_data);
        std::string channel = "EXAMPLE";

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        my_data.Accept(writer);
        std::string msgstr = buffer.GetString();

        pMessageHandler->publish(channel, msgstr);
        usleep(50000);
    }

    return 0;
}
