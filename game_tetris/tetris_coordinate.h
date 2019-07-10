#ifndef __TETRIS_COORDINATE_H__
#define __TETRIS_COORDINATE_H__

#include <stdint.h>

typedef struct
{
	int16_t Row;
	int16_t Column;
} Coordinate_t;

#define TETRIS_BOUNDARY_COLUMN	38
#define TETRIS_NEXTBOX_COLUMN	96
#define TETRIS_NEXTBOX_ROW		16
uint8_t tetris_coordinate_to_position(Coordinate_t Source, Coordinate_t *Dest);

#endif // __TETRIS_COORDINATE_H__
