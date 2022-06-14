/**
 * @file app.h
 * @brief タスクを管理するクラス
 * @author sakakibara
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "ev3api.h"

#define MAIN_PRIORITY TMIN_APP_TPRI + 1

#ifndef STACK_SIZE
#define STACK_SIZE 4096
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY
    extern void main_task(intptr_t exinf); // メインタスク
#endif                                     /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
