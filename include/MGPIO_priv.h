/***************************************************************************************/
/* Author               : Ahmed Hammad                                                 */
/* Version              : V0.0.0                                                       */
/* Date                 : 22 - 1 -2023                                                 */
/* Description          : MRCC_Private.h -> Register Definitions                       */
/***************************************************************************************/

/***************************************************************************************/
/*  - Developer can't Edit                                                             */
/*                 * Register Definition Design                                        */
/*                         1)  #define : NO                                       	   */
/*                         2)  Struct  : YES                                           */
/*                         3)  Union   : NO                                            */
/***************************************************************************************/

#ifndef MGPIO_priv
#define MGPIO_priv

typedef struct
{
	u32 volatile MODER;
	u32 volatile OTYPER;
	u32 volatile OSPEEDR;
	u32 volatile PUPDR;
	u32 volatile IDR;
	u32 volatile UDR;
	u32 volatile BSRR;
	u32 volatile LCKR;
	u32 volatile AFRL;
	u32 volatile AFRH;
}MGPIO_t;


#define    MGPIOA_BASE_ADDRESS              (0x40020000)
#define    MGPIOB_BASE_ADDRESS              (0x40020400)
#define    MGPIOC_BASE_ADDRESS              (0x40020800)

#define MGPIOA						((MGPIO_t *)(MGPIOA_BASE_ADDRESS))
#define MGPIOB						((MGPIO_t *)(MGPIOB_BASE_ADDRESS))
#define MGPIOC 						((MGPIO_t *)(MGPIOC_BASE_ADDRESS))

#endif
