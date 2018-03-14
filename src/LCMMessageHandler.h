/*************************************************************************
 * File Name: MessageHandler.h
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 03:55:48 PM CST
 *************************************************************************/

#pragma once
#include <iostream>
#include <map>
#include <set>
#include <lcm/lcm.h>
//#include <lcm/lcm-cpp.hpp>
//#include "lcm_jsonmsg.hpp"
#include "MessageHandler.h"
using namespace std;

class CLCMMessageHandler:public CMessageHandler
{
public:
    CLCMMessageHandler();
    ~CLCMMessageHandler();
public:
    bool init(int argc, char** argv, const std::string& name);
    bool publish(const std::string& channel, const std::string& msgstr);
    bool subscribe(const std::string& channel,
            MsgHandlerFunc handlerMethod=NULL);
    bool unsubscribe(const std::string& channel);
    bool spin();
    bool spinOnce();
    //friend void defaultHandler(const std::string& channel, const std::string& jsonmsg);
    friend void handleMessage(const lcm_recv_buf_t* rbuf, const char *chan, void *userdata);
private:
    //lcm::LCM *pLCM;
    lcm_t * lcm;
    map<string, string> databuf;
    //map<string, set<lcm::Subscription *> > m_subs;
    map<string, set<lcm_subscription_t*> > m_subs;
    //void register_callback(uint64_t, MsgHandlerFunc);
    //void unregister_callback(uint64_t);

public:
    void save(const std::string& channel, const std::string& jsonmsg);
    string getData(const string& channel);
};

/*
class HandlerWrapper
{
public:
    ~HandlerWrapper() {}
    void handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const lcm::lcm_jsonmsg* msg);
};
*/

