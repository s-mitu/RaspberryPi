#!/bin/sh
pi2c="/usr/local/bin/pi2c -f /dev/iic1 -a 0x18"
echo $pi2c
if [ `$pi2c  -o 0x16 2>&1` = "00" ]; then
	/usr/local/bin/perl -e 'printf("\x80");' |  $pi2c  -o 0x16 -b -d w
fi
if [ `$pi2c -o 0x0c 2>&1` = "80" ]; then
	/usr/local/bin/openjtalk.sh '平らです'
else
	/usr/local/bin/openjtalk.sh '斜めってます'

fi

