#include "game_flash.h"

unsigned int	Random_Number;
uint16_t		Tetris_HighScore[5];

Flash_Table_t Game_Flash_Table =
{
	APP_FLASH_GAMES,
	{
		{&Random_Number,		sizeof(unsigned int)	},
		{Tetris_HighScore,		sizeof(uint16_t)*5		},
		{(void*)0}
	}
};

void game_flash_init()
{
	if(Game_Flash_Table.Table[0].pVariable == 0)
		return;

	Game_Flash_Table.Table[0].pbuf = Game_Flash_Table.StartAddress;

	int i = 1;
	while(Game_Flash_Table.Table[i].pVariable != 0)
	{
		Game_Flash_Table.Table[i].pbuf = (uint8_t)(Game_Flash_Table.Table[i-1].pbuf + Game_Flash_Table.Table[0].size);
	}
}

void game_flash_read()
{
	int i = 1;
	while(Game_Flash_Table.Table[i].pVariable != 0)
	{
		flash_read(Game_Flash_Table.Table[i].pVariable, Game_Flash_Table.Table[i].pbuf, Game_Flash_Table.Table[i].size);
	}
}

void game_flash_write()
{
	int i = 1;
	while(Game_Flash_Table.Table[i].pVariable != 0)
	{
		flash_write(Game_Flash_Table.Table[i].pVariable, Game_Flash_Table.Table[i].pbuf, Game_Flash_Table.Table[i].size);
	}
}
