/*
 * ADC_program.c
 *
 * Created: 9/8/2023 11:10:31 PM
 *  Author: Karim Mostafa
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"


/* MCAL */
#include "ADC_interface.h"
#include "ADC_private.h"


void ADC_init(u8 referenceVolt)
{
	switch(referenceVolt)
	{
		case ADC_REFERENCE_AVCC:
		// Select Vref = AVCC
	     SET_BIT(ADMUX,REFS0);
	     CLR_BIT(ADMUX,REFS1);
		break;
		
		case ADC_REFERENCE_AREF:
		// Select Vref = AREF
	     CLR_BIT(ADMUX,REFS0);
	     CLR_BIT(ADMUX,REFS1);
		break;
		
		case ADC_REFERENCE_INTRNAL:
		// Select Vref = 2.56V internal
	     SET_BIT(ADMUX,REFS0);
	     SET_BIT(ADMUX,REFS1);
		break;
	}
	
	// Select Right Adjustment
	CLR_BIT(ADMUX,ADLAR);
	
	// Single Conversation Mode
	CLR_BIT(ADCSRA,ADATE);
	
	//Disable ADC Interrupt 
	CLR_BIT(ADCSRA,ADIE);
	
	// Prescaler 128 For 16MHZ (125 KHZ)
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	
	// ADC Enable
	SET_BIT(ADCSRA,ADEN);
}


void ADC_getDigitalValue(u8 channelNum,u16* digitalValue)
{
	if((digitalValue != NULL)&&(channelNum<32))
	{
		//Clear ADMUX Channel Bits
	    ADMUX &= 0xE0; //0b11100000
	    
	    // Select Channel Number
	    ADMUX |= channelNum;
	    
	    // Start Conversition
		SET_BIT(ADCSRA,ADSC);
		
		// Monitor ADC Flag 
		while(0 == GET_BIT(ADCSRA,ADIF));
		
		// Clear Flag(write one to clear)
		SET_BIT(ADCSRA,ADIF);
		
		*digitalValue = ADC_u16;
	}
}