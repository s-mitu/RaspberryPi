#!/usr/local/bin/python2
# -*- coding: utf-8 -*-

import twitterfunc

twitter = twitterfunc.oauth()
print twitter

#post(twitter, message)
results = twitterfunc.search(twitter, "#FreeBSDWorkshop")
if results != None:
    for result in results:
        print "%s:%s" %(result["user"]["id"], result["text"])
else:
    print "None"
