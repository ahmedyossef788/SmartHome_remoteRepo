/*
 * DIO_Program.c
 *
 * Created: 8/19/2023 11:36:54 PM
 *  Author: Ahmed
 */ 

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "DIO_private.h"

void DIO_setPinDirection(u8 PortId, u8 PinId, u8 PinDirection)
{
	if((PortId<=3) && (PinId<=7) && ((PinDirection==DIO_PIN_OUTPUT)||(PinDirection==DIO_PIN_INPUT)))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(PinDirection == DIO_PIN_OUTPUT)
			{
				SET_BIT(DDRA,PinId);
			}
			else
			{
				CLR_BIT(DDRA,PinId);
			}
			break;
			
			case DIO_PORTB:
			if(PinDirection == DIO_PIN_OUTPUT)
			{
				SET_BIT(DDRB,PinId);
			}
			else
			{
				CLR_BIT(DDRB,PinId);
			}
			break;
			
			case DIO_PORTC:
			if(PinDirection == DIO_PIN_OUTPUT)
			{
				SET_BIT(DDRC,PinId);
			}
			else
			{
				CLR_BIT(DDRC,PinId);
			}
			break;
			
			case DIO_PORTD:
			if(PinDirection == DIO_PIN_OUTPUT)
			{
				SET_BIT(DDRD,PinId);
			}
			else
			{
				CLR_BIT(DDRD,PinId);
			}
			break;
		}
	}
	else
	{
		// DO Nothing
	}
}


void DIO_setPinValue(u8 PortId, u8 PinId, u8 PinValue)
{
	if((PortId<=3) && (PinId<=7) && ((PinValue==DIO_PIN_HIGH)||(PinValue==DIO_PIN_LOW)))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTA,PinId);
			}
			else
			{
				CLR_BIT(PORTA,PinId);
			}
			break;
			
			case DIO_PORTB:
			if(DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTB,PinId);
			}
			else
			{
				CLR_BIT(PORTB,PinId);
			}
			break;
			
			case DIO_PORTC:
			if(DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTC,PinId);
			}
			else
			{
				CLR_BIT(PORTC,PinId);
			}
			break;
			
			case DIO_PORTD:
			if(DIO_PIN_HIGH == PinValue)
			{
				SET_BIT(PORTD,PinId);
			}
			else
			{
				CLR_BIT(PORTD,PinId);
			}
			break;
		}
	}
	else
	{
		// DO Nothing
	}
}


void DIO_togglePinValue(u8 PortId, u8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			TOG_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			TOG_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			TOG_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			TOG_BIT(PORTD,PinId);
			break;
		}
	}
	else
	{
		// DO Nothing
	}
}


void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue)
{
	if((PortId<=3) && (PinId<=7) && (PinValue!= NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PinValue = GET_BIT(PINA,PinId);
			break;
			
			case DIO_PORTB:
			*PinValue = GET_BIT(PINB,PinId);
			break;
			
			case DIO_PORTC:
			*PinValue = GET_BIT(PINC,PinId);
			break;
			
			case DIO_PORTD:
			*PinValue = GET_BIT(PIND,PinId);
			break;
		}
	}
	else
	{
		// DO Nothing
	}
}


void DIO_activePinInPullUpResistance(u8 PortId, u8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			SET_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			SET_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			SET_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			SET_BIT(PORTD,PinId);
			break;
		}
	}
	else
	{
		// DO Nothing
	}
}



/* Port Apis */
void DIO_setPortDirection(u8 PortId, u8 PortDirection)
{
	if((PortId<=3) && ((DIO_PORT_OUTPUT == PortDirection) || (DIO_PORT_INPUT == PortDirection)))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRA = 0xff;
			}
			else
			{
				DDRA = 0x00;
			}
			break;

			case DIO_PORTB:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRB = 0xff;
			}
			else
			{
				DDRB = 0x00;
			}
			break;

			case DIO_PORTC:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRC = 0xff;
			}
			else
			{
				DDRC = 0x00;
			}
			break;

			case DIO_PORTD:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRD = 0xff;
			}
			else
			{
				DDRD = 0x00;
			}
			break;
		}
	}
}


void DIO_setPortValue(u8 PortId, u8 PortValue)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA = PortValue;
			break;

			case DIO_PORTB:
			PORTB = PortValue;
			break;

			case DIO_PORTC:
			PORTC = PortValue;
			break;

			case DIO_PORTD:
			PORTD = PortValue;
			break;
		}
	}
}


void DIO_getPortValue(u8 PortId, u8* PortValue)
{
	if((PortId<=3) && (PortValue != NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PortValue = PINA;
			break;

			case DIO_PORTB:
			*PortValue = PINB;
			break;

			case DIO_PORTC:
			*PortValue = PINC;
			break;

			case DIO_PORTD:
			*PortValue = PIND;
			break;
		}
	}
}


void DIO_togglePortValue(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA = ~PORTA;
			break;

			case DIO_PORTB:
			PORTB = ~PORTB;
			break;

			case DIO_PORTC:
			PORTC = ~PORTC;
			break;

			case DIO_PORTD:
			PORTD = ~PORTD;
			break;
		}
	}
}


void DIO_activePortInPullUpResistance(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA = 0xff;
			break;

			case DIO_PORTB:
			PORTB = 0xff;
			break;

			case DIO_PORTC:
			PORTC = 0xff;
			break;

			case DIO_PORTD:
			PORTD = 0xff;
			break;
		}
	}
}