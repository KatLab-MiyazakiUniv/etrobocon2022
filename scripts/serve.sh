#!/bin/sh
# 参考:https://qiita.com/wf-yamaday/items/f890f3523eeacbe71153

PORT=8080
MESSAGE_FILE_PATH="message.txt"

message="Wait"
echo -n "$message" > $MESSAGE_FILE_PATH

while [ "$message" != "Start" ]; do
    message="$(cat $MESSAGE_FILE_PATH)"
    echo -n "$message" | nc -l -p $PORT -w 1
done

rm $MESSAGE_FILE_PATH