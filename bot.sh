#!/bin/bash

HOST="test.mosquitto.org"
TOPIC="game/move"
while [ true ]
do
spot=$((RANDOM % 9 + 1))
	case $spot in
	1) row=0; col=0;;
	2) row=0; col=1;;
	3) row=0; col=2;;
	4) row=1; col=0;;
	5) row=1; col=1;;
	6) row=1; col=2;;
	7) row=2; col=0;;
	8) row=2; col=1;;
	9) row=2; col=2;;
	esac
	echo "Player 2: moves $row, $col"
sleep 1
done

mosquitto_publish -h $HOST -t $TOPIC -m "$row $col"
