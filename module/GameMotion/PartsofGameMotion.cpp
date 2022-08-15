/**
 * @file PartsofGameMotion.cpp
 * @brief ゲームエリア内動作パラメータ調整用の仮コード
 * @author sap2368
 */

#include "PartsofGameMotion.h"

using namespace std;

PartsofGameMotion::PartsofGameMotion()
  : isLeftEdge(true), targetBrightness(48), lineTracer(isLeftEdge)
{
}

void PartsofGameMotion::mp2ip(bool& isLeftEdge, int targetBrightness)
{
  //中点から指定した色のノードまでライントレース
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 60, PidGain(0.1, 0.08, 0.08));
}

void PartsofGameMotion::mp2b()
{
  //中点からブロックの位置まで直進
  straightRunner.run(120, 70);
}

void PartsofGameMotion::mp2mp()
{
  //連続で使用する場合を考え黒線を認識しないように直進
  straightRunner.run(30, 70);

  //中点(黒線)から中点(黒線)まで直進
  straightRunner.runToColor(COLOR::BLACK, 70);
}

void PartsofGameMotion::b2ip()
{
  //ブロックの位置から指定した色の交点まで直進
  straightRunner.runToColor(COLOR::YELLOW, 70);

  //黒線の交点がタイヤの中心に来るよう調整
  straightRunner.run(42, 60);
}

void PartsofGameMotion::b2mp()
{
  //ブロックの位置から中点(黒線)まで直進
  straightRunner.runToColor(COLOR::BLACK, 70);

  //手前で止まってしまうため黒線にタイヤの中心が来るように調整
  straightRunner.run(20, 70);
}

void PartsofGameMotion::ip2mp(bool& isLeftEdge, int targetBrightness)
{
  //ノードの色を認識してしまう場合があるため直進
  straightRunner.run(15, 70);

  //中点までライントレース
  lineTracer.run(80, targetBrightness, 60, PidGain(0.1, 0.08, 0.08));
}

void PartsofGameMotion::ip2b()
{
  //交点からブロックの位置まで直進
  straightRunner.run(150, 70);
}

void PartsofGameMotion::reverse_action(bool& isLeftEdge, int targetBrightness)
{
  //今いる黒線を認識するために直進(後退)
  straightRunner.run(70, -40);

  //今いるノードの真後ろのノードまで後退(ライントレース)
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, -40, PidGain(0.1, 0.08, 0.08));

  //色を認識した段階では行き過ぎてしまうため黒線の交点がタイヤの中心になるよう調整
  straightRunner.run(15, 40);
}

void PartsofGameMotion::Vadjustment()
{
  //黒線の横幅分直進
  straightRunner.run(10, 70);
}

void PartsofGameMotion::Dadjustment()
{
  //黒線を45°で横切る場合の調整
  straightRunner.run(20, 70);
}