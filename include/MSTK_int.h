

#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_


typedef enum
{
	MSTK_INT_DISABLE ,
	MSTK_INT_ENABLE
}INT_t ;

#define AHB		1
#define AHB_8 	0

void MSTK_voidInit(void) ;
void MSTK_voidStart(u32 Copy_u32PreloadVal) ;
u8   MSTK_u8ReadCountFlag(void) ;
void MSTK_voidSetIntStatus(INT_t Copy_uddtIntStatus) ;
void MSTK_voidDelayMs(u32 Copy_u32Time) ;
void MSTK_voidDelayUs(u32 Copy_u32Time) ;
void MSTK_voidSetCallBack(void (*PFunc)(void)) ;

#endif /* MSTK_INTERFACE_H_ */
