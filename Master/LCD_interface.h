/*
 * LCD_interface.h
 * 
 * Created: 8/26/2023 9:55:47 PM
 *  Author: ahmed
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "STD_TYPES.h"

void LCD_init       (void);
void LCD_sendCmnd (u8 comand);
void LCD_sendChar   (u8 data);
void LCD_writeString(u8*string);
void LCD_clear      (void);
void LCD_shiftRight (u8 NumberOfshift);
void LCD_goTo       (void);
void LCD_shiftLift  (u8 NumberOfshift);
void LCD_writeNumber(u16 num);


#endif /* LCD_INTERFACE_H_ */