#!/bin/bash

changeit() {
	feh --bg-fill --randomize ~/Pictures/Wallpapers/Gruvbox/*
}

while true;
do
	changeit
	sleep 1000
done
