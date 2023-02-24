/*
 * MNVIC_Interface.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Salma Elgohary
 */

#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_

typedef enum{
    NVIC_GroupMode_g16s0 = 3,
    NVIC_GroupMode_g8s2,
    NVIC_GroupMode_g4s4,
    NVIC_GroupMode_g2s8,
    NVIC_GroupMode_g0s16
}NVIC_GroupMode_t;

typedef enum
{
	WWDG_GLOBAL_INT,
	EXTI16_GLOBAL_INT,
	EXTI21_GLOBAL_INT,
	EXTI22_GLOBAL_INT,
	FLASH_GLOBAL_INT,
	RCC_GLOBAL_INT,
	EXTI0_GLOBAL_INT,
	EXTI1_GLOBAL_INT,
	EXTI2_GLOBAL_INT,
	EXTI3_GLOBAL_INT,
	EXTI4_GLOBAL_INT,
	EXTI5_9_GLOBAL_INT,
	TIM2_GLOBAL_INT = 28,
	TIM3_GLOBAL_INT = 29,
	TIM4_GLOBAL_INT = 30,
	USART1_GLOBAL_INT = 37,
	TIM5_GLOBAL_INT = 50,
	USART6_GLOBAL_INT = 71,

}NVIC_IRQ_t ;


typedef struct
{
	u8 Copy_u8IntNum ;
	NVIC_GroupMode_t Copy_uddtGroupMode ;
	u8 Copy_GroupPriority  ;
	u8 Copy_SubPriority  ;

}NVIC_PriorityConfig_t ;

/*******************************************************************/
/********************** Function ProtoTypes ************************/
/*******************************************************************/

void MNVIC_voidEnableInterrupt(u8 Copy_u8IntNum) ;
void MNVIC_voidDisableInterrupt(u8 Copy_u8IntNum) ;
void MNVIC_voidEnableInterruptPending(u8 Copy_u8IntNum) ;
void MNVIC_voidDisableInterruptPending(u8 Copy_u8IntNum) ;
u8   MNVIC_u8InterruptActive(u8 Copy_u8IntNum)           ;
void MNVIC_voidInitInterruptGroup(NVIC_GroupMode_t Copy_uddtGroupMode)    ;
void MNVIC_voidSetInterruptPriority(u8 Copy_u8IntNum ,NVIC_GroupMode_t Copy_uddtGroupMode,u8 Copy_GroupPriority,u8 Copy_SubPriority) ;



#endif /* MNVIC_INTERFACE_H_ */
