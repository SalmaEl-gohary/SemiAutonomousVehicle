/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


#define EXTI0     0
#define EXTI1     1
#define EXTI2	  2
#define EXTI3	  3

#define   RISING_EDGE     0

#define   FALLING_EDGE   1


#define    ON_CHANGE       2

/***********	Function Intialize EXTI	Line & Mode By #define	***********/

void MEXTI_voidInit(void)  ;

/***********	Function To Choice The Sense Mode At The Line	***********/

void MEXTI_voidSetSignalLatch(u8 Copy_Exti_Line ,u8 Copy_EXTI_Sense_Mode )  ;

/***********		  Function To Enable The Line				***********/

void MEXTI_voidEnableEXTI(u8 Copy_u8Line) ;

/***********	Function To Disable The Line					***********/

void MEXTI_voidDisableEXTI(u8 Copy_u8Line);

/***********	Function Make SoftWare Interrput				***********/

void MEXIT_voidSoftwareInterrput(u8 Copy_u8Line);

/***********	Function Take A Pointer To Function				***********/

void MEXTI0_voidSetCallBack( void (*ptr) (void));
void MEXTI1_voidSetCallBack( void (*ptr) (void));
void MEXTI2_voidSetCallBack( void (*ptr) (void));

void MEXTI3_voidSetCallBack( void (*ptr) (void));




void MEXTI_voidSetEXTIConfiguration(u8 Copy_u8ExtiLine , u8 Copy_u8GpioPortNum );
#endif  //EXTI_INTERFACE_H
