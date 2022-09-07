/**
 * @file   MotionParser.cpp
 * @brief  動作コマンドファイルを解析するクラス
 * @author mutotaka0426 kawanoichi sap2368 miyashita64
 */

#include "MotionParser.h"

using namespace std;

vector<Motion*> MotionParser::createMotions(const char* filePath, int targetBrightness,
                                            bool& isLeftEdge)
{
  const int BUF_SIZE = 512;
  char buf[BUF_SIZE];  // log用にメッセージを一時保持する領域
  Logger logger;
  int lineNum = 1;  // Warning用の行番号

  vector<Motion*> motionList;  // 動作インスタンスのリスト

  // ファイル読み込み
  FILE* fp = fopen(filePath, "r");
  // ファイル読み込み失敗
  if(fp == NULL) {
    snprintf(buf, BUF_SIZE, "%s file not open!\n", filePath);
    logger.logWarning(buf);
    return motionList;
  }

  char row[BUF_SIZE];           // 各行の文字を一時的に保持する領域
  const char* separator = ",";  // 行ごとにパラメータを読み込む

  while(fgets(row, BUF_SIZE, fp) != NULL) {
    vector<char*> params;
    // separatorを区切り文字にしてrowを分解し，paramに代入する
    char* param = strtok(row, separator);
    while(param != NULL) {
      // paramをパラメータとして保持する
      params.push_back(param);
      // 次のパラメータをparamに代入する
      // strtok()は第1引数にNULLを与えると、前回の続きのアドレスから処理が開始される
      param = strtok(NULL, separator);
    }

    // 取得したパラメータから動作インスタンスを生成する
    COMMAND command = convertCommand(params[0]);  // 行の最初のパラメータをCOMMAND型に変換
    if(command == COMMAND::DL) {  // 指定距離ライントレース動作の生成
      DistanceLineTracing* dl = new DistanceLineTracing(
          atof(params[1]),                                             // 目標距離
          targetBrightness + atoi(params[2]),                          // 目標輝度 + 調整
          atoi(params[3]),                                             // PWM値
          PidGain(atof(params[4]), atof(params[5]), atof(params[6])),  // PIDゲイン
          isLeftEdge);                                                 // エッジ

      motionList.push_back(dl);          // 動作リストに追加
    } else if(command == COMMAND::CL) {  // 指定色ライントレース動作の生成
      ColorLineTracing* cl = new ColorLineTracing(
          ColorJudge::stringToColor(params[1]),                        // 目標色
          targetBrightness + atoi(params[2]),                          // 目標輝度 + 調整
          atoi(params[3]),                                             // PWM値
          PidGain(atof(params[4]), atof(params[5]), atof(params[6])),  // PIDゲイン
          isLeftEdge);                                                 // エッジ

      motionList.push_back(cl);          // 動作リストに追加
    } else if(command == COMMAND::DS) {  // 指定距離直進動作の生成
      DistanceStraight* ds = new DistanceStraight(atof(params[1]),   // 目標距離
                                                  atoi(params[2]));  // PWM値

      motionList.push_back(ds);          // 動作リストに追加
    } else if(command == COMMAND::CS) {  // 指定色直進動作の生成
      ColorStraight* cs = new ColorStraight(ColorJudge::stringToColor(params[1]),  // 目標色
                                            atoi(params[2]));                      // PWM値

      motionList.push_back(cs);                                        // 動作リストに追加
    } else if(command == COMMAND::RT) {                                // 回頭動作の生成
      Rotation* rt = new Rotation(atoi(params[1]),                     // 回転角度
                                  atoi(params[2]),                     // PWM値
                                  convertBool(params[0], params[3]));  // 回頭方向

      motionList.push_back(rt);          // 動作リストに追加
    } else if(command == COMMAND::DT) {  // 距離指定旋回動作の生成
      DistanceTurning* dt = new DistanceTurning(atof(params[1]),   // 目標距離
                                                atoi(params[2]),   // 左モータのPWM値
                                                atoi(params[3]));  // 右モータのPWM値

      motionList.push_back(dt);                        // 動作リストに追加
    } else if(command == COMMAND::EC) {                // エッジ切り替えの生成
      EdgeChanging* ec = new EdgeChanging(isLeftEdge,  // エッジ
                                          convertBool(params[0], params[1]));  // 切り替え後のエッジ

      motionList.push_back(ec);          // 動作リストに追加
    } else if(command == COMMAND::SL) {  // 自タスクスリープの生成
      Sleeping* sl = new Sleeping(atoi(params[1]));

      motionList.push_back(sl);          // 動作リストに追加
    } else if(command == COMMAND::AR) {  // アームを上げる
      ArmRising* ar = new ArmRising(atoi(params[1]), atoi(params[2]));

      motionList.push_back(ar);          // 動作リストに追加
    } else if(command == COMMAND::AF) {  // アームを下げる
      ArmFalling* af = new ArmFalling(atoi(params[1]), atoi(params[2]));

      motionList.push_back(af);  // 動作リストに追加
    } else {                     // 未定義のコマンドの場合
      snprintf(buf, BUF_SIZE, "%s:%d: '%s' is undefined command", filePath, lineNum, params[0]);
      logger.logWarning(buf);
    }
    lineNum++;  // 行番号をインクリメントする
  }

  // ファイルを閉じる
  fclose(fp);

  return motionList;
}

COMMAND MotionParser::convertCommand(char* str)
{
  if(strcmp(str, "DL") == 0) {  // 文字列がDLの場合
    return COMMAND::DL;
  } else if(strcmp(str, "CL") == 0) {  // 文字列がCLの場合
    return COMMAND::CL;
  } else if(strcmp(str, "DS") == 0) {  // 文字列がDSの場合
    return COMMAND::DS;
  } else if(strcmp(str, "CS") == 0) {  // 文字列がCSの場合
    return COMMAND::CS;
  } else if(strcmp(str, "RT") == 0) {  // 文字列がRTの場合
    return COMMAND::RT;
  } else if(strcmp(str, "DT") == 0) {  // 文字列がDTの場合
    return COMMAND::DT;
  } else if(strcmp(str, "EC") == 0) {  // 文字列がECの場合
    return COMMAND::EC;
  } else if(strcmp(str, "SL") == 0) {  // 文字列がSLの場合
    return COMMAND::SL;
  } else if(strcmp(str, "AR") == 0) {  // 文字列がARの場合
    return COMMAND::AR;
  } else if(strcmp(str, "AF") == 0) {  // 文字列がAFの場合
    return COMMAND::AF;
  } else {  //想定していない文字列が来た場合
    return COMMAND::NONE;
  }
}

bool MotionParser::convertBool(char* command, char* binaryParameter)
{
  Logger logger;

  if(strcmp(command, "RT") == 0) {                   //  コマンドがRTの場合
    if(strcmp(binaryParameter, "clockwise") == 0) {  // パラメータがclockwiseの場合
      return true;
    } else if(strcmp(binaryParameter, "unclockwise") == 0) {  // パラメータがunclockwiseの場合
      return false;
    } else {  //想定していないパラメータが来た場合
      logger.logWarning("Parameter before conversion must be 'clockwise' or 'unclockwise'");
      return true;
    }
  }

  if(strcmp(command, "EC") == 0) {              //  コマンドがECの場合
    if(strcmp(binaryParameter, "left") == 0) {  // パラメータがleftの場合
      return true;
    } else if(strcmp(binaryParameter, "right") == 0) {  // パラメータがrightの場合
      return false;
    } else {  //想定していないパラメータが来た場合
      logger.logWarning("Parameter before conversion must be 'left' or 'right'");
      return true;
    }
  }
}
