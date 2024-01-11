#!/bin/bash

powermenu ()
{
  options="cancel\nshutdown\nrestart"
  selected=$(echo -e "$options" | dmenu -fn "JetBrains Mono Nerd Font")
  if [[ "$selected" = "shutdown" ]]; then
    confirm=$(echo -e "yes\nno" | dmenu -fn "JetBrains Mono Nerd Font")
    [[ $confirm = "yes" ]] && poweroff || return
  elif [[ "$selected" = "restart" ]]; then
    confirm=$(echo -e "yes\nno" | dmenu -fn "JetBrains Mono Nerd Font")
    [[ $confirm = "yes" ]] && reboot || return
  elif [[ "$selected" = "cancel" ]]; then
    return
  fi
}

powermenu
