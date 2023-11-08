#!/bin/bash

function send_notification(){
    brightness=$(light -G)
    dunstify -a "brightnessnotification" -u normal -r "9994" -h int:value:"$brightness" "Brightness: ${brightness}" -t 2000
}

case $1 in
up)
	if [ $(light -G | awk -F'\\.' '{print $1}') -lt 5 ]; then
		light -A 1
	else
		light -A 5
	fi
    send_notification $1
    ;;
down)
	if [ $(light -G | awk -F'\\.' '{print $1}') -le 5 ]; then
		light -U 1
	else
		light -U 5
	fi
    send_notification $1
    ;;
esac
