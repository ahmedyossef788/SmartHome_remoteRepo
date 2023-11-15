/*
 * lamp_test.c
 *
 * Created: 10/22/2023 8:28:00 PM
 * Author : ahmed
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"


/* HAL */


#include "LCD_interface2.h"
#include "LM35_interface.h"
#include "DCM_interface.h"
#include "ADC_interface.h"



int main(void)
{
    /* Replace with your application code */

	DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);
	LCD_init2();
	ADC_init(ADC_REFERENCE_INTRNAL);
	DCM_init(MOTOR_A);
	u16 temp;
    while (1) 
    {
		LM35_readTemperature(&temp);
		LM35_displayTemperature(temp);
		LM35_temperatureAction(temp);
    }
}

