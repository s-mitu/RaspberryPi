#!/usr/local/bin/python2
# -*- coding: utf-8 -*-

import sys
import twitterfunc
if len(sys.argv) > 1:
    message = sys.argv[1]
else:
    quit()

twitter = twitterfunc.oauth()
print twitter


twitterfunc.post(twitter, message)
