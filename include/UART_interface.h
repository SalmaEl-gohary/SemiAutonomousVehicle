/*********************************************************************************************/
/*  Author   :    Fatma Radwan                                                                */
/*  Date     :    3/10/2020                                                                  */
/*********************************************************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H




void USART1_voidInit(void);
void USART1_voidTransmit(u8 data[]);
void   USART1_u8Receive(u8* Copy_u8Data);
u8 USART1_u8ReceiveInt(void);


void USART6_voidInit(void);
void USART6_voidTransmit(u8 data[]);
void   USART6_u8Receive(u8* Copy_u8Data);
u8 USART6_u8ReceiveInt(void);


void USART2_voidInit(void);
void USART2_voidTransmit(u8 data[]);
void   USART2_u8Receive(u8* Copy_u8Data);
u8 USART2_u8ReceiveInt(void);


#endif

