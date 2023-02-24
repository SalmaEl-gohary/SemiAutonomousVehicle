#ifndef MSTK_priv
#define MSTK_priv

/*************************************************************************/
/* 						Register Definition								 */
/*************************************************************************/


#define MSTK_BASE_ADDRESS		0xE000E010


#define MSTK_STK_CTRL			*((volatile u32 * )(MSTK_BASE_ADDRESS + 0x00))
#define MSTK_STK_LOAD			*((volatile u32 * )(MSTK_BASE_ADDRESS + 0x04))
#define MSTK_STK_VAL			*((volatile u32 * )(MSTK_BASE_ADDRESS + 0x08))
#define MSTK_STK_CALIB			*((volatile u32 * )(MSTK_BASE_ADDRESS + 0x0C))


#define MSTK_EN_BIT				0
#define MSTK_INT_EN				1
#define MSTK_CLK_SRC			2
#define MSTK_COUNT_FLAG			16


#endif
