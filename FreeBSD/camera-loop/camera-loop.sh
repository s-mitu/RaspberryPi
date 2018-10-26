#!/bin/sh
delay=0.5
if [ "$1" ]; then
	delay=$1
fi
while true; do
	/usr/local/bin/raspistill -o /tmp/camera-0.jpg -w 800 -h 600
	sleep ${delay}
done
