#!/bin/bash

function send_notification(){
    brightness=$(light -G)
    dunstify -a "brightnessnotification" -u normal -r "9994" -h int:value:"$brightness" "Brightness: ${brightness}" -t 2000
}

case $1 in
up)
    light -A 5
    send_notification $1
    ;;
down)
    light -U 5 
    send_notification $1
    ;;
esac