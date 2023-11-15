/*
 * TMR0_program.c
 *
 * Created: 9/9/2023 10:54:36 PM
 *  Author: Ahmed
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"

static void (*private_pCallBackOVF)(void)=NULL;
static void (*private_pCallBackCTC)(void)=NULL;
volatile static u16   private_ctcCounter;

void TMR0_init (void)
{
#if TMR0_MODE == TMR0_NORMAL_MODE
	// Select Mode = Normal Mode
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	
	// Init Timer With Preload Value
	TCNT0 = TMR0_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK,TOIE0);*/
    
#elif TMR0_MODE == TMR0_CTC_MODE
    // Select Mode = CTC Mode
    CLR_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,WGM01);
	
	// Enable OC Interrupt
	SET_BIT(TIMSK,OCIE0);
#elif TMR0_MODE == TMR0_FAST_PWM_MODE
    // Select Mode = PWM Mode
    SET_BIT(TCCR0,WGM00);
    SET_BIT(TCCR0,WGM01);
	
	//Non INVERTING Mode
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	

#endif
}

void TMR0_start(void)
{
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}

void TMR0_stop(void)
{
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
}


void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u16 ovfCounter=0;
	ovfCounter++;
	
	if (TMR0_OVER_FLOW_COUNTER==ovfCounter)
	{
		TCNT0 = TMR0_PRELOAD_VALUE;
		ovfCounter = 0;
		
		if (private_pCallBackOVF!=NULL)
		{
			private_pCallBackOVF();
		}
		
	}
}

void TMR0_setCallBackOVF(void(*ptrToFun)(void))
{
	if (ptrToFun!=NULL)
	{
		private_pCallBackOVF = ptrToFun;
	}
}

void TMR0_setCallBackCTC(void(*ptrToFun)(void))
{
	if (ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}

void TMR0_setCompareMatchValue(u8 comparevalue)
{
	OCR0 = comparevalue;
}

void TMR0_setDelay_ms_UsingCTC(u16 delay_ms)
{
	OCR0 = 249;
	private_ctcCounter = delay_ms;
}


void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u16 ctcCounter=0;
	ctcCounter++;
	
	if (private_ctcCounter==ctcCounter)
	{
		ctcCounter = 0;
		
		if (private_pCallBackCTC!=NULL)
		{
			private_pCallBackCTC();
		}
		
	}
}

void TMR0_setDutyCycle(u8 dutycycle)
{
	//under condition non inverting fast pwm
	if (dutycycle<=100)
	{
		OCR0 = ((dutycycle*256)/100)-1;
	}
}