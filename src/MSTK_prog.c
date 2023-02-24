

/***************************************************************************************/
/*                            StandarAd Types LIB                                       */
/***************************************************************************************/

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"


/***************************************************************************************/
/*                                    Lower Layer                                      */
/***************************************************************************************/



/***************************************************************************************/
/*                                    Own Header                                       */
/***************************************************************************************/

#include "MSTK_priv.h"
#include "MSTK_config.h"
#include "MSTK_int.h"

/***************************************************************************************/
/*                                    Function Implementation                          */
/***************************************************************************************/

static void (*MSTK_CallBack)(void)  ;

// calling by Hardware if interrupt happens
void SysTick_Handler(void)
{
	// Execute CallBack Function
	MSTK_CallBack() ;
}

void MSTK_voidInit(void)
{
	//TODO
	/* [Enable Systick Interrupt - clock = AHB/8 - Stop Systick]*/
	#if CLK_SRC == AHB
		SET_BIT(MSTK_STK_CTRL, MSTK_CLK_SRC);
	#elif	CLK_SRC == AHB/8
		CLR_BIT(MSTK_STK_CTRL, MSTK_CLK_SRC);
	#endif

	SET_BIT(MSTK_STK_CTRL, MSTK_INT_EN);
	CLR_BIT(MSTK_STK_CTRL, MSTK_EN_BIT);

}
void MSTK_voidStart(u32 Copy_u32PreloadVal)
{
	//if F_CPU -> HSI = 16MHz , AHB = 16 MHz , F_Timer = AHB/8 = 2 MHz
	// 0.5 us for each count

	//Step 1: Load Value
	MSTK_STK_LOAD = Copy_u32PreloadVal - 1;

	//Step 2: Clear Val Reg
	MSTK_STK_VAL  = 1;
	//Step 3: Enable Systick
	SET_BIT(MSTK_STK_CTRL, MSTK_EN_BIT);
}
u8   MSTK_u8ReadCountFlag(void)
{

	u8 Flag = GET_BIT(MSTK_STK_CTRL, MSTK_COUNT_FLAG);

	return Flag;
}
void MSTK_voidSetIntStatus(INT_t Copy_uddtIntStatus)
{
	//TODO
	//Step 1 : Clear Bit of Interrupt
	CLR_BIT(MSTK_STK_CTRL, MSTK_INT_EN);
	//Step 2 : Set the Bit of interrupt with the input
	MSTK_STK_CTRL |= (Copy_uddtIntStatus << MSTK_INT_EN);

}
void MSTK_voidDelayMs(u32 Copy_u32Time)
{
	//TODO
	//Step 1 : Init Systick
	MSTK_voidInit() ;

	//Step 2 : Disable INT
	MSTK_voidSetIntStatus(MSTK_INT_DISABLE) ;

	//Step 3 : Start Systick( Copy_u32Time )
    MSTK_voidStart(Copy_u32Time * 2000) ;
	//Step 4 : Wait Flag Polling */
	while(MSTK_u8ReadCountFlag() == 0) ;
}

void MSTK_voidDelayUs(u32 Copy_u32Time)
{
//TODO
	//Step 1 : Init Systick
	MSTK_voidInit();

	//Step 2 : Disable INT
	MSTK_voidSetIntStatus(MSTK_INT_DISABLE);

	//Step 3 : Start Systick( Copy_u32Time)
	MSTK_voidStart(Copy_u32Time * 2);

	//Step 4 : Wait Flag Polling */
	while(MSTK_u8ReadCountFlag() == 0) ;
}
void MSTK_voidSetCallBack(void (*PFunc)(void))
{
	// assign the function passed  to Global pointer
	MSTK_CallBack = PFunc ;
}
