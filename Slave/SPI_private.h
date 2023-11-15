/*
 * SPI_private.h
 *
 * Created: 10/6/2023 6:10:39 PM
 *  Author: Ahmed
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_
typedef struct  
{
	u8 SPCR;
	u8 SPSR;
	u8 SPDR;
}SPI_REGS;

#define  SPI      ((volatile SPI_REGS*)0x2D)


#define  SPR0       0
#define  SPR1		1
#define  CPHA 		2
#define  CPOL 		3
#define  MSTR		4
#define  DORD 		5
#define  SPE 		6
#define  SPIE		7


#define SPI2X      0
#define WCOL       6
#define SPIF       7






#endif /* SPI_PRIVATE_H_ */