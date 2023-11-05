#!/bin/bash

# Check if trayer is running
if pgrep trayer > /dev/null; then
  # Trayer is running, so kill it
  pkill trayer
  # echo "Trayer was running and has been killed."
else
  # Trayer is not running, so start it
  trayer --edge top --align center --widthtype request --height 24 &  # Replace "--options-here" with your desired trayer options
  # echo "Trayer was not running and has been started."
fi