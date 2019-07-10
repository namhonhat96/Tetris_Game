#include "Tetris_GameHandler.h"
#include "app.h"



uint16_t Score = 0;

GameHandler_t	Tetris_GameFunction =
{
		//	GameTask_t		TaskHandler;

		//	GameFunction_t	Init;
		//	GameFunction_t	Button_Up;
		//	GameFunction_t	Button_Down;
		//	GameFunction_t	Button_Left;
		//	GameFunction_t	Button_Right;

		//	GameFunction_t	GraphicInit;
		//	GameFunction_t	GraphicClear;
		//	GameFunction_t	GraphicUpdate;
		//	GameFunction_t	GraphicShow;
};

void Other_GraphicInit()
{
	OtherGraphicObj.initialize();
	OtherGraphicObj.display_off();
	OtherGraphicObj.display_on();
}

void Other_GraphicDeInit()
{
	OtherGraphicObj.clear(0);
	OtherGraphicObj.display_off();
}

void Other_GraphicClear()
{
	OtherGraphicObj.clear();
}

void Other_GraphicUpdate()
{
	OtherGraphicObj.drawLine(TETRIS_BOUNDARY_COLUMN, 0, TETRIS_BOUNDARY_COLUMN, 62, WHITE);
	OtherGraphicObj.drawLine(TETRIS_BOUNDARY_COLUMN, 62, TETRIS_BOUNDARY_COLUMN + 44, 62, WHITE);
	OtherGraphicObj.drawLine(TETRIS_BOUNDARY_COLUMN + 44, 62, TETRIS_BOUNDARY_COLUMN + 44, 0, WHITE);

	OtherGraphicObj.setTextSize(1);
	OtherGraphicObj.setTextColor(WHITE);
	OtherGraphicObj.setCursor(0, 10);
	OtherGraphicObj.print("Score");
	OtherGraphicObj.setCursor(0, 22);
	OtherGraphicObj.print((unsigned int)100);

	OtherGraphicObj.setCursor(100, 5);
	OtherGraphicObj.print("Next");

	OtherGraphicObj.drawRect(TETRIS_NEXTBOX_COLUMN, TETRIS_NEXTBOX_ROW, 29, 39, WHITE);
	for(int i = 0; i<3; i++)
	{
		switch(MovingObject.NextShape[i])
		{
			case Block_Bar:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  2, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 14, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
			}
			break;
			case Block_Square:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
			case Block_L:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
			case Block_L_mirror:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
			case Block_Z:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
			case Block_Z_mirror:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
			case Block_T:
			{
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				OtherGraphicObj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
			break;
		}
	}
}

void Other_GraphicShow()
{
	OtherGraphicObj.update();
}


void Tetris_Graphic_Init()
{
	MovingObject.GraphicInit();
	StandingObject.GraphicInit();
	Other_GraphicInit();
}

void Tetris_Graphic_DeInit()
{
	MovingObject.GraphicDeInit();
	StandingObject.GraphicDeInit();
	Other_GraphicDeInit();
}

void Tetris_Graphic_Update()
{
	// Clear all Objects
	MovingObject.GraphicClear();
	StandingObject.GraphicClear();
	Other_GraphicClear();

	// Update all Objects
	MovingObject.GraphicUpdate();
	StandingObject.GraphicUpdate();
	Other_GraphicUpdate();

	// Show all Objects
	MovingObject.GraphicShow();
	StandingObject.GraphicShow();
	Other_GraphicShow();
}

void Tetris_Graphic_GameOver()
{
	MovingObject.GraphicDeInit();
	StandingObject.GraphicDeInit();

	Other_GraphicClear();
	Other_GraphicUpdateGameOver();
	Other_GraphicShow();
}
