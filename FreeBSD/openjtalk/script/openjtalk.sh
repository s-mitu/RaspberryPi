#!/bin/sh
args=`getopt t: "$@"`
set -- $args 

type=mei/mei_normal.htsvoice
voicepath=/usr/local/share/hts_voice

for i 
do
	case "$i"
	in
	-t)
		type=$2;
		if [ ! -f ${voicepath}/${type} ]; then
			type=${type}.htsvoice
			if [ ! -f ${voicepath}/${type} ]; then
				echo "${voicepath}/${type} not found"
				exit 1
			fi
		fi
		shift
		shift;;
	--)
		shift;
		break;;	
	esac
done
echo $* | 
/usr/local/bin/open_jtalk -x /usr/local/share/open_jtalk/open_jtalk_dic -m ${voicepath}/${type} -r 0.5 -ow /dev/stdout | 
play -
