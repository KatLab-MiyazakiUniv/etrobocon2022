/**
 * @file GameArea.h
 * @brief ゲームエリアを攻略するクラス
 * @author kawano
 */

#include "BonusBlockCarrier.h"
#include "LineTracer.h"


class GameArea {
 public:
  static void runGameArea(const bool isLeftCourse, const int targetBrightness);

  private:
    GameArea();  // インスタンス化を禁止する
};

#endif