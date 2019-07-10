#include "Tetris_StandingObject.h"
#include "Tetris_MovingObject.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ssd1306syp.h"
#include <string.h>

static bool isFilled(TetrisRow_t Row);
static bool StandingObject_isExisted(Coordinate_t Coordinate);
static int StandingObject_Init();
static int StandingObject_DeInit();
static int StandingObject_Update();
static void StandingObject_GraphicInit();
static void StandingObject_GraphicDeInit();
static void StandingObject_GraphicClear();
static void StandingObject_GraphicUpdate();
static void StandingObject_GraphicShow();

bool isFilled(TetrisRow_t Row)
{
	return(Row == TETRIS_ROW_FILLED_FLAG);
}

StandingObject_t StandingObject =
{
	StandingObject_Init,
	StandingObject_DeInit,
	StandingObject_Update,

	StandingObject_GraphicInit,
	StandingObject_GraphicDeInit,
	StandingObject_GraphicClear,
	StandingObject_GraphicUpdate,
	StandingObject_GraphicShow,

	StandingObject_isExisted,

};

int StandingObject_Init()
{
	memset(StandingObject.Row, 0, sizeof(TetrisRow_t)*(TETRIS_ROW_NUMBER+4));
	return 0;
}

int StandingObject_DeInit()
{
	return 0;
}

int StandingObject_Update()
{
	for(int i = 0; i < 4; i++)
	{
		StandingObject.Row[MovingObject.Block[i].Row] |= 1<<((uint16_t)MovingObject.Block[i].Column);
	}

	for(int i = 0; i < TETRIS_ROW_NUMBER; i++)
	{
		if(isFilled(StandingObject.Row[i]))
		{
			Score+=20;
			for(int j = i; j < TETRIS_ROW_NUMBER + 4 - 1; j++)
			{
				StandingObject.Row[j] = StandingObject.Row[j+1];
			}
			StandingObject.Row[TETRIS_ROW_NUMBER + 3] = 0;
			i--;
		}
	}

	if(StandingObject.Row[TETRIS_ROW_NUMBER] != 0x0000)
	{
		return 1;	//Game Over!!
	}
	else
	{
		return 0;
	}
}

void StandingObject_GraphicInit()
{
	StandingObject.GraphicObj.initialize();
	StandingObject.GraphicObj.display_off();
	StandingObject.GraphicObj.display_on();
}

void StandingObject_GraphicDeInit()
{
	StandingObject.GraphicObj.clear(0);
	StandingObject.GraphicObj.display_off();
}

void StandingObject_GraphicClear()
{
	StandingObject.GraphicObj.clear(0);
}

void StandingObject_GraphicUpdate()
{
	Coordinate_t _Temp, _TempStandingObj;
	for(int16_t row = 0; row<TETRIS_ROW_NUMBER; row++)
	{
		for(int16_t column = 0; column<TETRIS_COLUMN_NUMBER; column++)
		{
			if( (StandingObject.Row[row] & (1<<(uint16_t)column) )!= 0x00)
			{
				_TempStandingObj.Row = row;
				_TempStandingObj.Column = column;
				tetris_coordinate_to_position(_TempStandingObj, &_Temp);
				StandingObject.GraphicObj.fillRect(_Temp.Column, _Temp.Row, 3, 3, WHITE);
			}
		}
	}
}

void StandingObject_GraphicShow()
{
	StandingObject.GraphicObj.update();
}

bool StandingObject_isExisted(Coordinate_t Coordinate)
{
	TetrisRow_t Temp = 1<<((uint16_t)Coordinate.Column);
	if( (StandingObject.Row[Coordinate.Row] & Temp) != 0x00)
	{
		return true;
	}
	else
	{
		return false;
	}
}
