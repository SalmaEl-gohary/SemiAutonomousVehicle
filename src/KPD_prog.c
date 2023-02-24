/*
 * KPD_prog.c
 *
 *  Created on: Nov 26, 2022
 *      Author: salma
 */
#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"
#include "KPD_config.h"
#include "KPD_int.h"
#include "MGPIO_int.h"
#include "MSTK_int.h"
#include "LCD_config.h"


static const u8 au8Array[4][4] =
{
		{'+', '=', '0', 'f'},
		{'/', '9', '8', '7'},
		{'X', '6', '5', '4'},
		{'-', '3', '2', '1'}

};

u8 KPD_u8GetKeypress(void)
{
	u8 u8SwVal = NOT_PRESSED;
	u8 u8Col;
	u8 u8Row;

	for (u8Col = 4; u8Col < 8; u8Col++)
	{
		MGPIO_vidSetPinValue(KDP_PORT, u8Col, MGPIO_PIN_LOW);

		for (u8Row = 8; u8Row < 12; u8Row++)
		{
			if (MGPIO_u8GetPinValue(KDP_PORT, u8Row) == MGPIO_PIN_LOW)
			{
				u8SwVal = au8Array[u8Row - 8][u8Col - 4];
				//debounce
				MSTK_voidDelayMs(20);
				while(MGPIO_u8GetPinValue(KDP_PORT, u8Row) == MGPIO_PIN_LOW);
			}
		}
		MGPIO_vidSetPinValue(KDP_PORT, u8Col, MGPIO_PIN_HIGH);

	}
	return u8SwVal;
}


