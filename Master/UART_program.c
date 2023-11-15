/*
 * UART_program.c
 *
 * Created: 9/30/2023 3:04:03 PM
 *  Author: Ahmed
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "UART_interface.h"
#include "UART_private.h"


void UART_init(void)
{
	CLR_BIT(UCSRA,U2X);
	
	UBRRL = 103;
	
	u8 initVar = 0x00;
	
	SET_BIT(initVar,URSEL);
	CLR_BIT(initVar,UMSEL);
	CLR_BIT(initVar,UPM1);
	CLR_BIT(initVar,UPM0);
	CLR_BIT(initVar,USBS);
	SET_BIT(initVar,UCSZ1);
	SET_BIT(initVar,UCSZ0);
	CLR_BIT(UCSRB,UCSZ2);
	CLR_BIT(initVar,UCPOL);
	
	UCSRC = initVar; 
	
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}

void UART_TxChar(u8 TxData)
{
	UDR = TxData;
	while(GET_BIT(UCSRA,UDRE) == 0);
}
void UART_RxChar(u8* RxData)
{
	if (RxData != NULL)
	{
		while(GET_BIT(UCSRA,RXC) == 0);
		*RxData = UDR;
	}
}

void UART_sendString(u8* TxString)
{
	if (TxString != NULL)
	{
		u8 charcounter=0;
		while (TxString[charcounter] != '\0')
		{
			UART_TxChar(TxString[charcounter]);
			charcounter++;
		}
	}
}

void UART_recieveString(u8* RxString)
{
	if (RxString != NULL)
	{
		u8 charcounter=0;
		while (RxString[charcounter] != '\0')
		{
			UART_TxChar(RxString[charcounter]);
			charcounter++;
		}
	}
}