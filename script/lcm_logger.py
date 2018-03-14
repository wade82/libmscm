#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
lcm_logger.py
Created on 2018-03-14 16:22:55
@author: Wei Zhang <wei.zhang@genetalks.com>
"""

import sys
import lcm
import time
import signal

global msg_logger

def signal_handler(signum, frame):
    print "\nCtrl+C pressed, Exiting..."
    msg_logger.close()
    sys.exit(0)

def msg_handler(channel, msg):
    global msg_logger
    timestamp = time.time()
    print 'Receive:', timestamp, channel, msg
    msg_logger.write_event(timestamp, channel, msg)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)
    my_lcm = lcm.LCM()
    global msg_logger
    path = "data.log"
    msg_logger = lcm.EventLog(path,'w', overwrite=True)
    # subscribe all channels.
    my_lcm.subscribe(".*", msg_handler)
    while(not my_lcm.handle()):
        pass

