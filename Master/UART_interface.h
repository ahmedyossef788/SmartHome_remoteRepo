/*
 * UART_interface.h
 *
 * Created: 9/30/2023 3:04:22 PM
 *  Author: ahmed
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_init(void);
void UART_TxChar(u8 TxData);
void UART_RxChar(u8* RxData);
void UART_sendString(u8* TxString);
void UART_recieveString(u8* RxString);

#endif /* UART_INTERFACE_H_ */