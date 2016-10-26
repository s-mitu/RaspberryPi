#!/usr/local/bin/python2
# -*- coding: utf-8 -*-

from requests_oauthlib import OAuth1Session
import sys
import json
import time
import serial
import romkan
import re
import subprocess
import keys

# ツイート投稿用のURL
url_post = "https://api.twitter.com/1.1/statuses/update.json"
url_search = "https://api.twitter.com/1.1/search/tweets.json"

# 認証
def oauth():
	# OAuth認証で POST method で投稿
	twitter = OAuth1Session(keys.CK, keys.CS, keys.AT, keys.AS)
	return twitter
	
# ツィート送信
def post(twitter, message):
	# ツイート本文
	params = {"status": message}

	req = twitter.post(url_post, params = params)

	# レスポンスを確認
	if req.status_code == 200:
	    print ("OK")
	else:
	    print ("Error: %d" % req.status_code)
	return req

#検索
def search(twitter, text):
	params = {"q": text}
	req = twitter.get(url_search, params = params)
	# レスポンスを確認
	if req.status_code == 200:
		results = json.loads(req.text)
		return results["statuses"]
	else:
	    print ("Error: %d" % req.status_code)
	    return None

