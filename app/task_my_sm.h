#ifndef __TASK_MY_SM_H__
#define __TASK_MY_SM_H__

#include "task_sm_tetris.h"

extern void task_sm_init(ak_msg_t*);
extern void task_sm_ready(ak_msg_t*);
extern void task_sm_tetris_playing(ak_msg_t*);
extern void task_sm_tetris_gameover(ak_msg_t*);

extern uint32_t Time_Down;
extern uint32_t Time_On;
extern uint32_t Time_Out;

extern pf_task task_sm_pointer;

#endif //__TASK_MY_SM_H__
