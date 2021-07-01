#!/bin/bash

pslist=$(ps a)
if ! echo $pslist | grep "python3 -m http.server" &>/dev/null; then
    python3 -m http.server --directory dist/ &
fi

trap ctrl_c INT
function ctrl_c() {
    pkill -f "python3 -m http.server"
    exit
}

make
while :; do inotifywait src -e close_write 1>&2; make 1>&2; echo "done"; done | ./websockifier 0.0.0.0 8001
