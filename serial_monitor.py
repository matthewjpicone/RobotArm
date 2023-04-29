#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 14 12:51:41 2023

@author: matthewpicone
"""

import serial  

conn = serial.Serial('/dev/cu.usbserial-210', 115200, timeout=.1)
while True:
    output = str(conn.readline())
    if len(output) > 3:
        print(output)
