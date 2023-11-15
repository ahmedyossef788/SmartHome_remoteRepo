/*
 * SPI_program.c
 *
 * Created: 10/6/2023 6:10:02 PM
 *  Author: Ahmed
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"


static void (*private_pCallBackSPI)(u8)=NULL;

void SPI_initMaster(void)
{
	SET_BIT(SPI->SPCR,DORD);
	
	SET_BIT(SPI->SPCR,MSTR);
	
	SET_BIT(SPI->SPCR,CPOL);
	SET_BIT(SPI->SPCR,CPHA); 
	
	SET_BIT(SPI->SPCR,SPR0);
	CLR_BIT(SPI->SPCR,SPR1);
	CLR_BIT(SPI->SPSR,SPI2X);
	
	// Enable SPI
	SET_BIT(SPI->SPCR,SPE);	
}

void SPI_initSlave (void)
{
	SET_BIT(SPI->SPCR,DORD);
	
	CLR_BIT(SPI->SPCR,MSTR);
	
	SET_BIT(SPI->SPCR,CPOL);
	SET_BIT(SPI->SPCR,CPHA);
	
	// Enable SPI
	SET_BIT(SPI->SPCR,SPE);
}

void SPI_tranceive(u8 TxData, u8* RxData)
{
	if (RxData != NULL)
	{
		while(1 == GET_BIT(SPI->SPSR,WCOL));
		SPI->SPDR = TxData;
		
		while(0==GET_BIT(SPI->SPSR,SPIF));
		
		*RxData = SPI->SPDR;
	}
}

void SPI_transmitAsynchronous(u8 TxData, void(*ptrToFun)(u8 RxData))
{
	if (ptrToFun != NULL)
	{
		SET_BIT(SPI->SPCR,SPIE);
		
		private_pCallBackSPI=ptrToFun;
		
		while(1 == GET_BIT(SPI->SPSR,WCOL));
		SPI->SPDR = TxData;
	}
}

void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{		
		if (private_pCallBackSPI!=NULL)
		{
			private_pCallBackSPI(SPI->SPDR);
		}
}

