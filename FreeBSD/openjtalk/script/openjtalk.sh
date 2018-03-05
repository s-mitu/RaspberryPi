#!/bin/sh
echo $* | 
open_jtalk -x /usr/local/share/open_jtalk/open_jtalk_dic_utf_8-1.08 -m /usr/local/share/hts_voice/mei_normal.htsvoice -r 0.5 -ow /dev/stdout | 
play -
