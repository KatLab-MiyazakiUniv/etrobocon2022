#!/bin/bash

# デフォルト値
port=10338

# キャリブレーションの実行
if [[ "${1}" == "--calibrate" ]]; then
    bash -c "echo calibrate | nc 127.0.0.1 ${port}"
    echo ''  # 改行をする
    exit 0
fi

# 角度補正の場合
if [[ "${1}" != "" ]]; then
    port=${1}
fi

bash -c "echo angle | nc 127.0.0.1 ${port}"
