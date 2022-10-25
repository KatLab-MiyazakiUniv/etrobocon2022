#!/bin/bash
set -eu

buildDir="build"

# NOTE: 必要に応じて build ディレクトリの削除を実行する処理
if [ -d $buildDir ]; then
    cmakeSourceDir=""
    
    # NOTE: build ディレクトリにある Makefile 中の CMAKE_SOURCE_DIR に記述されたパスを取得する
    if [ -f "${buildDir}/Makefile" ]; then
        cmakeSourceDir=`cat ${buildDir}/Makefile | grep -oE "^CMAKE_SOURCE_DIR\s=\s((/.+)+)$" | sed -r "s/^CMAKE_SOURCE_DIR\s=\s((\/.+)+)$/\1/g"`
    fi
    
    # NOTE: 上記で取得したパスとカレントディレクトリが異なる場合、実行環境が変更されたと判断して build ディレクトリを削除する
    if [ "${cmakeSourceDir}" != "`pwd`" ]; then
        echo "[LOG]   実行環境の変更が検出されたため '${buildDir}' ディレクトリを削除します"
        rm -rf build
    fi
fi

# NOTE: 実行とテストでカレントディレクトリが異なり，テストの際にファイルパスの指定ができないため，テスト用にdatafiles/及びscripts/ディレクトリを作成・コピーする
mkdir -p build/etrobocon2022/datafiles
mkdir -p build/etrobocon2022/scripts
cd build
cp ../datafiles/*.csv etrobocon2022/datafiles/
cp ../scripts/*.sh etrobocon2022/scripts/
chmod 744 ./etrobocon2022/scripts/*.sh

cmake -DCMAKE_BUILD_TYPE=Coverage ..
cmake --build .
export GTEST_COLOR=1
ctest -VV

rm -rf etrobocon2022/
rm result.txt
