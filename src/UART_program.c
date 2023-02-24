/*********************************************************************************************/
/*  Author   :    Fatma Radwan                                                               */
/*  Date     :    16/10/2020                                                                 */
/*********************************************************************************************/

#include "LSTD_TYPES.h"
#include "LBIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"



void USART1_voidInit(void)
{
	
	#if   BAUD_RATE  ==  BAUD_RATE_9600_8MHZ
	USART1 -> BRR = 0x683;
	#elif BAUD_RATE  ==  BAUD_RATE_115200_8MHZ
	USART1 -> BRR = 0x410b0000;
	#endif
	//USART1->CR2 |= (1 << 12);

	SET_BIT(USART1 -> CR1 , 2);     /* Enable Receiver */
	SET_BIT(USART1 -> CR1 , 3); /* Enable Transmitter */
	SET_BIT(USART1 -> CR1,  5);
	USART1 -> SR = 0;              /* clear status register */

	SET_BIT(USART1 -> CR1 , 13);    /* Enable USART */

}

void USART2_voidInit(void)
{

	#if   BAUD_RATE  ==  BAUD_RATE_9600_8MHZ
	USART2 -> BRR = 0x683;
	#elif BAUD_RATE  ==  BAUD_RATE_115200_8MHZ
	USART2 -> BRR = 0x410b0000;
	#endif
	//USART1->CR2 |= (1 << 12);

	SET_BIT(USART2 -> CR1 , 2);     /* Enable Receiver */
	SET_BIT(USART2 -> CR1 , 3); /* Enable Transmitter */
	SET_BIT(USART2 -> CR1,  5);
	USART2 -> SR = 0;              /* clear status register */

	SET_BIT(USART2 -> CR1 , 13);    /* Enable USART */

}

void USART6_voidInit(void)
{

	#if   BAUD_RATE  ==  BAUD_RATE_9600_8MHZ
	USART6 -> BRR = 0x683;
	#elif BAUD_RATE  ==  BAUD_RATE_115200_8MHZ
	USART6 -> BRR = 0x410b0000;
	#endif
	//USART1->CR2 |= (1 << 12);

	SET_BIT(USART6 -> CR1 , 2);     /* Enable Receiver */
	SET_BIT(USART6 -> CR1 , 3); /* Enable Transmitter */
	SET_BIT(USART6 -> CR1,  5);
	USART6 -> SR = 0;              /* clear status register */

	SET_BIT(USART6 -> CR1 , 13);    /* Enable USART */

}


void USART1_voidTransmit(u8 data[])
{
	u8 i= 0;
	while(data[i] !='\0')
	{
		USART1 -> DR = data[i];
		while( GET_BIT(USART1 -> SR , TC) == 0 );
		i++;
	}
}

void USART2_voidTransmit(u8 data[])
{
	u8 i= 0;
	while(data[i] !='\0')
	{
		USART2 -> DR = data[i];
		while( GET_BIT(USART2 -> SR , TC) == 0 );
		i++;
	}
}

void USART6_voidTransmit(u8 data[])
{
	u8 i= 0;
	while(data[i] !='\0')
	{
		USART6 -> DR = data[i];
		while( GET_BIT(USART6 -> SR , TC) == 0 );
		i++;
	}
}

void USART1_u8Receive(u8* Copy_u8Data)
{

	while(GET_BIT(USART1->SR , RXNE) == 0);

	*Copy_u8Data = USART1 -> DR;
}

void USART2_u8Receive(u8* Copy_u8Data)
{

	while(GET_BIT(USART2->SR , RXNE) == 0);

	*Copy_u8Data = USART2 -> DR;
}

void USART6_u8Receive(u8* Copy_u8Data)
{

	while(GET_BIT(USART6->SR , RXNE) == 0);

	*Copy_u8Data = USART6 -> DR;


}

u8 USART6_u8ReceiveInt(void)
{

	return (u8) USART6 -> DR;
}

u8 USART2_u8ReceiveInt(void)
{

	return (u8) USART2 -> DR;
}

u8 USART1_u8ReceiveInt(void)
{

	return (u8) USART1 -> DR;
  	
}
