/*
 * DCM_program.c
 *
 * Created: 10/2/2023 6:06:49 PM
 *  Author: MUSTA
 */ 

//STD_LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//MCAL_LIB
#include "DIO_interface.h"
#include "DIO_PRIVATE.h"
#include "TMR0_config.h"
#include "TMR0_interface.h"
#include "TMR0_private.h"

//HAL_LIB
#include "DCM_config.h"
#include "DCM_interface.h"

void DCM_init(u8 DCM_ID)
{
	switch(DCM_ID)
	{
		case MOTOR_A:
			DIO_setPinDirection(H_EN1_PORT , H_EN1_PIN , DIO_PIN_OUTPUT);
			DIO_setPinDirection(H_IN1_PORT , H_IN1_PIN , DIO_PIN_OUTPUT);
			DIO_setPinDirection(H_IN2_PORT , H_IN2_PIN , DIO_PIN_OUTPUT);
			DIO_setPinValue	   (H_EN1_PORT , H_EN1_PIN , DIO_PIN_HIGH);
			break;
		
		case MOTOR_B:
			DIO_setPinDirection(H_EN2_PORT , H_EN2_PIN , DIO_PIN_OUTPUT);
			DIO_setPinDirection(H_IN3_PORT , H_IN3_PIN , DIO_PIN_OUTPUT);
			DIO_setPinDirection(H_IN4_PORT , H_IN4_PIN , DIO_PIN_OUTPUT);
			DIO_setPinValue    (H_EN2_PORT , H_EN2_PIN , DIO_PIN_HIGH);
			break;
	}
	
}
void DCM_on(u8 DCM_ID , u8 DCM_direction)
{
	switch(DCM_ID)
	{
		case MOTOR_A:
			switch(DCM_direction)
			{
				case CLOCKWISE:
					DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_HIGH);
					DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
					break;
				case COUNTER_CLOCKWISE:
					DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
					DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_HIGH);
					break;
			}
		break;
		
		case MOTOR_B:
			switch(DCM_direction)
			{
				case CLOCKWISE:
					DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_HIGH);
					DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_LOW);
					break;
				case COUNTER_CLOCKWISE:
					DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_LOW);
					DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_HIGH);
					break;
			}
		break;
	}
}
void DCM_onControlSpeed(u8 DCM_ID , u8 DCM_direction , u8 DCM_speed)
{
	switch(DCM_ID)
	{
		case MOTOR_A:
			switch(DCM_speed)
			{
				case MOTOR_speed_1:
					//Fast PWM Pin Configuration
					DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
					switch(DCM_direction)
					{
						case CLOCKWISE:
							DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_HIGH);
							DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
							TMR0_init();
							TMR0_setDytyCycle(MOTOR_speed_1);
							TMR0_start();
							break;
						case COUNTER_CLOCKWISE:
							DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
							DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_HIGH);
							TMR0_init();
							TMR0_setDytyCycle(MOTOR_speed_1);
							TMR0_start();
							break;
					}
				break;
				
				case MOTOR_speed_2:
					//Fast PWM Pin Configuration
					DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
					switch(DCM_direction)
					{
						case CLOCKWISE:
							DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_HIGH);
							DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
							TMR0_init();
							TMR0_setDytyCycle(MOTOR_speed_2);
							TMR0_start();
							break;
						case COUNTER_CLOCKWISE:
							DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
							DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_HIGH);
							TMR0_init();
							TMR0_setDytyCycle(MOTOR_speed_2);
							TMR0_start();
							break;
					}
				break;
				
				case MOTOR_speed_3:
				//Fast PWM Pin Configuration
				DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
				switch(DCM_direction)
				{
					case CLOCKWISE:
					DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_HIGH);
					DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
					TMR0_init();
					TMR0_setDytyCycle(MOTOR_speed_3);
					TMR0_start();
					break;
					case COUNTER_CLOCKWISE:
					DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
					DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_HIGH);
					TMR0_init();
					TMR0_setDytyCycle(MOTOR_speed_3);
					TMR0_start();
					break;
				}
				break;
			}
			
		break;
		
		case MOTOR_B:
		switch(DCM_speed)
		{
			case MOTOR_speed_1:
				//Fast PWM Pin Configuration
				DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
				switch(DCM_direction)
				{
					case CLOCKWISE:
						DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_HIGH);
						DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_LOW);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_1);
						TMR0_start();
						break;
					case COUNTER_CLOCKWISE:
						DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_LOW);
						DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_HIGH);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_1);
						TMR0_start();
						break;
				}
			break;
			
			case MOTOR_speed_2:
				//Fast PWM Pin Configuration
				DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
				switch(DCM_direction)
				{
					case CLOCKWISE:
						DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_HIGH);
						DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_LOW);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_2);
						TMR0_start();
						break;
					case COUNTER_CLOCKWISE:
						DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_LOW);
						DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_HIGH);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_2);
						TMR0_start();
						break;
				}
			break;
			
			case MOTOR_speed_3:
				//Fast PWM Pin Configuration
				DIO_setPinDirection(DIO_PORTB , DIO_PIN3 , DIO_PIN_OUTPUT);
				switch(DCM_direction)
				{
					case CLOCKWISE:
						DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_HIGH);
						DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_3);
						TMR0_start();
						break;
					case COUNTER_CLOCKWISE:
						DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
						DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_HIGH);
						TMR0_init();
						TMR0_setDytyCycle(MOTOR_speed_3);
						TMR0_start();
						break;
				}
				break;
		}
		break;
	}
	
}
void DCM_off(u8 DCM_ID)
{
	switch(DCM_ID)
	{
		case MOTOR_A:
			DIO_setPinValue(H_IN1_PORT , H_IN1_PIN , DIO_PIN_LOW);
			DIO_setPinValue(H_IN2_PORT , H_IN2_PIN , DIO_PIN_LOW);
			break;
		case MOTOR_B:
			DIO_setPinValue(H_IN3_PORT , H_IN3_PIN , DIO_PIN_LOW);
			DIO_setPinValue(H_IN4_PORT , H_IN4_PIN , DIO_PIN_LOW);
			break;
	}
}
