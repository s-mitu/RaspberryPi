#!/bin/sh

iicbus=/dev/iic1
i2cpath=/usr/local/bin/pi2c
orig_i2cpath=/usr/sbin/i2c

i2c="$i2cpath -f $iicbus -a 0x3e -b -d w"
i2creset="$orig_i2cpath -f $iicbus -r"

#delay=0.0005
delay=0.01
width=8
freq=500000

debug=0
linemode=0
clear=0
keep=0

outbin() {
	printf '\'`echo "ibase=16;obase=8 ;"$1 | bc `
}
writecommand()
{
	local ret
	local i
	for i in `jot 10 0`; do 
		outbin $1 |  $i2c -o 0x00 -c 1
		ret=$?
		if [ $ret -eq 0 ]; then
			sleep $delay
			break
		fi
		if [ $debug -eq 1 ]; then
			echo $1 $ret
		fi
		sleep $delay
		
	done
	sleep $delay
}
writedata()
{
	local ret=1
	local pos=0
	local line=0
	local base=0
	local i
	while true; do
		IFS_X=$IFS
		IFS=$'\n'
		for i in `echo "$1" | sed -E "s/(.)/\1\\\\"$'\n'"/g"`; do
			IFS=$IFS_X
			if [ $pos -ge $width -a $linemode -ne 1 ] || [ $pos -eq 0 -a $linemode -eq 2 ]; then
				if [ $line -eq 0 ]; then
					line=$(($line+1))
					base=0x40
					pos=0
					writecommand `printf "%02X" $(($base + 0x80))`
				else	
					break
				fi
			fi
			for j in `jot 10 0`; do 
				printf "$i" |  $i2c -o 0x40 -c 1
				ret=$?
				if [ $ret -ne 0 ]; then
					writecommand `printf "%02X" $(($pos + $base + 0x80))`
					continue
				else
					sleep $delay
				fi
				break
			done
			if [ $debug -eq 1 ]; then
				echo '"'$i'"' $ret
			fi
			sleep $delay
			pos=$(($pos+1))
		done
		IFS=$IFS_X
		if [ $ret -eq 0 ]; then
			break;
		fi
	done
}
init() {
	if [ `sysctl -n dev.iicbus.1.frequency` -ne $freq ]; then
		sysctl dev.iicbus.1.frequency=$freq
		#/usr/local/bin/pi2c -f $iicbus -r
		$i2creset
	fi
	writecommand "38"
	writecommand "39"
	writecommand "14"
	writecommand "73"
	writecommand "56"
	writecommand "6C"
	writecommand "38"
	#writecommand "01"
	writecommand "0C"
}
while getopts "w:ulbdck" i
do
	case "$i"
	in
	\?) printf "arg error\n" >/dev/stderr; exit 2;;
	w)
		width="$OPTARG";;
	b)
		linemode=0;;
	u)
		linemode=1;;
	l)
		linemode=2;;
	c)
		clear=1;;
	k)
		keep=1;;
	d)
		debug=1;;
	esac
done

shift $(( $OPTIND - 1 ))

if [ $keep -eq 0 ];then
	init
fi

sleep 0.1


ret=0
if [ $clear -eq 0 ]; then
	params=$(echo $* | sed -e "s/$1//")
	data=$(printf "$1" $(echo $* | sed -e "s/$1//"))
	ret=$?
fi

if [ "$ret" -ne 0 ]; then
	printf "printf error" >/dev/stderr
else
	# hyde
	#writecommand "08"
	if [ $linemode -gt 0 ]; then
		writedata "$(printf "%${width}s" " ")"
	else
		writecommand "01"
	fi
	if [ $clear -eq 0 ]; then
		writedata "$data"
	fi
	# show
	#writecommand "0C"
fi

exit $ret
