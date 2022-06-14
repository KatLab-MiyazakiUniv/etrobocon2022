/**
 * @file etroboc_ext.h.h
 * @brief EV3拡張API（ダミー）
 * @author sakakibara
 */

#ifndef ETROBOC_EXT_H
#define ETROBOC_EXT_H
inline static void ETRoboc_notifyCompletedToSimulator(void) {}
void setIsLeft(bool _isLeft);

//コース情報取得関数用ID定義
enum ETROBOC_COURSE_INFO_ID
{
   ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1,
   ETROBOC_COURSE_INFO_BLOCK_POS_RED1,
   ETROBOC_COURSE_INFO_BLOCK_POS_RED2,
   ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW1,
   ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW2,
   ETROBOC_COURSE_INFO_BLOCK_POS_BLUE1,
   ETROBOC_COURSE_INFO_BLOCK_POS_BLUE2,
   ETROBOC_COURSE_INFO_BLOCK_POS_GREEN1,
   ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2
};

/**
 * コース情報の取得
 * @param id
 * @return 位置情報(ASCIIコード)
 */
int ETRoboc_getCourseInfo(ETROBOC_COURSE_INFO_ID id);
#endif
