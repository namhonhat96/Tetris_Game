#include "task_Tetris_GC.h"

Adafruit_ssd1306syp obj_drawing;

void draw_init(){
	obj_drawing.initialize();
	obj_drawing.display_off();
	obj_drawing.display_on();
}

void draw(){
	obj_drawing.clear(0);
	for(int row = 0 ; row < 3; row++){
		for(int col = 0; col < 3; col++){
			obj_drawing.drawRect(row, col,2, 2, WHITE );
		}
	}
	obj_drawing.update();
}

