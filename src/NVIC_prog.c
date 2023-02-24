/*
 * NVIC_prog.c
 *
 *  Created on: Jan 29, 2023
 *      Author: salma
 */
#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"
#include "NVIC_priv.h"
#include "NVIC_config.h"
#include "NVIC_int.h"



void MNVIC_voidEnableInterrupt(u8 Copy_u8IntNum)
{
	NVIC_REG->ISER[Copy_u8IntNum / 32] = (1U << Copy_u8IntNum % 32);
}

void MNVIC_voidDisableInterrupt(u8 Copy_u8IntNum)
{
	NVIC_REG->ICER[Copy_u8IntNum / 32] = (1U << Copy_u8IntNum % 32);
}

void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntNum)
{
	NVIC_REG->ISPR[Copy_u8IntNum / 32] = (1U << Copy_u8IntNum % 32);
}

void MNVIC_voidDisableInterruptPending(u8 Copy_u8IntNum)
{
	NVIC_REG->ICPR[Copy_u8IntNum / 32] = (1U << Copy_u8IntNum % 32);
}

u8   MNVIC_u8InterruptActive(u8 Copy_u8IntNum)
{

	return GET_BIT(NVIC_REG->IABR[Copy_u8IntNum / 32], Copy_u8IntNum);
}

void MNVIC_voidInitInterruptGroup(NVIC_GroupMode_t Copy_uddtGroupMode)
{
	SCB_AIRCR = (VECTKEY | (Copy_uddtGroupMode << 8));

}

void MNVIC_voidSetInterruptPriority(u8 copy_u8IntNum ,NVIC_GroupMode_t copy_uddtGroupMode,u8 copy_u8IntGroup,u8 copy_u8IntPrio)
{
	u8 L_u8PrioValue = 0;
	switch(copy_uddtGroupMode){
		case NVIC_GroupMode_g16s0 : L_u8PrioValue =  copy_u8IntGroup; break;
		case NVIC_GroupMode_g8s2  : L_u8PrioValue = (copy_u8IntGroup << 1) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g4s4  : L_u8PrioValue = (copy_u8IntGroup << 2) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g2s8  : L_u8PrioValue = (copy_u8IntGroup << 3) | copy_u8IntPrio; break;
		case NVIC_GroupMode_g0s16 : L_u8PrioValue =  copy_u8IntPrio; break;
	}

	NVIC_REG->IPR[copy_u8IntNum] = L_u8PrioValue << 4;
}
