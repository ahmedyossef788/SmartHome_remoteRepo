/*
 * KPD_program.c
 *
 * Created: 9/1/2023 8:17:25 PM
 *  Author: Kareem Hussein
 */ 
 
 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
 
/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "KPD_config.h"


void KPD_init(void)
{
	//ROWS >> input
	DIO_setPinDirection(KPD_ROW0_PORT,KPD_ROW0_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(KPD_ROW1_PORT,KPD_ROW1_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(KPD_ROW2_PORT,KPD_ROW2_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(KPD_ROW3_PORT,KPD_ROW3_PIN,DIO_PIN_INPUT);
	
	//COLS >> output
	DIO_setPinDirection(KPD_COL0_PORT,KPD_COL0_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(KPD_COL1_PORT,KPD_COL1_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(KPD_COL2_PORT,KPD_COL2_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(KPD_COL3_PORT,KPD_COL3_PIN,DIO_PIN_OUTPUT);
	
	//active internal pull up (ROWS initial value are ones)
	DIO_activePinInPullUpResistance(KPD_ROW0_PORT,KPD_ROW0_PIN);
	DIO_activePinInPullUpResistance(KPD_ROW1_PORT,KPD_ROW1_PIN);
	DIO_activePinInPullUpResistance(KPD_ROW2_PORT,KPD_ROW2_PIN);
	DIO_activePinInPullUpResistance(KPD_ROW3_PORT,KPD_ROW3_PIN);
}


void KPD_getValue(u8* returnedValue)
{
	if(returnedValue != NULL)
	{
		*returnedValue = KPD_NOT_PRESSED;
		
		u8 COLOS_PINS [4]={KPD_COL0_PIN ,KPD_COL1_PIN ,KPD_COL2_PIN ,KPD_COL3_PIN};
		u8 COLOS_PORTS[4]={KPD_COL0_PORT,KPD_COL1_PORT,KPD_COL2_PORT,KPD_COL3_PORT};
		u8 ROWS_PINS  [4]={KPD_ROW0_PIN ,KPD_ROW1_PIN ,KPD_ROW2_PIN ,KPD_ROW3_PIN};
		u8 ROWS_PORTS [4]={KPD_ROW0_PORT,KPD_ROW1_PORT,KPD_ROW2_PORT,KPD_ROW3_PORT};
		u8 KPD_keys[4][4]= KPD_KEYS;
		                  
		u8 colsCounter,rowsCounter;
		u8 pinValue,pinFlag=0;
		for(colsCounter=0;colsCounter<4;colsCounter++)
		{
			// Activate Each cols
		    DIO_setPinValue(COLOS_PORTS[colsCounter],COLOS_PINS[colsCounter],DIO_PIN_LOW);
			
			for(rowsCounter=0;rowsCounter<4;rowsCounter++)
			{
				DIO_getPinValue(ROWS_PORTS[rowsCounter],ROWS_PINS[rowsCounter],&pinValue);
				if(0 == pinValue)
				{
					while(0 == pinValue)
					{
						DIO_getPinValue(ROWS_PORTS[rowsCounter],ROWS_PINS[rowsCounter],&pinValue);
					}
					//pressed
					*returnedValue = KPD_keys[rowsCounter][colsCounter];
					pinFlag=1;
					break;
				}
			}
			
			if(1 == pinFlag)
			{
				break;
			}
			// Deactivate current cols
		    DIO_setPinValue(COLOS_PORTS[colsCounter],COLOS_PINS[colsCounter],DIO_PIN_HIGH);
		}
	}
	else
	{
		//DO Nothing
	}
}
