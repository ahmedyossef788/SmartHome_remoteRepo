/*
 * EEPROM_interface.h
 *
 * Created: 10/13/2023 10:10:30 PM
 *  Author: Ahmed
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_init     (void);
void EEPROM_writeByte(u16 wordAddress, u8 data);
void EEPROM_readByte (u16 wordAddress, u8* data);
void EEPROM_writePage(u16 baseAddress, u8* data, u8 dataSize);
void EEPROM_readPage (u16 baseAddress, u8* data, u8 dataSize);

#endif /* EEPROM_INTERFACE_H_ */