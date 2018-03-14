#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
lcm_replay.py
Created on 2018-03-14 18:07:22
@author: Wei Zhang <wei.zhang@genetalks.com>
"""

import lcm

if __name__ == "__main__":
    my_lcm = lcm.LCM()
    path = "data.log"
    msg_logger = lcm.EventLog(path,'r')
    for event in msg_logger:
        my_lcm.publish(event.channel, event.data)
        print event.timestamp, event.channel, event.data

