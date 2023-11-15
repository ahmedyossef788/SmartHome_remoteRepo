/*
 * KPD_config.h
 *
 * Created: 9/1/2023 8:17:56 PM
 *  Author: Kareem Hussein
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_


           /* MACROS FOR KPD ROWS PORTS & PINS CONFIGURATION */
					  
//input
#define KPD_ROW0_PORT            DIO_PORTD   
#define KPD_ROW0_PIN             DIO_PIN3
#define KPD_ROW1_PORT            DIO_PORTD     
#define KPD_ROW1_PIN             DIO_PIN4
#define KPD_ROW2_PORT            DIO_PORTC  
#define KPD_ROW2_PIN             DIO_PIN2
#define KPD_ROW3_PORT            DIO_PORTC  
#define KPD_ROW3_PIN             DIO_PIN3  

          /* MACROS FOR KPD COLUMNS PORTS & PINS CONFIGURATION */
		  
//output			
#define KPD_COL0_PORT            DIO_PORTC
#define KPD_COL0_PIN             DIO_PIN4
#define KPD_COL1_PORT            DIO_PORTC
#define KPD_COL1_PIN             DIO_PIN5
#define KPD_COL2_PORT            DIO_PORTC
#define KPD_COL2_PIN             DIO_PIN6
#define KPD_COL3_PORT            DIO_PORTC
#define KPD_COL3_PIN             DIO_PIN7


#define KPD_KEYS  {{'1','2','3','A'},\
                   {'4','5','6','B'},\
                   {'7','8','9','C'},\
                   {'*','0','#','D'}}
 
 
#endif /* KPD_CONFIG_H_ */