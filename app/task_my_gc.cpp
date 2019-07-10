#include "task_my_gc.h"
#include "message.h"
#include "app_bsp.h"

#include "task_list.h"
#include "app.h"
#include "timer.h"

Coordinate_t Obj;
void task_tetris_gc(ak_msg_t *message)
{
	switch(message->sig)
	{
		case TETRIS_GC_INIT_REQ:

			task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_INIT_REQ);
			break;
		case TETRIS_GC_START_GAME_REQ:
			Obj.Column = 5;
			Obj.Row = 8;
			task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_START);
			task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_START_GAME_RES_OK);
			break;
		case TETRIS_GC_GO_LEFT:
			Obj.Column--;
			if(Obj.Column < 0)
			{
				task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_GAME_OVER);
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_OVER);
			}
			else
			{
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
			}
			break;
		case TETRIS_GC_GO_RIGHT:
			Obj.Column++;
			if(Obj.Column >= 10)
			{
				task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_GAME_OVER);
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_OVER);
			}
			else
			{
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
			}
			break;
		case TETRIS_GC_ROTATE:
			Obj.Row++;
			if(Obj.Row >= 15)
			{
				task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_GAME_OVER);
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_OVER);
			}
			else
			{
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
			}
			break;
		case TETRIS_GC_GO_DOWN:
			Obj.Row--;
			if(Obj.Row < 0)
			{
				task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_GAME_OVER);
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_OVER);
			}
			else
			{
				task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
			}
			break;
	}
}
