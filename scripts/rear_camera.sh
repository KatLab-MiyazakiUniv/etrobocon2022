#!/bin/bash

port=${1}
if [[ "${1}" == "" ]]; then
    # デフォルト値
    port=10338
fi

bash -c "echo angle | nc 127.0.0.1 ${port}"
