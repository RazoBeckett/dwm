#!/bin/bash


# ---- USING brightnessctl ----

function send_notification(){
    brightness=$(brightnessctl | awk '/Current brightness/ {print substr($4, 2, length($4)-3)}')
    dunstify -a "brightnessnotification" -u normal -r "9994" -h int:value:"$brightness" "Brightness: ${brightness}%" -t 2000
}

case $1 in
up)
	if [ $(brightnessctl | awk '/Current brightness/ {print substr($4, 2, length($4)-3)}') -lt 5 ]; then
		brightnessctl set +1%
	else
		brightnessctl set +5%
	fi
    send_notification $1
    ;;
down)
	if [ $(brightnessctl | awk '/Current brightness/ {print substr($4, 2, length($4)-3)}') -le 5 ]; then
		brightnessctl set 1%-
	else
		brightnessctl set 5%-
	fi
    send_notification $1
    ;;
esac
