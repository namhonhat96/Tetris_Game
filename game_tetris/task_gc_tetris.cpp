#include "task_gc_tetris.h"
#include "app.h"
#include "task_list.h"

static void Tetris_Init();
static void Tetris_DeInit();
static void Tetris_Button_Up();
static void Tetris_Button_Down();
static void Tetris_Button_Left();
static void Tetris_Button_Right();

uint16_t Score;

void task_gc_tetris(ak_msg_t* message)
{
	switch(message->sig)
	{
		case TETRIS_GC_INIT_REQ:

			task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_INIT_REQ);
			break;
		case TETRIS_GC_START_GAME_REQ:
			Tetris_Init();
			task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_START);
			task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_START_GAME_RES_OK);
			break;
		case TETRIS_GC_GO_LEFT:
			Tetris_Button_Left();
			break;
		case TETRIS_GC_GO_RIGHT:
			Tetris_Button_Right();
			break;
		case TETRIS_GC_ROTATE:
			Tetris_Button_Up();
			break;
		case TETRIS_GC_GO_DOWN:
			Tetris_Button_Down();
			break;
	}
}

void Tetris_Init()
{
	MovingObject.Init();
	StandingObject.Init();
	Score = 0;
}

void Tetris_DeInit()
{
	MovingObject.DeInit();
	StandingObject.DeInit();
}

void Tetris_Button_Up()
{
	MovingObject.Rotate();
	task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
}

void Tetris_Button_Down()
{
	if(MovingObject.MoveDown() == 1)
	{
		if(StandingObject.Update() == 1)	//Game Over
		{
			Tetris_DeInit();
			task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_GAME_OVER);
			task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_GAME_OVER);
			return;
		}
		else
		{
			MovingObject.Generate();
		}
	}
	Score++;
	task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);

}

void Tetris_Button_Left()
{
	if(MovingObject.able_moveLeft)
	{
		MovingObject.MoveLeft();
		task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
	}
}

void Tetris_Button_Right()
{
	if(MovingObject.able_moveRight)
	{
		MovingObject.MoveRight();
		task_post_pure_msg(TETRIS_TASK_UI_ID, TETRIS_UI_UPDATE);
	}
}
