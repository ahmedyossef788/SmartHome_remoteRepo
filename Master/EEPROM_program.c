/*
 * EEPROM_program.c
 *
 * Created: 10/13/2023 10:10:07 PM
 *  Author: Ahmed
 */ 

#define F_CPU   16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "TWI_interface.h"

/* HAL */
#include "EEPROM_interface.h"
#include "EEPROM_private.h"


void EEPROM_init(void)
{
	TWI_initMaster();
}


void EEPROM_writeByte(u16 wordAddress, u8 data)
{
	u8 address = (wordAddress>>8) | EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send word address
	TWI_sendMasterDataByte((u8)wordAddress);
	
	// Send byte data
	TWI_sendMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}


void EEPROM_readByte(u16 wordAddress, u8* data)
{
	u8 address = (wordAddress>>8) | EEPROM_FIXED_ADDRESS;
	
	// Send start condition
	TWI_sendStartCondition();
	
	// Send slave address with write operation
	TWI_sendSlaveAddWithWrite(address);
	
	// Send word address
	TWI_sendMasterDataByte((u8)wordAddress);
	
	// Send Repeated start condition
	TWI_sendRepStartCondition();
	
	// Send slave address with read operation
	TWI_sendSlaveAddWithRead(address);
	
	// Read byte data
	TWI_receiveMasterDataByte(data);
	
	// Send stop condition
	TWI_sendStopCondition();
	
	// Self-timed Write Cycle delay
	_delay_ms(5);
}


void EEPROM_writePage(u16 baseAddress, u8* data, u8 dataSize)
{
	if((data!=NULL)&&(dataSize<=16))
	{
		u8 address = (baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		
		// Send start condition
		TWI_sendStartCondition();
		
		// Send slave address with write operation
		TWI_sendSlaveAddWithWrite(address);
		
		// Send word address
		TWI_sendMasterDataByte((u8)baseAddress);
		
		u8 counter;
		for(counter=0;counter<dataSize;counter++)
		{
			// Send byte data
			TWI_sendMasterDataByte(data[counter]);
		}
		
		// Send stop condition
		TWI_sendStopCondition();
		
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}
void EEPROM_readPage(u16 baseAddress, u8* data, u8 dataSize)
{
	if((data!=NULL)&&(dataSize<=16))
	{
		u8 address = (baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		
		// Send start condition
		TWI_sendStartCondition();
		
		// Send slave address with write operation
		TWI_sendSlaveAddWithWrite(address);
		
		// Send word address
		TWI_sendMasterDataByte((u8)baseAddress);
		
		// Send Repeated start condition
		TWI_sendRepStartCondition();
		
		// Send slave address with read operation
		TWI_sendSlaveAddWithRead(address);
		
		u8 counter;
		for(counter=0;counter<dataSize-1;counter++)
		{
			// Read byte data
			TWI_receiveMasterDataByteAck(&data[counter]);
		}
		
		// Read last byte data
		TWI_receiveMasterDataByteNack(&data[counter]);
		
		// Send stop condition
		TWI_sendStopCondition();
		
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}