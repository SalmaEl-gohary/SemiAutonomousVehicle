/*
 * HULTRASONIC_prog.c
 *
 *  Created on: Feb 16, 2023
 *      Author: salma
 */
#include "LSTD_TYPES.h"
#include "TMR_int.h"


void APP_voidTrigPulses(void)
{
	//Set prescaler as to make each count equals 1us
	TMR_voidSetPrescaler(TMR2, 15);


	TMR_voidSetChannelOutput(TMR2, PWM_MODE1, CH2);

	//Set ovf at 500 ms
	TMR_voidSetARR(TMR2,  80000);

	TMR_voidSetCMPVal(TMR2, CH2, 20);

	TMR_voidClearCount(TMR2);

	TMR_voidStart(TMR2);

}

void APP_voidSetICU(void)
{
	//Enable ICU interrupt
	TMR_voidEnableICUInt(TMR3);

	//Set prescaler and choose channel 2 as input
	TMR_voidSetPrescaler(TMR3, 15);

	TMR_voidSetChannelInput(TMR3, CH1);

	//Start timer
	TMR_voidStart(TMR3);
}




