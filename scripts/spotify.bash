status=$(playerctl metadata --format '{{artist}} - {{title}}' -p spotify 2>&1)

if [ "$status" != "No players found" ]; then
	echo "[ 🎶 $status ]"
fi
