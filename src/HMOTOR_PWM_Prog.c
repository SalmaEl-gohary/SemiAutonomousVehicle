/*
 * HMOTOR_PWM_Prog.c
 *
 *  Created on: Feb 13, 2023
 *      Author: abdelhamid
 */

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

#include "MRCC_Interface.h"
#include "MSTK_int.h"
#include "MGPIO_int.h"
#include "NVIC_int.h"
#include "TMR_int.h"

#include "HMOTOR_PWM_Config.h"
#include "HMOTOR_PWM_Iterface.h"
#include "HMOTOR_PWM_Priv.h"





void App_voidSpeedInit()
{

	TMR_voidSetPrescaler(TMR5, 15);

	TMR_voidSetARR(TMR5,  60000 - 1);

	TMR_voidSetChannelOutput(TMR5, PWM_MODE1,  CH1);
	TMR_voidSetChannelOutput(TMR5, PWM_MODE1,  CH2);

}


void App_voidAccelerationLoop(u32 * speedValue)
{
	while (*speedValue < MAX_PWM)
	{
		App_voidIncreaseSpeed(speedValue);
	//	MSTK_voidDelayMs(100);
	}
}

void App_voidDecelerationLoop(u32 * speedValue)
{

	while (*speedValue >= MIN_PWM)
	{
		App_voidDecreaseSpeed(speedValue);
	//	MSTK_voidDelayMs(100);
	}

}

void App_voidIncreaseSpeed(u32 * speedValue)
{

	if(*speedValue < MAX_PWM)
	{
		if (*speedValue == 0)
		{
			*speedValue = 8000;
		}
		else
		{
			*speedValue = (*speedValue) +  2000;
		}
	}

	TMR_voidSetCMPVal(TMR5, CH1, *speedValue );

	TMR_voidSetCMPVal(TMR5, CH2, (*speedValue));

	TMR_voidClearCount(TMR5);

	TMR_voidStart(TMR5);

}

void App_voidIncreaseSpeedSlow(u32 * speedValue)
{

	if(*speedValue < MAX_PWM)
	{
		if (*speedValue == 0)
		{
			*speedValue = 4000;
		}
		else
		{
			*speedValue = (*speedValue) +  500;
		}
	}

	TMR_voidSetCMPVal(TMR5, CH1, *speedValue );

	TMR_voidSetCMPVal(TMR5, CH2, (*speedValue));

	TMR_voidClearCount(TMR5);

	TMR_voidStart(TMR5);

}

void App_voidDecreaseSpeed(u32 * speedValue)
{
	if(*speedValue >= MIN_PWM)
	{
		if (*speedValue == MIN_PWM)
		{
			*speedValue = 0;
		}
		else
		{
			*speedValue = (*speedValue) -  2000;

		}
	}

	TMR_voidSetCMPVal(TMR5, CH1, *speedValue);

	TMR_voidSetCMPVal(TMR5, CH2, (*speedValue));

	TMR_voidClearCount(TMR5);

	TMR_voidStart(TMR5);

}

void App_voidDecreaseSpeedSlow(u32 * speedValue)
{
	if(*speedValue >= MIN_PWM)
	{
		if (*speedValue == MIN_PWM)
		{
			//*speedValue = 0;
			//APP_voidMotorStop(speedValue);
		}
		else
		{
			*speedValue = (*speedValue) -  1000;

	}
	}

	TMR_voidSetCMPVal(TMR5, CH1, *speedValue);

	TMR_voidSetCMPVal(TMR5, CH2, (*speedValue));

	TMR_voidClearCount(TMR5);

	TMR_voidStart(TMR5);

}

void APP_voidMotorForward(u32 * curSpeed, u8 * curDir)
{

	if (*curDir == 'B')
	{
		App_voidDecelerationLoop(curSpeed);
	}

	// RUN MOTOR1 FORWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_LOW);

	// RUN MOTOR2 FORWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_LOW);


	App_voidIncreaseSpeed(curSpeed);
	*curDir = 'F';

}

void APP_voidMotorBackward(u32 * curSpeed, u8 * curDir)
{

	if (*curDir == 'F')
	{
		App_voidDecelerationLoop(curSpeed);
	}

	// RUN MOTOR1 BACKWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_HIGH);

	// RUN MOTOR2 BACKWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_HIGH);


	App_voidIncreaseSpeed(curSpeed);
	*curDir = 'B';
}

void APP_voidMotorLeft(u8 * curDir)
{
	// RUN MOTOR1
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_LOW);

	// STOP MOTOR2
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_LOW);

	*curDir = 'L';
}

void APP_voidMotorRight(u8 * curDir)
{
	// STOP MOTOR1
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_LOW);

	// RUN MOTOR2
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_LOW);

	*curDir = 'R';

}

void APP_voidMotorStop(u32 * speed)
{
	// STOP MOTOR1
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_LOW);

	// STOP MOTOR2
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_LOW);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_LOW);

	*speed = 0;
}

void APP_voidMotorForwardDir(u32 * curSpeed, u8 * curDir)
{

	// RUN MOTOR1 FORWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR1_DIR2, MGPIO_PIN_LOW);

	// RUN MOTOR2 FORWARD DIR
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR1, MGPIO_PIN_HIGH);
	MGPIO_vidSetPinValue(MOTOR_PORT, MOTOR2_DIR2, MGPIO_PIN_LOW);


}



