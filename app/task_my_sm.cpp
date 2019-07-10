#include "fsm.h"
#include "port.h"
#include "message.h"

#include "app_bsp.h"
#include "task_my_sm.h"
#include "task_list.h"
#include "app.h"
#include "timer.h"

#include "my_debug.h"

uint32_t Time_Down = 100;
uint32_t Time_On = 1000;
uint32_t Time_Out = 5000;

pf_task task_sm_pointer = task_sm_init;

void task_sm(ak_msg_t *message)
{
	task_sm_pointer(message);
}

void task_sm_init(ak_msg_t * message)
{
	switch(message->sig)
	{
		case GAME_SM_INIT_REQ:
			debug_info("%10s: Init Required!\n", "[SM]");
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_INIT_REQ);
			break;
		case GAME_SM_INIT_RES_ERR:
			debug_info("%10s: Init Error!\n", "[SM]");
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_INIT_REQ);
			break;
		case GAME_SM_INIT_RES_OK:
			debug_info("%10s: Init Success!\n", "[SM]");
			task_sm_pointer = task_sm_ready;
			break;
		case INPUT_SM_BUTTON_MODE_RELEASED:
		case INPUT_SM_BUTTON_LEFT_RELEASED:
		case INPUT_SM_BUTTON_RIGHT_RELEASED:
			debug_info("%10s: Key Pressed!\n", "[SM]");
		default: break;
	}
}

void task_sm_ready(ak_msg_t *message)
{
	switch(message->sig)
	{
		case INPUT_SM_BUTTON_MODE_RELEASED:
		case INPUT_SM_BUTTON_LEFT_RELEASED:
		case INPUT_SM_BUTTON_RIGHT_RELEASED:
			debug_info("%10s: Ready State Required!\n", "[SM]");
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_START_GAME_REQ);
			break;
		case GAME_SM_START_GAME_RES_ERR:
			debug_info("%10s: Failed to change to Ready!\n","[SM]");
			task_post_pure_msg(TETRIS_TASK_GC_ID, TETRIS_GC_START_GAME_REQ);
			break;
		case GAME_SM_START_GAME_RES_OK:
			debug_info("[SM]: Successfully to Ready!\n");
			task_sm_pointer = task_sm_tetris_playing;
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_ON_TIME, Time_On, TIMER_ONE_SHOT);
			timer_set(TETRIS_TASK_SM_ID, GAME_SM_CONTROL_TIME_OUT, Time_Out, TIMER_ONE_SHOT);
			break;
	}
}
