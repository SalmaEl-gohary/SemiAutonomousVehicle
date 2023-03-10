/*********************************************************************************************/
/*  Author   :    Fatma Radwan                                                                */
/*  Date     :    3/10/2020                                                                  */
/*********************************************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_Register;

#define   USART1      ((volatile UART_Register*)0x40011000)
#define   USART2	  ((volatile UART_Register*)0x40004400)
#define   USART6	  ((volatile UART_Register*)0x40011400)

/* status register (USART_SR)  Pins  */
#define   RXNE      5                 /* this bit is set when data transferred to USART_DR 
                                         and interrupt generated if RXNEIE=1 in USART_CR1  */
										   
#define   TC        6                 /* this bit is set by hardware when transmission is complete and if 
                                         TXE is set . interrupt is generated if TCIE=1 in USART_CR1 */
										 
#define   TXE       7

#define   BAUD_RATE_9600_8MHZ       0
#define   BAUD_RATE_115200_8MHZ     1

#endif
