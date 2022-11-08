#!/bin/bash

# キャリブレーションの実行
if [[ "${1}" == "--calibrate" ]]; then
    bash -c "echo calibrate | nc 127.0.0.1 10338"
    echo ''  # 改行をする
    exit 0
fi

# 角度補正の場合
port=${1}
if [[ "${1}" == "" ]]; then
    # デフォルト値
    port=10338
fi

bash -c "echo angle | nc 127.0.0.1 ${port}"
