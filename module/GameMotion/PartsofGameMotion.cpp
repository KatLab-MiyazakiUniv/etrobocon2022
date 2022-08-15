/**
 * @file Rotation.cpp
 * @brief 回頭・ピボットターンする
 * @author sugaken0528 KakinokiKanta
 */

#include "PartsofGameMotion.h"

using namespace std;

PartsofGameMotion::PartsofGameMotion()
  : isLeftEdge(true), targetBrightness(48), lineTracer(isLeftEdge)
{
}

void PartsofGameMotion::mp2ip(bool& isLeftEdge, int targetBrightness)
{
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, 60, PidGain(0.1, 0.08, 0.08));
}

void PartsofGameMotion::mp2b()
{
  straightRunner.run(120, 70);
}

void PartsofGameMotion::mp2mp()
{
  straightRunner.run(30, 70);
  straightRunner.runToColor(COLOR::BLACK, 70);
}

void PartsofGameMotion::b2ip()
{
  straightRunner.runToColor(COLOR::YELLOW, 70);
  straightRunner.run(42, 60);
}

void PartsofGameMotion::b2mp()
{
  straightRunner.runToColor(COLOR::BLACK, 70);
  straightRunner.run(20, 70);
}

void PartsofGameMotion::ip2mp(bool& isLeftEdge, int targetBrightness)
{
  straightRunner.run(15, 70);
  lineTracer.run(80, targetBrightness, 60, PidGain(0.1, 0.08, 0.08));
}

void PartsofGameMotion::ip2b()
{
  straightRunner.run(150, 70);
}

void PartsofGameMotion::reverse_action(bool& isLeftEdge, int targetBrightness)
{
  straightRunner.run(70, -40);
  lineTracer.runToColor(COLOR::GREEN, targetBrightness, -40, PidGain(0.1, 0.08, 0.08));
  straightRunner.run(15, 40);
}

void PartsofGameMotion::Vadjustment()
{
  straightRunner.run(10, 70);
}

void PartsofGameMotion::Dadjustment()
{
  straightRunner.run(20, 70);
}