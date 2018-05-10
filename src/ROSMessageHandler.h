/*************************************************************************
 * File Name: MessageHandler.h
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 03:55:48 PM CST
 *************************************************************************/

#pragma once
#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "MessageHandler.h"

using namespace std;

class CROSMessageHandler:public CMessageHandler
{
public:
    CROSMessageHandler():CMessageHandler() { };
    ~CROSMessageHandler() { };
public:
    bool init(int argc, char **argv, const std::string& name);
    bool publish(const std::string&, const std::string& msgstr);
    bool subscribe(const std::string& channel,
            MsgHandlerFunc callback=NULL);
    bool unsubscribe(const std::string& channel);
    bool spin();
    bool spinOnce();
    string getData(const string&);
private:
    ros::NodeHandle* node;
};

