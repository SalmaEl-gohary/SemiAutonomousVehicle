/*
 * HMOTOR_PWM_Iterface.h
 *
 *  Created on: Feb 13, 2023
 *      Author: abdelhamid
 */

#ifndef HMOTOR_PWM_ITERFACE_H_
#define HMOTOR_PWM_ITERFACE_H_


/***************************************************************************************/
/*                            Standard Types LIB                                       */
/***************************************************************************************/

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"
/***************************************************************************************/


#define MAX_PWM			60000
#define MIN_PWM			4000

void App_voidSpeedInit();
void App_voidAccelerationLoop(u32 *);
void App_voidDecelerationLoop(u32 *);
void App_voidIncreaseSpeed(u32 * );
void App_voidIncreaseSpeedSlow(u32 * speedValue);

void App_voidDecreaseSpeed(u32 *);
void App_voidDecreaseSpeedSlow(u32 *);

void APP_voidMotorForward(u32 * curSpeed, u8 * dir);
void APP_voidMotorBackward(u32 * curSpeed, u8 * dir);
void APP_voidMotorLeft(u8 * curDir);
void APP_voidMotorRight(u8 * curDir);
void APP_voidMotorStop(u32 * speed);
void APP_voidMotorForwardDir(u32 * curSpeed, u8 * curDir);








#endif /* HMOTOR_PWM_ITERFACE_H_ */
