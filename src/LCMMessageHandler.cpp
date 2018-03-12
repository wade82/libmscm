/*************************************************************************
 * File Name: LCMMessageHandler.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 05:19:26 PM CST
 *************************************************************************/

#include <iostream>
#include <map>
#include <lcm/lcm-cpp.hpp>
#include "LCMMessageHandler.h"
using namespace std;
using namespace lcm;

// 不能放在HandlerWrapper中，地址不对了。
static map<uint64_t, MsgHandlerFunc> callbacks;
static set<CLCMMessageHandler*> lcm_handlers;

void defaultHandler(const std::string& channel, const std::string& jsonmsg)
{
    set<CLCMMessageHandler*>::const_iterator itr;
    for(itr=lcm_handlers.begin();itr!=lcm_handlers.end();itr++) {
        (*itr)->save(channel, jsonmsg);
    }
}

void CLCMMessageHandler::register_callback(uint64_t handler_addr, MsgHandlerFunc callback)
{
    callbacks[handler_addr] = callback;
}

void CLCMMessageHandler::unregister_callback(uint64_t handler_addr)
{
    callbacks.erase(handler_addr);
}

CLCMMessageHandler::CLCMMessageHandler():CMessageHandler()
{
    pLCM = NULL;
    lcm_handlers.insert(this);
}

CLCMMessageHandler::~CLCMMessageHandler()
{
    if (pLCM)
        delete pLCM;
    pLCM = NULL;
    lcm_handlers.erase(this);
}

bool CLCMMessageHandler::init(int argc, char **argv, const std::string& name)
{
    if (argc>1) {
        cout<<argc<<"==="<<argv[1]<<endl;
        pLCM = new lcm::LCM(argv[1]);
    }
    else
        pLCM = new lcm::LCM();
    if(!pLCM->good())
        return false;
    cout<<"LCM init OK."<<endl;
    cout<<"Handler name is :"<<name<<endl;

    return true;
}

bool CLCMMessageHandler::publish(const std::string& channel, const std::string& msgstr)
{
    lcm::lcm_jsonmsg msg;
    msg.jsonstr = msgstr;
    pLCM->publish(channel, &msg);
    return true;
}

bool CLCMMessageHandler::subscribe(const std::string& channel,
        MsgHandlerFunc handlerMethod)
{
    HandlerWrapper handlerObject;
    if (handlerMethod==NULL) {
        cout<<"subscribe:handlerMethod is NULL, use default."<<endl;
        register_callback((uint64_t)&handlerObject, defaultHandler);
    }
    else {
        register_callback((uint64_t)&handlerObject, handlerMethod);
    }

    Subscription * sub = pLCM->subscribe(channel,
            &HandlerWrapper::handleMessage, &handlerObject);
    this->m_subs[channel].insert(sub);
    return true;
}

bool CLCMMessageHandler::unsubscribe(const std::string& channel)
{
    set<Subscription *> subs=this->m_subs[channel];
    set<Subscription *>::iterator it;
    for(it=subs.begin();it!=subs.end();it++) {
        Subscription * sub = *it;
        pLCM->unsubscribe(sub);
    }
    m_subs.erase(channel);
    return true;
}

bool CLCMMessageHandler::spin()
{
    while(0 == pLCM->handle());
    return true;
}

bool CLCMMessageHandler::spinOnce()
{
    pLCM->handle();
    return true;
}

void CLCMMessageHandler::save(const std::string& channel, const std::string& jsonmsg)
{
    this->databuf[channel]=jsonmsg;
}

string CLCMMessageHandler::getData(const std::string& channel)
{
    return this->databuf[channel];
}

void HandlerWrapper::handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const lcm::lcm_jsonmsg* msg)
{
    map<uint64_t, MsgHandlerFunc>::iterator iter;
    iter = callbacks.find((uint64_t)this);
    if(iter != callbacks.end()) {
        (iter->second)(chan, msg->jsonstr);
    }
}

