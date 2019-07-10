#include "task_my_ui.h"
#include "task_my_gc.h"
#include "message.h"
#include "app_bsp.h"

#include "task_list.h"
#include "app.h"
#include "timer.h"
#include "tetris_coordinate.h"
#include "tetris_struct.h"
#include "xprintf.h"
Adafruit_ssd1306syp Unchanged_Drawing_Obj;
Adafruit_ssd1306syp Moving_Drawing_Obj;

Coordinate_t Moving_Drawing_Obj_Position;

static void screen_init_display();
static void screen_start_display();
static void screen_update();
static void screen_game_over();

Block_Shape_t NextShape[3];
void task_tetris_ui(ak_msg_t *message)
{
	switch(message->sig)
	{
		case TETRIS_UI_INIT_REQ:
			screen_init_display();
			task_post_pure_msg(TETRIS_TASK_SM_ID, GAME_SM_INIT_RES_OK);
			break;
		case TETRIS_UI_GAME_START:
			screen_start_display();
			NextShape[0] = (Block_Shape_t)(rand()%7);
			NextShape[1] = (Block_Shape_t)(rand()%7);
			NextShape[2] = (Block_Shape_t)(rand()%7);
			break;
		case TETRIS_UI_UPDATE:
			screen_update();
			break;
		case TETRIS_UI_GAME_OVER:
			screen_game_over();
			break;
	}
}

void screen_init_display()
{
	xprintf("Screen initialized\n");
	Unchanged_Drawing_Obj.initialize();
	Unchanged_Drawing_Obj.display_off();
	Unchanged_Drawing_Obj.display_on();
	Unchanged_Drawing_Obj.setTextSize(2);
	Unchanged_Drawing_Obj.setTextColor(WHITE);
	Unchanged_Drawing_Obj.setCursor(10, 25);
	Unchanged_Drawing_Obj.println("Press any button!");
	Unchanged_Drawing_Obj.update();

	Moving_Drawing_Obj.initialize();
	Moving_Drawing_Obj.display_off();
	Moving_Drawing_Obj.display_on();
}

void screen_start_display()
{
	Unchanged_Drawing_Obj.clear(0);
	Moving_Drawing_Obj.clear(0);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN, 0, TETRIS_BOUNDARY_COLUMN, 62, WHITE);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN, 62, TETRIS_BOUNDARY_COLUMN + 44, 62, WHITE);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN + 44, 62, TETRIS_BOUNDARY_COLUMN + 44, 0, WHITE);

	Unchanged_Drawing_Obj.setTextSize(1);
	Unchanged_Drawing_Obj.setTextColor(WHITE);
	Unchanged_Drawing_Obj.setCursor(0, 10);
	Unchanged_Drawing_Obj.print("Score");
	Unchanged_Drawing_Obj.update();

	tetris_coordinate_to_position(Obj, &Moving_Drawing_Obj_Position);
	Moving_Drawing_Obj.fillRect(Moving_Drawing_Obj_Position.Column, Moving_Drawing_Obj_Position.Row, 3, 3, WHITE);
	Moving_Drawing_Obj.update();
}

void screen_update()
{
	//Moving_Drawing_Obj.clear(0);
	//Unchanged_Drawing_Obj.update();
	//Unchanged_Drawing_Obj.clear(0);
	Moving_Drawing_Obj.clear(0);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN, 0, TETRIS_BOUNDARY_COLUMN, 62, WHITE);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN, 62, TETRIS_BOUNDARY_COLUMN + 44, 62, WHITE);
	Unchanged_Drawing_Obj.drawLine(TETRIS_BOUNDARY_COLUMN + 44, 62, TETRIS_BOUNDARY_COLUMN + 44, 0, WHITE);

	Unchanged_Drawing_Obj.setTextSize(1);
	Unchanged_Drawing_Obj.setTextColor(WHITE);
	Unchanged_Drawing_Obj.setCursor(0, 10);
	Unchanged_Drawing_Obj.print("Score");
	Unchanged_Drawing_Obj.setCursor(0, 22);
	Unchanged_Drawing_Obj.print((unsigned int)100);

	Unchanged_Drawing_Obj.setCursor(100, 5);
	Unchanged_Drawing_Obj.print("Next");

	Unchanged_Drawing_Obj.drawRect(TETRIS_NEXTBOX_COLUMN, TETRIS_NEXTBOX_ROW, 29, 39, WHITE);
	for(int i = 0; i<3; i++)
	{
		switch(NextShape[i])
		{
			case Block_Bar:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  2, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 14, TETRIS_NEXTBOX_ROW + 5 + 11*i + 2, 3, 3, WHITE);
			}
				break;
			case Block_Square:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  6, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 10, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
			case Block_L:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
			case Block_L_mirror:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
			case Block_Z:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
			case Block_Z_mirror:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
			case Block_T:
			{
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 0, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  4, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 +  8, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
				Unchanged_Drawing_Obj.fillRect(TETRIS_NEXTBOX_COLUMN + 5 + 12, TETRIS_NEXTBOX_ROW + 5 + 11*i + 4, 3, 3, WHITE);
			}
				break;
		}
	}
	tetris_coordinate_to_position(Obj, &Moving_Drawing_Obj_Position);
	Moving_Drawing_Obj.fillRect(Moving_Drawing_Obj_Position.Column, Moving_Drawing_Obj_Position.Row, 3, 3, WHITE);
	Moving_Drawing_Obj.update();
	Unchanged_Drawing_Obj.update();
}

void screen_game_over()
{
	Unchanged_Drawing_Obj.clear(0);
	Moving_Drawing_Obj.clear(0);
	Unchanged_Drawing_Obj.setTextSize(2);
	Unchanged_Drawing_Obj.setTextColor(WHITE);
	Unchanged_Drawing_Obj.setCursor(10, 25);
	Unchanged_Drawing_Obj.println("GAME OVER");
	Unchanged_Drawing_Obj.update();
}
