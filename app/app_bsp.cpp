#include "button.h"

#include "sys_dbg.h"

#include "app.h"
#include "app_bsp.h"
#include "app_dbg.h"
#include "app_if.h"

#include "task_list.h"
#include "task_list_if.h"
#include "timer.h"

button_t btn_mode;
button_t btn_up;
button_t btn_down;

void btn_mode_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED:
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_MODE_PRESSED);
			APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_PRESSED\n");
			//	timer_set(AC_TASK_LIFE_ID, AC_LIFE_SYSTEM_CHECK, AC_LIFE_TASK_TIMER_LED_LIFE_INTERVAL, TIMER_PERIODIC);
			//task_post_pure_msg(AC_TASK_TETRIS_ID, AC_TETRIS_ROTATE);
			break;

		case BUTTON_SW_STATE_LONG_PRESSED:
			APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
			break;

		case BUTTON_SW_STATE_RELEASED:
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_MODE_RELEASED);
			APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_RELEASED\n");
			//task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_ON_LOGO);

			break;

		default:
			break;
	}
}

void btn_up_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED: {
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_LEFT_PRESSED);
			APP_DBG("[btn_up_callback] BUTTON_SW_STATE_PRESSED\n");
		}
			break;

		case BUTTON_SW_STATE_LONG_PRESSED: {
			APP_DBG("[btn_up_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
		}
			break;

		case BUTTON_SW_STATE_RELEASED: {
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_LEFT_RELEASED);
			APP_DBG("[btn_up_callback] BUTTON_SW_STATE_RELEASED\n");
		}
			break;

		default:
			break;
	}
}

void btn_down_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
		case BUTTON_SW_STATE_PRESSED: {
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_RIGHT_PRESSED);
			APP_DBG("[btn_down_callback] BUTTON_SW_STATE_PRESSED\n");
		}
			break;

		case BUTTON_SW_STATE_LONG_PRESSED: {
			APP_DBG("[btn_down_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
		}
			break;

		case BUTTON_SW_STATE_RELEASED: {
			task_post_pure_msg(TETRIS_TASK_SM_ID, INPUT_SM_BUTTON_RIGHT_RELEASED);
			APP_DBG("[btn_down_callback] BUTTON_SW_STATE_RELEASED\n");
		}
			break;

		default:
			break;
	}
}
