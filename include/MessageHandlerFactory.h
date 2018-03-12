/*************************************************************************
 * File Name: MessageHandlerFactory.h
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 01:36:13 PM CST
 *************************************************************************/

#pragma once
#include <iostream>
#include "MessageHandler.h"
using namespace std;

class CMessageHandlerFactory
{
public:
    CMessageHandlerFactory() { };
    ~CMessageHandlerFactory() { };
public:
    CMessageHandler * CreateMessageHandler(int type);
};


