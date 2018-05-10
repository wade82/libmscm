/*************************************************************************
 * File Name: ROSMessageHandler.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 05:19:26 PM CST
 *************************************************************************/

#include <iostream>
#include "ROSMessageHandler.h"

using namespace std;

void defaultHandler(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

bool CROSMessageHandler::init(int argc, char** argv, const std::string& name)
{
    cout<<"invoke function CROSMessageHandler::init"<<endl;
    ros::init(argc, argv, "listener");
    return true;
}

bool CROSMessageHandler::publish(const std::string& channel, const std::string& msgstr)
{
    ros::Publisher pub = node->advertise<std_msgs::String>(channel, 1000);
    std_msgs::String msg;
    msg.data = msgstr;
    pub.publish(msg);
    return true;
}

bool CROSMessageHandler::subscribe(const std::string& channel, MsgHandlerFunc callback)
{
    ros::Subscriber sub = node->subscribe(channel.c_str(), 1000, defaultHandler);
    return true;
}

bool CROSMessageHandler::unsubscribe(const std::string& channel)
{
    return true;
}

bool CROSMessageHandler::spin()
{
    ros::spin();
    return true;
}

bool CROSMessageHandler::spinOnce()
{
    ros::spinOnce();
    return true;
}

string CROSMessageHandler::getData(const string& channel)
{
    return "";
}

