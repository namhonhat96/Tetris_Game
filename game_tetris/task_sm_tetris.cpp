#include "fsm.h"
#include "port.h"
#include "message.h"

#include "app_bsp.h"
#include "task_sm_tetris.h"
#include "task_my_sm.h"
#include "task_list.h"
#include "app.h"
#include "timer.h"

#include "my_debug.h"

void task_sm_tetris_playing(ak_msg_t *message)
{
	switch(message->sig)
	{
		case INPUT_SM_BUTTON_LEFT_PRESSED:
			if(btn_mode.state == BUTTON_SW_STATE_PRESSED)
			{
				timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME);
				timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
				task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_ROTATE);
			}
			else
			{
				timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME);
				timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
				task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_GO_LEFT);
			}
			break;
		case INPUT_SM_BUTTON_RIGHT_PRESSED:
			if(btn_down.state == BUTTON_SW_STATE_RELEASED)
				break;
			if(btn_mode.state == BUTTON_SW_STATE_PRESSED)
			{
				timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME);
				timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT);
				timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
				timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT, Time_Out, TIMER_ONE_SHOT);
				if(btn_mode.state == BUTTON_SW_STATE_PRESSED && btn_down.state == BUTTON_SW_STATE_PRESSED)
				{
					timer_set(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_RIGHT_PRESSED, Time_Down, TIMER_ONE_SHOT);
				}
				task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_GO_DOWN);
			}
			else
			{
				timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME);
				timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
				task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_GO_RIGHT);
			}
			break;
		case GAME_SM_CONTROL_ON_TIME:
			timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT);
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT, Time_Out, TIMER_ONE_SHOT);
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_GO_DOWN);
			break;
		case GAME_SM_CONTROL_TIME_OUT:
			timer_remove_attr(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME);
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT, Time_Out, TIMER_ONE_SHOT);
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_GO_DOWN);
			break;
		case GAME_SM_GAME_OVER:
			task_sm_pointer = task_sm_tetris_gameover;
			break;
	}
}

void task_sm_tetris_gameover(ak_msg_t *message)
{
	switch(message->sig)
	{
		case INPUT_SM_BUTTON_MODE_PRESSED:
		case INPUT_SM_BUTTON_LEFT_PRESSED:
		case INPUT_SM_BUTTON_RIGHT_PRESSED:
			task_sm_pointer = task_sm_ready;
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_INIT_REQ);
			break;
	}
}
