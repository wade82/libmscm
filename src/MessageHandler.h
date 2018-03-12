/*************************************************************************
 * File Name: MessageHandler.h
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 03:55:48 PM CST
 *************************************************************************/

#pragma once
#include <iostream>
using namespace std;

typedef enum HandlerType
{
    ROS,
    LCM,
    DDS,
    UNKNOWN
}HandlerType;

typedef void (*MsgHandlerFunc)(const std::string&, const std::string&);

class CMessageHandler
{
public:
    CMessageHandler() {};
    virtual ~CMessageHandler() {};
public:
    virtual bool init(int argc, char **argv, const std::string& name) = 0;

    virtual bool publish(const std::string& channel, const std::string& msgstr) = 0;
    virtual bool subscribe(const std::string& channel,
            MsgHandlerFunc handlerMethod=NULL) = 0;
    virtual bool unsubscribe(const std::string& channel) = 0;
    virtual bool spin() = 0;
    virtual bool spinOnce() = 0;
    virtual string getData(const string&) = 0;
};

