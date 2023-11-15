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
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "TWI_interface.h"
#include "SPI_interface.h"

/* HAL */
#include "GI_interface.h"
#include "EXTI_interface.h"
#include "TMR0_interface.h"


static counter = 0;

int main(void)
{
	/*PWM PIN*/
	DIO_setPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT);
	
	/*Buttons I/P  */
	DIO_setPinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	//enable global interrupt
	GI_enable();
	EXTI_enable(EXTI_INT0,EXTI_RISING_EDGE);
	EXTI_enable(EXTI_INT2,EXTI_RISING_EDGE);
	
	TMR0_init();
    /* Replace with your application code */
	/* SPI DIRECTION*/
	DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_INPUT);
    /* LED DIRECTION */
	DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);
	
	DIO_setPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_INPUT);    // ADC pin connected to LM35 temeratur sensor
	DIO_setPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);   // TX
	DIO_setPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);    // RX
	SPI_initSlave();
	u8 data=0xff;
    while (1) 
    {
		SPI_tranceive(7,&data);
		switch(data)
		{
			case 1:
			DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
			break;
			case 2:
			DIO_setPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH);
			break;
			case 3:
			DIO_setPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
			break;
			case 4:
			DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
			break;
			case 5:
			DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
			break;
			case 0:
			DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
			break;
			case 6:
			DIO_setPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_LOW);
			break;
			case 7:
			DIO_setPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
			break;
			case 8:
			DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_LOW);
			break;
			case 9:
			DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
			break;
			
		}
		
    }
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	
	u8 state;
	DIO_getPinValue(DIO_PORTD,DIO_PIN2,&state);
	if (state==1)
	{
		if (counter >= 0 && counter <= 100)
		{
			counter +=10 ;
			TMR0_setDutyCycle(counter);
			TMR0_start();
		}

	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	u8 state;
	DIO_getPinValue(DIO_PORTB,DIO_PIN2,&state);
	if (state==1)
	{
		if (counter > 0 && counter <= 100)
		{
			counter -=10;
			TMR0_setDutyCycle(counter);
			TMR0_start();
		}
	}
	

}