/**
 * @file ColorJudge.cpp
 * @brief 色識別クラス
 * @author mutotaka0426
 */

#include "ColorJudge.h"

// RGBから色を判別する
COLOR ColorJudge::getColor(rgb_raw_t const& _rgb)
{
  rgb_raw_t rgb;
  Hsv hsv;
  int min;

  // 環境光による値の偏りを軽減する
  // 事前に測った白が(255,255,255)となるように、RGB値を正規化する
  rgb.r = (_rgb.r < MAX_RGB.r) ? std::max((_rgb.r - MIN_RGB.r), 0) * 255 / (MAX_RGB.r - MIN_RGB.r)
                               : 255;
  rgb.g = (_rgb.g < MAX_RGB.g) ? std::max((_rgb.g - MIN_RGB.g), 0) * 255 / (MAX_RGB.g - MIN_RGB.g)
                               : 255;
  rgb.b = (_rgb.b < MAX_RGB.b) ? std::max((_rgb.b - MIN_RGB.b), 0) * 255 / (MAX_RGB.b - MIN_RGB.b)
                               : 255;

  // HSV値に変換
  hsv = convertRgbToHsv(rgb);

  // RGBの中の最小値を取得
  min = std::min({ rgb.r, rgb.g, rgb.b });

  // 明度が極端に低ければ、黒を返す
  if(hsv.value < BLACK_LIMIT_BORDER) return COLOR::BLACK;
  // 明度が極端に高ければ、白を返す
  if(min > WHITE_LIMIT_BORDER) return COLOR::WHITE;
  // 彩度が低い場合
  if(hsv.saturation < SATURATION_BORDER) {
    // 明度が低ければ、黒を返す
    if(hsv.value < BLACK_BORDER) return COLOR::BLACK;
    // 明度が高ければ、白を返す
    return COLOR::WHITE;
  }

  // 各色相の境界によって、色を判別する
  if(hsv.hue < RED_BORDER) return COLOR::RED;
  if(hsv.hue < YELLOW_BORDER) return COLOR::YELLOW;
  if(hsv.hue < GREEN_BORDER) return COLOR::GREEN;
  if(hsv.hue < BLUE_BORDER) return COLOR::BLUE;
  return COLOR::RED;
}

// RGBをHSVに変換する
// 参考: https://tomari.org/main/java/color/ccal.html
Hsv ColorJudge::convertRgbToHsv(rgb_raw_t const& _rgb)
{
  Hsv hsv{ 0, 0, 0 };

  // RGBの中の最大・最小値を求める
  int max = std::max({ _rgb.r, _rgb.g, _rgb.b });
  int min = std::min({ _rgb.r, _rgb.g, _rgb.b });

  // maxが0の場合、黒を返す
  if(max == 0) {
    return hsv;
  }

  // 色相
  if(max == min) {
    hsv.hue = 0;
  } else if(_rgb.r == max) {
    hsv.hue = 60 * (_rgb.g - _rgb.b) / (max - min);
  } else if(_rgb.g == max) {
    hsv.hue = 60 * (_rgb.b - _rgb.r) / (max - min) + 120;
  } else if(_rgb.b == max) {
    hsv.hue = 60 * (_rgb.r - _rgb.g) / (max - min) + 240;
  }
  // マイナスの場合の補完
  hsv.hue = (hsv.hue + 360) % 360;

  // 彩度
  hsv.saturation = 100 * (max - min) / max;

  // 明度
  hsv.value = max;

  return hsv;
}
