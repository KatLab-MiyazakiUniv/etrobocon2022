#!/bin/bash -eu

# @file: sim-test-wsl.sh
# @author: Takahiro55555
# @brief: 設定ファイルを適用した後、シミュレータを動作させる
#         WSL で動作させることしか考えていない
#         sim-settings/l 又は、sim-settings/r ディレクトリ中の設定ファイルの数だけテストを行う

# 日付
DAY=`date '+%Y-%m-%d'`
TIME=`date '+%H-%M-%S'`

### 以下、設定 ###
LOG_FILES_DIR="`pwd`/logs/${DAY}/${TIME}"  # ログを格納するディレクトリ名
MD_FILE_NAME='result.txt'  # マークダウン形式で出力するファイル
CSV_FILE_NAME='result.csv'  # CSV 形式で出力するファイル
### 以上、設定 ###

# このシェルスクリプトを Ctrl-C で強制終了した際、
# バックグランドで実行しているプロセスも強制終了する
trap 'kill $(jobs -p)' EXIT

### 以下、必要なパッケージの確認・インストール ###
INSTALL_PACKAGE_LIST=""
if [ `dpkg -l | grep '^ii' | grep ffmpeg | wc -l` -eq "0" ]; then
    INSTALL_PACKAGE_LIST="ffmpeg "
fi

if [ `dpkg -l | grep '^ii' | grep -oE "\sjq\s" | wc -l` -eq "0" ]; then
    INSTALL_PACKAGE_LIST+="jq "
fi

if [ "${INSTALL_PACKAGE_LIST}" != "" ]; then
    echo "Install additional packages (${INSTALL_PACKAGE_LIST})"
    sudo apt update && sudo apt install $INSTALL_PACKAGE_LIST
fi
### 以上、必要なパッケージの確認・インストール ###



### 以下、シミュレータを実行し、結果を集計する ###
mkdir -p ${LOG_FILES_DIR}/.logs

# シミュレータを起動
echo 'sim' | ${HOME}/startetrobo shell

# 設定ファイルをシミュレータに反映した後、プログラムを実行する
# awk コマンドの -v オプションで awk 中のスクリプトにシェル変数を渡している
ls sim-settings/?/* | \
    xargs -L1 -I{} ./scripts/sim-test-wsl.sh {} ${LOG_FILES_DIR} | \
    awk -v md_file_path=${LOG_FILES_DIR}/${MD_FILE_NAME} \
        -v csv_file_name=${LOG_FILES_DIR}/${CSV_FILE_NAME} '
    BEGIN {
        # ループの最初に1度だけ呼び出されるブロック
        # ここでは、変数の初期化を行っている
        counter = 0;
        run_time_sum = 0;
        goaled_num = 0;
    }
    {
        # 標準出力から1行出力されるたびに呼び出されるブロック（ループ）
        # $0 に標準出力の1行が設定されている
        # $1, $2, $3, ... $n には標準出力の1行をスペースで区切ったものが順に設定されている

        # 新たなシミュレーションの開始を検知
        if($0 ~ /\[ script: starting: [0-9a-zA-Z_\-]+ \]/){
            counter++;
            STATISTICS[counter]["course"]                    = "None";
            STATISTICS[counter]["goal_time"]                 = "None";
            STATISTICS[counter]["env_light_intensity_level"] = "None";
            STATISTICS[counter]["env_light_rotation"]        = "None";
            STATISTICS[counter]["l_spot_light"]              = "None";
            STATISTICS[counter]["r_spot_light"]              = "None";
            STATISTICS[counter]["start_gate"]                = "None";
            STATISTICS[counter]["gate_1"]                    = "None";
            STATISTICS[counter]["gate_2"]                    = "None";
            STATISTICS[counter]["capture_rate"]              = "None";
            STATISTICS[counter]["settings_file_name"]        = "None";
            print $0;
        }

        # 設定ファイル名を取得
        if($0 ~ /\[ script: settings file name: .+\]/){
            STATISTICS[counter]["settings_file_name"] = $6;
            print "\n" $0;
        }

        # シミュレータをキャプチャする際のフレームレートを取得
        if($0 ~ /\[ script: captureRate: [0-9] \]/){
            if ($4 == 0) {
                STATISTICS[counter]["capture_rate"] = "OFF";
            } else if ($4 == 1) {
                STATISTICS[counter]["capture_rate"] = "60fps";
            } else if ($4 == 2) {
                STATISTICS[counter]["capture_rate"] = "30fps";
            } else if ($4 == 3) {
                STATISTICS[counter]["capture_rate"] = "20fps";
            } else if ($4 == 4) {
                STATISTICS[counter]["capture_rate"] = "15fps";
            }
            print $0;
        }

        # 照明関連の情報取得
        if($0 ~ /\[ script: EnvLightIntensityLevel: [0-3] \]/){
            STATISTICS[counter]["env_light_intensity_level"] = $4;
            print $0;
        }
        if($0 ~ /\[ script: EnvLightRotation: [0-3] \]/){
            STATISTICS[counter]["env_light_rotation"] = $4;
            print $0;
        }
        if($0 ~ /\[ script: LSpotLight: [0-3] \]/){
            STATISTICS[counter]["l_spot_light"] = $4;
            print $0;
        }
        if($0 ~ /\[ script: RSpotLight: [0-3] \]/){
            STATISTICS[counter]["r_spot_light"] = $4;
            print $0;
        }

        # コース情報を取得
        if($0 ~ /\[ launcher: ready to start on right course \]/){
            STATISTICS[counter]["course"] = "Right";
        }else if($0 ~ /\[ launcher: ready to start on left course \]/){
            STATISTICS[counter]["course"] = "Left";
        }

        # スタートゲート通過情報を取得
        if($0 ~ /^\[ launcher: ((left)|(right)): passed Start Gate \]$/){
            STATISTICS[counter]["start_gate"] = "true";
            print $0;
        }

        # ゲート1通過情報を取得
        if($0 ~ /^\[ launcher: ((left)|(right)): passed Gate 1 \]$/){
            STATISTICS[counter]["gate_1"] = "true";
            print $0;
        }

        # ゲート2通過情報を取得
        if($0 ~ /^\[ launcher: ((left)|(right)): passed Gate 2 \]$/){
            STATISTICS[counter]["gate_2"] = "true";
            print $0;
        }

        # ゴール通過情報を取得
        if($0 ~ /^\[ launcher: ((left)|(right)): GOAL!  Goal Time: [0-9]*\.[0-9]* \]$/){
            STATISTICS[counter]["goal_time"] = $7;
            run_time_sum += $7;
            goaled_num++;
            print $0;
        }
    }
    END {
        # ループの最後に1度だけ呼び出されるブロック
        
        if(counter == 0){
            print "ERR: シミュレータログの検出に失敗";
            exit 1;
        }

        ### 以下、CSVファイル生成 ###
        # ヘッダ行の作成
        printf "course,"                    >> csv_file_name;
        printf "goal_time,"                 >> csv_file_name;
        printf "env_light_intensity_level," >> csv_file_name;
        printf "env_light_rotation,"        >> csv_file_name;
        printf "l_spot_light,"              >> csv_file_name;
        printf "r_spot_light,"              >> csv_file_name;
        printf "start_gate,"                >> csv_file_name;
        printf "gate_1,"                    >> csv_file_name;
        printf "gate_2,"                    >> csv_file_name;
        printf "capture_rate,"              >> csv_file_name;
        printf "settings_file_name"         >> csv_file_name;
        printf "\n"                         >> csv_file_name;

        # データ行の作成
        for (i in STATISTICS) {
            # NOTE: 表示順序を指定するためにループを使用していない
            printf "%s,", STATISTICS[i]["course"]                    >> csv_file_name;
            printf "%s,", STATISTICS[i]["goal_time"]                 >> csv_file_name;
            printf "%s,", STATISTICS[i]["env_light_intensity_level"] >> csv_file_name;
            printf "%s,", STATISTICS[i]["env_light_rotation"]        >> csv_file_name;
            printf "%s,", STATISTICS[i]["l_spot_light"]              >> csv_file_name;
            printf "%s,", STATISTICS[i]["r_spot_light"]              >> csv_file_name;
            printf "%s,", STATISTICS[i]["start_gate"]                >> csv_file_name;
            printf "%s,", STATISTICS[i]["gate_1"]                    >> csv_file_name;
            printf "%s,", STATISTICS[i]["gate_2"]                    >> csv_file_name;
            printf "%s,", STATISTICS[i]["capture_rate"]              >> csv_file_name;
            printf "%s,", STATISTICS[i]["settings_file_name"]        >> csv_file_name;
            printf "\n" >> csv_file_name
        }
        ### 以上、CSVファイル生成 ###


        ### 以下、Markdown形式ファイル生成(.txt ファイル) ###
        ## 各実験結果テーブルの作成
        print "### 各実験結果" > md_file_path;

        # ヘッダー行の作成
        printf "| 番号 "                   >> md_file_path;
        printf "| 全体の明るさ "           >> md_file_path;
        printf "| 影の方向 "               >> md_file_path;
        printf "| スポットライトLの明るさ " >> md_file_path;
        printf "| スポットライトRの明るさ " >> md_file_path;
        printf "| コース "                 >> md_file_path;
        printf "| 走行時間 "               >> md_file_path;
        printf "| 設定ファイル名 |\n"       >> md_file_path;

        printf "| ---- "                   >> md_file_path;
        printf "| ----------- "            >> md_file_path;
        printf "| ------- "                >> md_file_path;
        printf "| --------------------- "  >> md_file_path;
        printf "| --------------------- "  >> md_file_path;
        printf "| ------ "                 >> md_file_path;
        printf "| ------- "                >> md_file_path;
        printf "| ------------- |\n"       >> md_file_path;

        # データ行の作成
        for (i in STATISTICS) {
            printf "| %s ",    i                                           >> md_file_path;
            printf "| %s ",    STATISTICS[i]["env_light_intensity_level"]  >> md_file_path;
            printf "| %s ",    STATISTICS[i]["env_light_rotation"]         >> md_file_path;
            printf "| %s ",    STATISTICS[i]["l_spot_light"]               >> md_file_path;
            printf "| %s ",    STATISTICS[i]["r_spot_light"]               >> md_file_path;
            printf "| %s ",    STATISTICS[i]["course"]                     >> md_file_path;
            printf "| %s ",    STATISTICS[i]["goal_time"]                  >> md_file_path;
            printf "| %s |\n", STATISTICS[i]["settings_file_name"]         >> md_file_path;
        }

        ## 集計テーブルの作成
        run_time_average = 0;
        if (goaled_num != 0) {
            run_time_average = run_time_sum/goaled_num;
        }
        goal_persentage = goaled_num/counter*100;
        print  "### 集計結果"                                         >> md_file_path;
        print  "| 走行エリア平均 | 成功率 |"                           >> md_file_path;
        print  "| ------------- | ----- |"                            >> md_file_path;
        printf "| %3.3f [s] (n=%d)    ", run_time_average, goaled_num >> md_file_path;
        printf "| %3.3f [%] (n=%d) |\n", goal_persentage , counter    >> md_file_path;
        ### 以上、Markdown形式ファイル生成(.txt ファイル) ###


        ### 以下、標準出力 ###
        print "走行エリア平均 : " run_time_average " [s] (n=" goaled_num ")";
        print "成功率        : " goal_persentage " [%] (n=" counter ")";
        ### 以上、標準出力 ###
    }' && (cd ${LOG_FILES_DIR}; explorer.exe .) || :
    # 上記の && 以降で生成した Markdown 形式のファイルを開く処理を行っている
### 以上、シミュレータを実行し、結果を集計する ###


if [ -f ".cancel-sim-test" ]; then
    rm -f .cancel-sim-test
    echo "sim stop" | ${HOME}/startetrobo shell
    echo "キャンセルされました"
    exit 800
fi
