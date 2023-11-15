/*
 * LCD_config.h
 *
 * Created: 8/26/2023 9:55:43 PM
 *  Author: Karim Mostafa
 */ 


#ifndef LCD_CONFIG2_H_
#define LCD_CONFIG2_H_


#define LCD_RS_PORT        DIO_PORTA
#define LCD_RS_PIN         DIO_PIN6
					      
#define LCD_RW_PORT        DIO_PORTA
#define LCD_RW_PIN         DIO_PIN4

#define LCD_EN_PORT        DIO_PORTA
#define LCD_EN_PIN         DIO_PIN7


#define LCD_D4_PORT         DIO_PORTB
#define LCD_D4_PIN          DIO_PIN0

#define LCD_D5_PORT         DIO_PORTB       
#define LCD_D5_PIN          DIO_PIN1

#define LCD_D6_PORT         DIO_PORTB        
#define LCD_D6_PIN          DIO_PIN2

#define LCD_D7_PORT         DIO_PORTB      
#define LCD_D7_PIN          DIO_PIN3


#endif /* LCD_CONFIG_H_ */