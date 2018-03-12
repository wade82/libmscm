/*************************************************************************
 * File Name: MessageHandlerFactory.cpp
 * Author: Wei Zhang
 * mail: wei.zhang@genetalks.com
 * Created Time: Sun 04 Mar 2018 03:45:19 PM CST
 *************************************************************************/

#include <iostream>
#include "MessageHandlerFactory.h"
#include "MessageHandler.h"
#include "LCMMessageHandler.h"
#include "ROSMessageHandler.h"

CMessageHandler * CMessageHandlerFactory::CreateMessageHandler(int type) {
    CMessageHandler * pMessageHandler = NULL;
    switch (type) {
        case LCM:
            pMessageHandler = (CMessageHandler *)new CLCMMessageHandler();
            break;
        case ROS:
            pMessageHandler = (CMessageHandler *)new CROSMessageHandler();
            break;
        case DDS:
        default:
            cout<<"Unknown handle type."<<endl;
            break;
    }
    return pMessageHandler;
}

