/**
 * @file etroboc_ext.cpp
 * @brief EV3拡張API（ダミー）
 * @author KakinokiKanta
 */

#include "etroboc_ext.h"

bool isLeft = true;

int ETRoboc_getCourseInfo(ETROBOC_COURSE_INFO_ID id)
{
    if (id == ETROBOC_COURSE_INFO_BLOCK_POS_BLACK1)
    {
        return 48;
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_RED1)
    {
        return (isLeft ? 69 : 72);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_RED2)
    {
        return (isLeft ? 77 : 74);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW1)
    {
        return (isLeft ? 66 : 67);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_YELLOW2)
    {
        return (isLeft ? 75 : 76);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_BLUE1)
    {
        return (isLeft ? 68 : 65);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_BLUE2)
    {
        return (isLeft ? 82 : 81);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_GREEN1)
    {
        return (isLeft ? 71 : 70);
    }
    else if (id == ETROBOC_COURSE_INFO_BLOCK_POS_GREEN2)
    {
        return (isLeft ? 80 : 83);
    }
    else
    {
        return -1;
    }
}

void setIsLeft(bool _isLeft)
{
    isLeft = _isLeft;
}