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

def main():
    my_lcm = lcm.LCM()
    path = "data.log"
    msg_logger = lcm.EventLog(path,'w', overwrite=True)

    def quit_handler(signum, _):
        print "received SIGQUIT, doing graceful shutting down.."
        msg_logger.close()
        sys.exit(0)
    signal.signal(getattr(signal, 'SIGQUIT', signal.SIGTERM), quit_handler)

    def int_handler(signum, _):
        print "received SIGINT, doing force shutting down.."
        sys.exit(1)
    signal.signal(signal.SIGINT, int_handler)

    def msg_handler(channel, msg):
        timestamp = time.time()
        print 'Receive:', timestamp, channel, msg
        msg_logger.write_event(timestamp, channel, msg)

    # subscribe all channels.
    my_lcm.subscribe(".*", msg_handler)
    try:
        while(not my_lcm.handle()):
            pass
    except CError:
        pass

if __name__ == "__main__":
    main()

