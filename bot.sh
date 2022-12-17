#!/bin/bash
declare -i row
declare -i col

while true
do
  row = $(($RANDOM % 3 + 1))
  col = $(($RANDOM % 3 + 1))
  echo "Player 2: makes their move $row $col"
  sleep 1
done