/*************************************************************************
 * File Name: LCMMessageHandler.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 05:19:26 PM CST
 *************************************************************************/

#include <iostream>
#include <map>
#include <lcm/lcm.h>
#include "LCMMessageHandler.h"
using namespace std;

static set<CLCMMessageHandler*> lcm_handlers;

void handleMessage(const lcm_recv_buf_t* rbuf, const char *chan, void *userdata)
{
    set<CLCMMessageHandler*>::const_iterator itr;
    for(itr=lcm_handlers.begin();itr!=lcm_handlers.end();itr++) {
        (*itr)->save(string(chan), string((char*)rbuf->data));
    }
    if (userdata!=NULL)
        ((MsgHandlerFunc)userdata)(string(chan), string((char*)rbuf->data));
}

CLCMMessageHandler::CLCMMessageHandler():CMessageHandler()
{
    lcm = NULL;
    lcm_handlers.insert(this);
}

CLCMMessageHandler::~CLCMMessageHandler()
{
    lcm_destroy (lcm);
    lcm_handlers.erase(this);
}

bool CLCMMessageHandler::init(int argc, char **argv, const std::string& name)
{
    this->lcm = lcm_create (NULL);
    cout<<"LCM init OK."<<endl;
    cout<<"Handler name is :"<<name<<endl;

    return true;
}

bool CLCMMessageHandler::publish(const std::string& channel, const std::string& msgstr)
{
    lcm_publish (lcm, channel.c_str(), msgstr.c_str(), msgstr.length()+1);
    return true;
}

bool CLCMMessageHandler::subscribe(const std::string& channel,
        MsgHandlerFunc handlerMethod)
{
    lcm_subscription_t * sub = lcm_subscribe(lcm, channel.c_str(), handleMessage, (void*)handlerMethod);
    this->m_subs[channel].insert(sub);
    return true;
}

bool CLCMMessageHandler::unsubscribe(const std::string& channel)
{
    set<lcm_subscription_t *> subs = this->m_subs[channel];
    set<lcm_subscription_t *>::iterator it;
    for(it=subs.begin();it!=subs.end();it++) {
        lcm_subscription_t * sub = *it;
        lcm_unsubscribe(this->lcm, sub);
    }
    m_subs.erase(channel);
    return true;
}

bool CLCMMessageHandler::spin()
{
    while(0 == lcm_handle(this->lcm));
    return true;
}

bool CLCMMessageHandler::spinOnce()
{
    lcm_handle(this->lcm);
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

