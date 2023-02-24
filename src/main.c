/*
 * main.c
 *
 *  Created on:
 *      Author: Salma Elgohary
 */

/***************************************************************************************/
/*                            Standard Types LIB                                       */
/***************************************************************************************/

#include <ALGORITHM_Config.h>
#include <HULTRASONIC_int.h>
#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"

/*GPIO REGIRTER DEFINITION*/



/***************************************************************************************/
/*                                     MCAL                                            */
/***************************************************************************************/
#include "MRCC_Interface.h"
#include "MSTK_int.h"
#include "MGPIO_int.h"
#include "NVIC_int.h"
#include "TMR_int.h"
#include "MEXTI_interface.h"
#include "UART_interface.h"
#include "MSPI_Interface.h"


/***************************************************************************************/
/*                                     HAL                                             */
/***************************************************************************************/
#include "HTFT_Interface.h"
#include "HMOTOR_PWM_Iterface.h"
#include "SYSTEM_int.h"
#include "KPD_int.h"

/***************************************************************************************/
/*                                     APP                                             */
/***************************************************************************************/
u8 distanceCount = 0;
u8 speedCount = 0;
u8 auth = 0;
u8 menu = 0;
u32 curSpeed = 0;
u32 setSpeed = 0;
u32 setDistance = 0;
u8 count = 0;
u32 curPWM = 4000;
u8 curDir;
u32 pulses2 = 0;
u32 pulses3 = 0;
u8 Mode = NORMAL_MODE;
u8  volatile state = 0;
u32 volatile rising_time, falling_time;
u32 volatile distance;
u8 speedArr[3], distanceArr[3];
u8  bluetoothData;


u8 distanceAvgCount = 0;


void EXTI2_ISR(void);
void EXTI3_ISR(void);
void APP_voidSetupSpeedTimer(void);


void main(void)
{

	// Initialize Clock
	MRCC_voidInitSystemClock();


	// Enable Peripherals
	MRCC_voidEnablePeripheralClock(AHB1,   MRCC_PERIPHERIAL_EN_GPIOA ) ;
	MRCC_voidEnablePeripheralClock(AHB1,   MRCC_PERIPHERIAL_EN_GPIOB ) ;
	MRCC_voidEnablePeripheralClock(APB1,   MRCC_PERIPHERAL_EN_SPI2   ) ;		//TFT
	MRCC_voidEnablePeripheralClock(APB1,   MRCC_PERIPHERAL_EN_TIM5   ) ;		//MOTOR PWM
	MRCC_voidEnablePeripheralClock(APB2,   MRCC_PERIPHERAL_EN_USART1   ) ;		//USART1 --> BLUETOOTH
	MRCC_voidEnablePeripheralClock(APB2,   MRCC_PERIPHERAL_EN_USART6   ) ;		//USART6 --> PI
	MRCC_voidEnablePeripheralClock(APB1,   MRCC_PERIPHERAL_EN_TIM2);			//ULTRASONIC --> ECHO
	MRCC_voidEnablePeripheralClock(APB1,   MRCC_PERIPHERAL_EN_TIM3);			//ULTRASONIC --> TRIG
	MRCC_voidEnablePeripheralClock(APB1,   MRCC_PERIPHERAL_EN_TIM4) ;			//SPEED TIMER



	/**********************************************INTERRUPTS*************************************************/
	// Enable Interrupts
	MNVIC_voidEnableInterrupt(TIM3_GLOBAL_INT);		//ULTRASONIC ECHO
	MNVIC_voidEnableInterrupt(EXTI2_GLOBAL_INT);    //ENCODER A
	MNVIC_voidEnableInterrupt(EXTI3_GLOBAL_INT);	//ENCODER B
	MNVIC_voidEnableInterrupt(USART6_GLOBAL_INT);	//USART 6 (PI)
	MNVIC_voidEnableInterrupt(TIM4_GLOBAL_INT);		//SPEED TIMER



	// Set Interrupt Priorities

	MNVIC_voidInitInterruptGroup(NVIC_GroupMode_g0s16);

	MNVIC_voidSetInterruptPriority(USART6_GLOBAL_INT, 	NVIC_GroupMode_g0s16,  0, 0);	//G0 S0
	MNVIC_voidSetInterruptPriority(TIM3_GLOBAL_INT,     NVIC_GroupMode_g0s16,  0, 1);	//G0 S1

	MNVIC_voidSetInterruptPriority(TIM4_GLOBAL_INT,     NVIC_GroupMode_g0s16,  0, 2);	//G1 S0
	MNVIC_voidSetInterruptPriority(EXTI2_GLOBAL_INT,    NVIC_GroupMode_g0s16,  0, 4);	//G1 S1
	MNVIC_voidSetInterruptPriority(EXTI3_GLOBAL_INT,    NVIC_GroupMode_g0s16,  0, 4);	//G1 S1


	/*********************************************************************************************************/


	/********************************************** TFT (SPI2) ***********************************************/
	//Set Pins as Output
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN12, MGPIO_PIN_OUTPUT);
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN14, MGPIO_PIN_OUTPUT);

	//Set Pins as Alternative for TFT
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN13, MGPIO_PIN_ALTFN);	//CLK2
	MGPIO_voidSetPinAltFn(MGPIOB_REG, PIN13, AF5);

	MGPIO_vidSetPinMode(MGPIOB_REG, PIN15, MGPIO_PIN_ALTFN);	//MOSI2
	MGPIO_voidSetPinAltFn(MGPIOB_REG, PIN15, AF5);

	//Initialize SPI
	MSPI2_voidInit() ;

	//Initialize TFT
	HTFT_voidInitialize();

	//Initialize
	TFT_VidFillColor(BLACK);
	/****************************************************************************************************/


	/********************************************** MOTOR (TIM5) *****************************************/
	//Set direction Pins as Output
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN8, MGPIO_PIN_OUTPUT);		//MOTOR2 -> DIR1
    MGPIO_vidSetPinMode(MGPIOB_REG, PIN9, MGPIO_PIN_OUTPUT);		//MOTOR2 -> DIR2
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN5, MGPIO_PIN_OUTPUT);		//MOTOR1 -> DIR1
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN6, MGPIO_PIN_OUTPUT);		//MOTOR1 -> DIR2

	//Set PWM Pins as Alternative for MOTOR
	MGPIO_vidSetPinMode(MGPIOA_REG, PIN0, MGPIO_PIN_ALTFN);			//TIM5 --> CH1
	MGPIO_voidSetPinAltFn(MGPIOA_REG, PIN0, AF2);

	MGPIO_vidSetPinMode(MGPIOA_REG, PIN1, MGPIO_PIN_ALTFN);			//TIM5 --> CH2
	MGPIO_voidSetPinAltFn(MGPIOA_REG, PIN1, AF2);

	//Initialize Timer5 for Motors
	App_voidSpeedInit();

	/****************************************************************************************************/

	/*************************************** Encoders (EXT2 & EXT3) *************************************/

	//EXTI2 --> A2
	MGPIO_vidSetPinMode(MGPIOA_REG, PIN2, MGPIO_PIN_INPUT);
	MGPIO_vidSetPinPullType(MGPIOA_REG, PIN2, MGPIO_PIN_PULLUP);
	MEXTI_voidEnableEXTI(EXTI2);
	MEXTI_voidSetSignalLatch(EXTI2, FALLING_EDGE);
	MEXTI2_voidSetCallBack(EXTI2_ISR);
	MEXTI_voidSetEXTIConfiguration(EXTI2, MGPIOA_REG);

	//EXTI3 --> A3
	MGPIO_vidSetPinMode(MGPIOA_REG, PIN3, MGPIO_PIN_INPUT);
	MGPIO_vidSetPinPullType(MGPIOA_REG, PIN3, MGPIO_PIN_PULLUP);
	MEXTI_voidEnableEXTI(EXTI3);
	MEXTI_voidSetSignalLatch(EXTI3, FALLING_EDGE);
	MEXTI3_voidSetCallBack(EXTI3_ISR);
	MEXTI_voidSetEXTIConfiguration(EXTI3, MGPIOA_REG);


	//Turn on speed Timer

	APP_voidSetupSpeedTimer();

	/*****************************************************************************************************/

	/********************************************** UART1 (BLUETOOTH) ***********************************/


	//Set RX1 as Alternative
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN7, MGPIO_PIN_ALTFN);			//UART1 --> RX (RECEIVE ONLY)
	MGPIO_voidSetPinAltFn(MGPIOB_REG, PIN7, AF7);

	//Initialize UART1
	USART1_voidInit();

	/****************************************************************************************************/

	/********************************************** UART6 (PI) ******************************************/

	//Set RX2 as Alternative
	MGPIO_vidSetPinMode(MGPIOA_REG, PIN12, MGPIO_PIN_ALTFN);			//UART6 --> RX (RECEIVE ONLY)
	MGPIO_voidSetPinAltFn(MGPIOA_REG, PIN12, AF8);

	//Initialize UART2
	USART6_voidInit();

	/****************************************************************************************************/


	/*************************************** ULTRASONIC (TIM2 & TIM3) ***********************************/

	//Set ECHO Pin as Alternative on TIMER2 --> CH2
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN3, MGPIO_PIN_ALTFN);			//TIM2 --> CH2
	MGPIO_voidSetPinAltFn(MGPIOB_REG, PIN3, AF1);

	//Set TRIG Pin as Alternative on TIMER3 --> CH1
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN4, MGPIO_PIN_ALTFN);			//TIM3 --> CH1
	MGPIO_voidSetPinAltFn(MGPIOB_REG, PIN4, AF2);

	//TURN ON ULTRASONIC

	//Initialize Timer3 To send Triggers
	APP_voidTrigPulses();

	//Initialize Timer2 To receive echo on ICU
	APP_voidSetICU();


	/****************************************************************************************************/

	/************************************************ KPD ***********************************************/

	for (u8 i = 4; i < 8; i++)
	{
		MGPIO_vidSetPinMode(MGPIOA_REG, i, MGPIO_PIN_OUTPUT);
	}

	for (u8 i = 8; i < 12; i++)
	{
		MGPIO_vidSetPinMode(MGPIOA_REG, i, MGPIO_PIN_INPUT);
		MGPIO_vidSetPinPullType(MGPIOA_REG, i, MGPIO_PIN_PULLUP);

	}

	/*****************************************************************************************************/

	/************************************************ LED ************************************************/

	MGPIO_vidSetPinMode(MGPIOB_REG, PIN0, MGPIO_PIN_OUTPUT);		//LED1
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN1, MGPIO_PIN_OUTPUT);		//LED2
	MGPIO_vidSetPinMode(MGPIOB_REG, PIN2, MGPIO_PIN_OUTPUT);		//LED3

	/*****************************************************************************************************/



	while(1)
	{

		if (auth == 0)
		{
			HTFT_vidAuthInit();
		}

		if (menu == 0  && auth == 1)	//ASK NORMAL OR ADAPTIVE
		{
			TFT_VidFillColor(BLACK);
			HTFT_vidPrintInit();			//PRINT OPTIONS

			//Turn on LEDS for 1 second
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN0, MGPIO_PIN_HIGH);
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN1, MGPIO_PIN_HIGH);
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN2, MGPIO_PIN_HIGH);
			MSTK_voidDelayMs(1000);
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN0, MGPIO_PIN_LOW);
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN1, MGPIO_PIN_LOW);
			MGPIO_vidSetPinValue(MGPIOB_REG, PIN2, MGPIO_PIN_LOW);


			u8 key = KPD_u8GetKeypress();	//GET KEY PRESS
			while (key == NOT_PRESSED)
			{
				key = KPD_u8GetKeypress();
				if (key != NOT_PRESSED)
				{
					switch(key)
					{
					case '1':
						menu = 1;		//GO TO NORMAL MODE
						break;
					case '2':
						menu = 2;		//GO TO ADAPTIVE MODE
						break;
					}
				}

			}
		}
		else if (menu == 1 && auth == 1)	//Normal Mode --> full BLUETOOTH control
		{
			//Print Distance and speed


			HTFT_vidSendNumAdaptive((curSpeed),  (distance));
			USART1_u8Receive(&bluetoothData);

			if (bluetoothData == 'F' && distance > DANGER_DISTANCE)
			{
				 APP_voidMotorForward(&curPWM, &curDir);
			}
			else if (bluetoothData == 'F' && distance <= DANGER_DISTANCE)
			{
				APP_voidMotorStop(&curPWM);

			}
			else if ((bluetoothData == 'L' || bluetoothData == 'G') && distance > DANGER_DISTANCE)
			{
				 APP_voidMotorLeft(&curDir);							//Change Direction to left
				 App_voidIncreaseSpeed(&curPWM);
			}
			else if ((bluetoothData == 'L' || bluetoothData == 'G') && distance <= DANGER_DISTANCE)
			{
				APP_voidMotorStop(&curPWM);

			}
			else if ((bluetoothData == 'R' || bluetoothData == 'I') && distance > DANGER_DISTANCE)
			{
				 APP_voidMotorRight(&curDir);						    //Change Direction to right
				 App_voidIncreaseSpeed(&curPWM);
			}
			else if ((bluetoothData == 'R' || bluetoothData == 'I') && distance <= DANGER_DISTANCE)
			{
				APP_voidMotorStop(&curPWM);

			}
			else if (bluetoothData == 'B' )
			{
				APP_voidMotorBackward(&curPWM, &curDir);
			}
			else if (bluetoothData == 'S')
			{
				APP_voidMotorStop(&curPWM);
			}
			else if (bluetoothData == 'D')
			{
				App_voidDecelerationLoop(&curPWM);				//Slow down car --> Stop
			    APP_voidMotorStop(&curPWM);
				menu = 0;										//Go back to choose Mode
				auth = 1;
			}

		}
		else if (menu == 2 && auth == 1)	//Ask for Speed [MIN:MAX]
		{
			HTFT_vidPrintSpeed();			//Print Speed Request
			u8 key = KPD_u8GetKeypress();	//Get speed in array
			while (speedCount < 2)
			{
				key = KPD_u8GetKeypress();
				if (key != NOT_PRESSED)
				{
					//Get Digit
					speedArr[speedCount] = (key - '0');
					//Print Digit
					HTFT_vidSendNum1DigSpeed((key - '0'));
					speedCount++;
				}
			}

			//Calculate Speed from array
			setSpeed = (speedArr[0] * 10) + (speedArr[1]);
			if (setSpeed > MAX_SPEED )
			{
				setSpeed = MAX_SPEED;
			}


			speedCount = 0;
			//Go To Distance Menu
			menu = 3;
		}

		else if (menu == 3 && auth == 1)	//Ask for Distance [MIN:MAX]
		{
			HTFT_vidPrintDistance();		//Print Distance Request

			while (distanceCount < 3)
			{
				u8 key = KPD_u8GetKeypress();
				if (key != NOT_PRESSED)
				{
					//Get Digit
					distanceArr[distanceCount] = (key - '0');
					//Print Digit
					HTFT_vidSendNum1DigDista((key - '0'));
					distanceCount++;
				}
			}
			//Calculate Distance from array
			setDistance = (distanceArr[0] * 100) + (distanceArr[1] * 10) + (distanceArr[2]);
			if (setDistance <= DANGER_DISTANCE )
			{
				setDistance = DANGER_DISTANCE + 10;
			}

			distanceCount = 0;
			//Go To Adaptive Control
			menu = 4;
		}

		else if (menu == 4 && auth == 1)	//ADAPTIVE MODE --> (R/L/B) CONTROL
		{
			HTFT_vidSendNumAdaptive((curSpeed),  (distance));

			USART1_u8Receive(&bluetoothData);

			if (distance <= DANGER_DISTANCE_AD && bluetoothData != 'B')
			{
				APP_voidMotorStop(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (distance > DANGER_DISTANCE_AD && (curSpeed < setSpeed - 5) && distance >= setDistance && bluetoothData == 'L')
			{
				//LEFT
				APP_voidMotorLeft(&curDir);
				App_voidIncreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}

			if (distance > DANGER_DISTANCE_AD && (curSpeed < setSpeed - 5) && distance >= setDistance && bluetoothData == 'R')
			{
				//RIGHT
				APP_voidMotorRight(&curDir);
				App_voidIncreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (distance > DANGER_DISTANCE_AD && (curSpeed < setSpeed - 5) && distance >= setDistance && bluetoothData == 'S')
			{
				//FORWARD
				APP_voidMotorForwardDir(&curPWM, &curDir);
				App_voidIncreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (distance > DANGER_DISTANCE_AD &&  (distance < setDistance) && bluetoothData == 'L')
			{
				//LEFT
				APP_voidMotorLeft(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (distance > DANGER_DISTANCE_AD &&  (distance < setDistance) && bluetoothData == 'R')
			{
				//RIGHT
				APP_voidMotorRight(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (distance > DANGER_DISTANCE_AD &&  (distance < setDistance) && bluetoothData == 'S')
			{
				//FORWARD
				APP_voidMotorForwardDir(&curPWM, &curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);


			}



			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance <= setDistance && bluetoothData == 'L')
			{

				//DECREASE
				APP_voidMotorLeft(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);


			}


			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance <= setDistance && bluetoothData == 'R')
			{

				//DECREASE
				APP_voidMotorRight(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}



			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance <= setDistance && bluetoothData == 'S')
			{
				//DECREASE
				APP_voidMotorForwardDir(&curPWM, &curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}

			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance > setDistance && bluetoothData == 'S')
			{
				//DECREASE
				APP_voidMotorForwardDir(&curPWM, &curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);
			}

			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance > setDistance && bluetoothData == 'R')
			{
				//DECREASE
				APP_voidMotorRight(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);
			}

			if (distance > DANGER_DISTANCE_AD && (curSpeed > setSpeed + 5) && distance > setDistance && bluetoothData == 'L')
			{
				//DECREASE
				APP_voidMotorLeft(&curDir);
				App_voidDecreaseSpeedSlow(&curPWM);
				USART1_u8Receive(&bluetoothData);

			}


			if (bluetoothData == 'B')
			{
				APP_voidMotorBackward(&curPWM, &curDir);
				USART1_u8Receive(&bluetoothData);

			}
		}


	}
}


void TIM3_IRQHandler(void) {

	u32 reading;
	reading = TMR_voidReadCapture(TMR3, CH1);

	if (state == 0)
	{
		rising_time = reading;

	}
	else
	{
		falling_time = reading;
		distance = ((falling_time - rising_time)/58);
		TMR_voidClearCount(TMR3);

	}
	state ^= 1;
}


void APP_voidSetupSpeedTimer(void)
{
	TMR_voidSetPrescaler(TMR4, 16000);

	//Set ovf at 1000 ms
	TMR_voidSetARR(TMR4,  1000 - 1);

	//enable interrupt
	TMR_vidEnableOVFInt(TMR4);


	TMR_voidClearCount(TMR4);

	TMR_voidStart(TMR4);
}


void TIM4_IRQHandler(void)
{

	curSpeed = DPP * ((pulses2 + pulses3) /2);
	pulses2 = 0;
	pulses3 = 0;

	TMR_vidClearOvf(TMR4);
}

void USART6_IRQHandler(void)
{
	u8 reading = USART6_u8ReceiveInt();
	switch(reading)
	{
	case 'A':				//Authorization Signal
		auth = 1;
		break;
	case 'D':				//Danger Signal --> Slow down --> Stop car
		App_voidDecelerationLoop(&curPWM);
		APP_voidMotorStop(&curPWM);
		break;
	}
}


void EXTI2_ISR(void)
{
	pulses2++;
}

void EXTI3_ISR(void)
{
	pulses3++;
}





