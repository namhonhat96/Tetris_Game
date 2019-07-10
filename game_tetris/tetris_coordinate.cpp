#include "tetris_coordinate.h"

uint8_t tetris_coordinate_to_position(Coordinate_t Source, Coordinate_t *Dest)
{
	if(Source.Row < 0 || Source.Column < 0)
		return -1;
	Dest->Column = TETRIS_BOUNDARY_COLUMN + 3 + 4*Source.Column;
	Dest->Row = 58 - 4*Source.Row;

	return 0;
}
