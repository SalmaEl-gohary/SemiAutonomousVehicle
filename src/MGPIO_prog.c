/****************************************************************/
/* Author: Salma Elgohary
 * Version:
 * Date:
 * Description:
 * Module Features:  MGPIO_prog.c   ->   Function Implementation
 * 		01- MGPIO_vidSetPinMode()
 * 		02- MGPIO_vidSetOutputType()
 * 		03- MGPIO_vidSetOutputPinSpeed()
 * 		04- MGPIO_vidSetPinPullType()
 * 		05- MGPIO_vidSetPinValue()
 * 		06- MGPIO_vidGetPinValue()
 * 		07- MGPIO_vidSetPinLock()
 * 		08- MGPIO_vidSetResetPin()
 * 		09- MGPIO_vidSetPinAltFn()
 ******************************************************************/

#include "LBIT_MATH.h"
#include "LERROR_STATES.h"
#include "LSTD_TYPES.h"

#include "MGPIO_priv.h"
#include "MGPIO_config.h"
#include "MGPIO_int.h"


/*#################################################################################*/
/*						FUNCTION PROTOTYPES							               */
/*#################################################################################*/


/***********************************************************************************/
/*                         04- MGPIO_vidSetPinMode()                    		   */
/*-------------------------------------------------------------------------------- */
/* @fu MGPIO_vidSetPinMode                                 						   */
/* @brief  This Function used to set pin mode									   */
/* 				- INPUT															   */
/* 				- OUTPUT														   */
/* 				- ALTF															   */
/* 				- ANALOG	          								    		   */
/* @param[in] Copy_uddtPortNum: The port of the pin								   */
/* 			  [MGPIOA_REG, MGPIOB_REG, MGPIOC_REG] Detect required register  	   */
/* @param[in] Copy_uddtPinNum: the Pin number									   */
/* 		      [PIN0: PIN15]														   */
/* @param[in] Copy_uddtPinMode:  												   */
/* 			  [MGPIO_PIN_INPUT, MGPIO_PIN_OUTPUT, MGPIO_PIN_ALTF, MGPIO_PIN_ANALOG]*/
/***********************************************************************************/

void MGPIO_vidSetPinMode(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, MODE_t Copy_uddtPinMode)
{
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		      CLR_BITS(MGPIOA->MODER,(3U<<Copy_uddtPinNum * 2U) ) ;
		      MGPIOA->MODER |= (u32)((Copy_uddtPinMode << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOB_REG :
	   	      CLR_BITS(MGPIOB->MODER,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOB->MODER |= (u32)((Copy_uddtPinMode << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOC_REG :
	   	      CLR_BITS(MGPIOC->MODER,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOC->MODER |= (u32)((Copy_uddtPinMode << Copy_uddtPinNum * 2U )) ; break ;
	   default :  /*Do Nothing */                                                 break ;
	   }
}

void MGPIO_vidSetOutputType(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, OutputType_t Copy_uddtOutputType)
{
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		   	  CLR_BIT(MGPIOA->OTYPER, Copy_uddtPinNum);
		      MGPIOA->OTYPER |= (u32)((Copy_uddtOutputType << Copy_uddtPinNum )) ; break ;
	   case MGPIOB_REG :
		   	  CLR_BIT(MGPIOB->OTYPER, Copy_uddtPinNum);
	   	      MGPIOB->OTYPER |= (u32)((Copy_uddtOutputType << Copy_uddtPinNum )) ; break ;
	   case MGPIOC_REG :
		   	  CLR_BIT(MGPIOC->OTYPER, Copy_uddtPinNum);
	   	      MGPIOC->OTYPER |= (u32)((Copy_uddtOutputType << Copy_uddtPinNum )) ; break ;
	   default :  /*Do Nothing */                                                  break ;
	   }
}

void MGPIO_vidSetOutputSpeed(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, SPEED_t Copy_uddtSpeed)
{
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		      CLR_BITS(MGPIOA->OSPEEDR,(3U<<Copy_uddtPinNum * 2U) ) ;
		      MGPIOA->OSPEEDR |= (u32)((Copy_uddtSpeed << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOB_REG :
	   	      CLR_BITS(MGPIOB->OSPEEDR,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOB->OSPEEDR |= (u32)((Copy_uddtSpeed << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOC_REG :
	   	      CLR_BITS(MGPIOC->OSPEEDR,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOC->OSPEEDR |= (u32)((Copy_uddtSpeed << Copy_uddtPinNum * 2U )) ; break ;
	   default :  /*Do Nothing */                                                 break ;
	   }
}

void MGPIO_vidSetPinPullType(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, PULL_t Copy_uddtPullType)
{
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		      CLR_BITS(MGPIOA->PUPDR,(3U<<Copy_uddtPinNum * 2U) ) ;
		      MGPIOA->PUPDR |= (u32)((Copy_uddtPullType << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOB_REG :
	   	      CLR_BITS(MGPIOB->PUPDR,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOB->PUPDR |= (u32)((Copy_uddtPullType << Copy_uddtPinNum * 2U )) ; break ;
	   case MGPIOC_REG :
	   	      CLR_BITS(MGPIOC->PUPDR,(3U<<Copy_uddtPinNum * 2U) ) ;
	   	      MGPIOC->PUPDR |= (u32)((Copy_uddtPullType << Copy_uddtPinNum * 2U )) ; break ;
	   default :  /*Do Nothing */                                                 break ;
	   }
}

void MGPIO_vidSetPinValue(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum, u8 Copy_u8Value)
{
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		   	  CLR_BIT(MGPIOA->UDR, Copy_uddtPinNum);
		      MGPIOA->UDR |= (u32)((Copy_u8Value << Copy_uddtPinNum )) ; break ;
	   case MGPIOB_REG :
		   	  CLR_BIT(MGPIOB->UDR, Copy_uddtPinNum);
	   	      MGPIOB->UDR |= (u32)((Copy_u8Value << Copy_uddtPinNum )) ; break ;
	   case MGPIOC_REG :
		   	  CLR_BIT(MGPIOC->UDR, Copy_uddtPinNum);
	   	      MGPIOC->UDR |= (u32)((Copy_u8Value << Copy_uddtPinNum )) ; break ;
	   default :  /*Do Nothing */                                                  break ;
	   }
}

u8 MGPIO_u8GetPinValue(PORT_t Copy_uddtPortNum, PIN_t Copy_uddtPinNum)
{
	u8 value;
	switch(Copy_uddtPortNum)
	   {
	   case MGPIOA_REG :
		      value = GET_BIT(MGPIOA->IDR, Copy_uddtPinNum) ; break ;
	   case MGPIOB_REG :
		      value = GET_BIT(MGPIOB->IDR, Copy_uddtPinNum) ; break ;
	   case MGPIOC_REG :
		      value = GET_BIT(MGPIOC->IDR, Copy_uddtPinNum) ; break ;
	   default :  /*Do Nothing */                                                  break ;
	   }
	return value;
}

void MGPIO_vidSetPortValue(PORT_t Copy_uddtPortNum, u32 Copy_u32Value)
{
	switch(Copy_uddtPortNum)
	{
	case MGPIOA_REG:
		MGPIOA -> UDR = Copy_u32Value; 	break;
	case MGPIOB_REG:
		MGPIOB -> UDR = Copy_u32Value;  break;
	case MGPIOC_REG:
		MGPIOC -> UDR = Copy_u32Value;  break;
	default:  /* Do Nothing */          break;
	}
}

void MGPIO_vidSetHalfPort(PORT_t Copy_uddtPortNum, u32 Copy_u32Value, u8 Copy_u8Half)
{
	switch(Copy_uddtPortNum)
	{
	case MGPIOA_REG:
		if (Copy_u8Half == 0)
		{
			CLR_BITS(MGPIOA -> UDR, 0x00FF);
			MGPIOA -> UDR |= Copy_u32Value;
		}
		else
		{
			CLR_BITS(MGPIOA -> UDR, 0XFF00);
			MGPIOA -> UDR |= (Copy_u32Value << 8);
		}
		break;
	case MGPIOB_REG:
		if (Copy_u8Half == 0)
		{
			CLR_BITS(MGPIOB -> UDR, 0x00FF);
			MGPIOB -> UDR |= Copy_u32Value;
		}
		else
		{
			CLR_BITS(MGPIOB -> UDR, 0XFF00);
			MGPIOB -> UDR |= (Copy_u32Value << 8);
		}
		break;
	default:	break;
	}
}



void MGPIO_vidSetPortMode(PORT_t Copy_uddtPortNum,  u32 Copy_u32Value)
{
	switch(Copy_uddtPortNum)
		{
		case MGPIOA_REG:
			MGPIOA -> MODER = Copy_u32Value; 	break;
		case MGPIOB_REG:
			MGPIOB -> MODER = Copy_u32Value;  break;
		case MGPIOC_REG:
			MGPIOC -> MODER = Copy_u32Value;  break;
		default:  /* Do Nothing */          break;
		}
}

void MGPIO_voidSetPinAltFn( u8 Copy_u8PortNum ,u8 Copy_u8PinNum, u8 Copy_u8ALF )
{
	if(Copy_u8PinNum <=7U)
	{
		switch(Copy_u8PortNum )
		{
			 case MGPIOA_REG  : MGPIOA->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case MGPIOB_REG  : MGPIOB->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case MGPIOC_REG  : MGPIOC->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;

			 default : break ;
		}

	}
	// 8 : 15
	// i need 8 = 0 & 15 = 7

	else
	{
	switch(Copy_u8PortNum )
		{
			 case MGPIOA_REG:   MGPIOA->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 case MGPIOB_REG  : MGPIOB->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U ))); break ;
			 case MGPIOC_REG  : MGPIOC->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;

			 default : break ;
		}


	}


}























































