#ifndef GAME_FLASH_H
#define GAME_FLASH_H

#include "flash.h"
#include "app_flash.h"

typedef struct
{
	void		*pVariable;
	uint32_t	size;
	uint8_t		*pbuf;
} User_Flash_t;

typedef struct
{
	uint8_t			*StartAddress;
	User_Flash_t	*Table;
} Flash_Table_t;

#endif // GAME_FLASH_H
