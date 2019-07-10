#ifndef __TETRIS_STRUCT_H__
#define __TETRIS_STRUCT_H__

#include "tetris_gameconfig.h"
#include "Adafruit_ssd1306syp.h"
#include "tetris_coordinate.h"

#include "message.h"
#include "task.h"

typedef int(*TetrisFunction_t)(void);
typedef void(*GameFunction_t)(void);
typedef uint32_t	TetrisRow_t;

typedef enum
{
	Block_Bar = 0,
	Block_Square,
	Block_L,
	Block_L_mirror,
	Block_Z,
	Block_Z_mirror,
	Block_T
} Block_Shape_t;

typedef struct
{
	TetrisFunction_t	Init;
	TetrisFunction_t	DeInit;
	TetrisFunction_t	Generate;
	TetrisFunction_t	MoveLeft;
	TetrisFunction_t	MoveRight;
	TetrisFunction_t	MoveDown;
	TetrisFunction_t	Rotate;
	TetrisFunction_t	Check;
	TetrisFunction_t	CheckAbleMove;
	TetrisFunction_t	CalculateDropPlace;

	GameFunction_t		GraphicInit;
	GameFunction_t		GraphicDeInit;
	GameFunction_t		GraphicClear;
	GameFunction_t		GraphicUpdate;
	GameFunction_t		GraphicShow;

	Adafruit_ssd1306syp	GraphicObj;

	Block_Shape_t		NextShape[3];
	Coordinate_t		Block[4];
	Coordinate_t		DropPoint[4];

	bool				able_moveLeft;
	bool				able_moveRight;
	bool				able_moveDown;
} MovingObject_t;

typedef struct
{
	TetrisFunction_t	Init;
	TetrisFunction_t	DeInit;
	TetrisFunction_t	Update;

	GameFunction_t		GraphicInit;
	GameFunction_t		GraphicDeInit;
	GameFunction_t		GraphicClear;
	GameFunction_t		GraphicUpdate;
	GameFunction_t		GraphicShow;

	bool(*is_Existed)(Coordinate_t);


	Adafruit_ssd1306syp	GraphicObj;
	TetrisRow_t			Row[TETRIS_ROW_NUMBER+4];	// 4 Virtual Row!!
} StandingObject_t;

typedef struct
{
	pf_task			Task_SM_Playing;
	pf_task			Task_SM_Game_Over;
	pf_task			Task_GC;
	pf_task			Task_UI;

	GameFunction_t	Init;
	GameFunction_t	DeInit;
	GameFunction_t	Button_Up;
	GameFunction_t	Button_Down;
	GameFunction_t	Button_Left;
	GameFunction_t	Button_Right;

	GameFunction_t	GraphicInit;
	GameFunction_t	GraphicClear;
	GameFunction_t	GraphicUpdate;
	GameFunction_t	GraphicShow;
} GameHandler_t;

extern uint16_t Score;

#endif // __TETRIS_STRUCT_H__
