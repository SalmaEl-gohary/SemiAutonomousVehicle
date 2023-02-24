/***************************************************************************************/
/* Author               : Salma Elgohary                                                */
/* Version              : V0.0.0                                                       */
/* Date                 : 29 - 1 -2023                                                 */
/* Description          : NVIC_priv.h -> Register Definitions                       */
/***************************************************************************************/

/***************************************************************************************/
/*  - Developer can't Edit                                                             */
/*                 * Register Definition Design                                        */
/*                         1)  #define : NO                                         */
/*                         2)  Struct  : YES                                            */
/*                         3)  Union   : NO                                            */
/***************************************************************************************/


/***************************************************************************************/
/*                            Guard of file will call on time in c file                */
/***************************************************************************************/

#ifndef NVIC_PRIV_H_
#define NVIC_PRIV_H_


#define NVIC_BASE_ADDRESS		0xE000E100

/*
#define NVIC_ISER_BASE		(NVIC_BASE_ADDRESS + 0x100)
#define NVIC_ICER_BASE		(NVIC_BASE_ADDRESS + 0x180)
#define NVIC_ISPR_BASE		(NVIC_BASE_ADDRESS + 0x204)
#define NVIC_ICPR_BASE		(NVIC_BASE_ADDRESS + 0x280)
#define NVIC_IABR_BASE		(NVIC_BASE_ADDRESS + 0x300)
#define NVIC_IPR_BASE		(NVIC_BASE_ADDRESS + 0x400)

typedef struct
{
	u32 volatile REG_0;
	u32 volatile REG_1;
	u32 volatile REG_2;
	u32 volatile REG_3;
	u32 volatile REG_4;
	u32 volatile REG_5;
	u32 volatile REG_6;
	u32 volatile REG_7;

}NVIC_t;


#define ISER_SET		((NVIC_t *)(NVIC_ISER_BASE))
#define ICER_SET		((NVIC_t *)(NVIC_ICER_BASE))
#define ISPR_SET		((NVIC_t *)(NVIC_ISPR_BASE))
#define ICPR_SET		((NVIC_t *)(NVIC_ICPR_BASE))
#define IABR_SET		((NVIC_t *)(NVIC_IABR_BASE))

#define IPR_SET			((volatile u8 *)(NVIC_IPR_BASE))

*/

typedef struct
{
	u32 ISER[8];
  	u32 RESEREVED_1[24];
  	u32	ICER[8];
  	u32 RESERVED_2[24];
  	u32 ISPR[8];
  	u32 RESERVED_3[24];
	u32 ICPR[8];
 	u32 RESERVED_4[24];
  	u32 IABR[8];
  	u32 RESERVED_5[56];
  	u8 	IPR[240];
  	u32 RESERVED_6[580];
  	u32 STIR;
}MNVIC_t;

#define     NVIC_REG    ((volatile MNVIC_t*)(NVIC_BASE_ADDRESS))

#define     SCB_AIRCR   (*(volatile u32*) 0xE000ED0C)

#define     VECTKEY     0x05FA0000



#endif /* NVIC_PRIV_H_ */
