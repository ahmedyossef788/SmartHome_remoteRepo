/*
 * SRVM_program.c
 *
 * Created: 9/29/2023 12:15:50 AM
 *  Author: Ahmed
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "TMR1_interface.h"
#include "SRVM_interface.h"


void SRVM_init(void)
{
	DIO_setPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT);
	TMR1_init();
}

void SRVM_on  (s8 angle)
{
	switch(angle)
	{
		case -90:
		TMR1_setFastPWM_usingMode14(5,50);
		break;
		case 0:
		TMR1_setFastPWM_usingMode14(7.5,50);
		break;
		case 90:
		TMR1_setFastPWM_usingMode14(10,50);
		break;
	}
	TMR1_start();
}
void SRVM_off (void)
{
	TMR1_stop();
}