#!/bin/bash

# ---- using pactl for pipewire ----

function send_notification() {
    volume=$(pactl list sinks | grep 'Volume: front-left' | awk '{print $5}' | tr -d '%')
    dunstify -a "changevolume" -u normal -r "9993" -h int:value:"$volume" -i "audio-volume-$1" "Volume: ${volume}%" -t 2000
}

case $1 in
up)
    pactl set-sink-volume @DEFAULT_SINK@ +5%
    send_notification $1
    ;;
down)
    pactl set-sink-volume @DEFAULT_SINK@ -5%
    send_notification $1
    ;;
mute)
    pactl set-sink-mute @DEFAULT_SINK@ toggle
    if [ "$(pactl list sinks | grep 'Mute: ' | awk '{print $2}')" == "yes" ]; then
        dunstify -i volume-mute -a "changevolume" -t 2000 -r 9993 -u low "Muted"
    else
        send_notification up
    fi
    ;;
esac
