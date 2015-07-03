#!/bin/bash

echo "Starting"
# Start off by collecting some tweets
python twt.py > tmp &
COLLECT_PID=$!
echo 'Launching '
sleep 2
trap 'kill $COLLECT_PID' 2
./hashtag_network c tmp
wait

