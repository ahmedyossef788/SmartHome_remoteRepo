/*
 * LM35_program.c
 *
 * Created: 10/23/2023 5:51:31 PM
 *  Author: Karim Mostafa
 */ 

#define F_CPU 16000000
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "TMR0_interface.h"

/* HAL */
#include "LCD_interface2.h"
#include "DCM_interface.h"
#include "LM35_interface.h"

void LM35_readTemperature(u16* temp)
{
	u16 digitalValue , analogValue; 
	ADC_getDigitalValue(ADC_CHANNEL_0 , &digitalValue);
	analogValue = ((u32)digitalValue * 2560UL)/1024;
	*temp = analogValue/10;
}

void LM35_displayTemperature(u16 temp)
{
	LCD_writeString((u8*)"Temp : ");
	LCD_writeNumber(temp);
	LCD_writeString((u8*)" C");
	//TMR0_setDelay_ms_usingCTC(1000);
	_delay_ms(1000);
	LCD_clear();
}

void LM35_temperatureAction(u16 temp)
{
	if (temp >= 28)
	{
		DCM_on(MOTOR_A , CLOCKWISE);
	}
	else if(temp < 21)
	{
		DCM_off(MOTOR_A);
	}
	
}