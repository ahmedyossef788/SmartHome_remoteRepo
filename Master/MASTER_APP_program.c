/*
 * MASTER_APP.c
 *
 * Created: 11/15/2023 10:58:08 AM
 *  Author: Ahmed
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
#include "GI_interface.h"
#include "EXTI_interface.h"


/* HAL */
#include "LCD_interface.h"
#include "KPD_interface.h"

#include "SRVM_interface.h"

#include "MASTER_APP_interface.h"


u8 mode=0xff;
u8 data;


void master_program(void)
{
	/* SPI DIRECTION */
	DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);
	
	/* EXTI DIRECTION */
	DIO_setPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);
	/* LED FOR ALARM */
	DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	/* BUZZER FOR ALARM */
	DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_OUTPUT);
	/* TX DIRECTION */
	DIO_setPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);
	/* RX DIRECTION */
	DIO_setPinDirection(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);
	DIO_setPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	
	UART_init();
	GI_enable();
	EXTI_enable(EXTI_INT0,EXTI_RISING_EDGE);
	LCD_init();
	KPD_init();
	SRVM_init();
	SPI_initMaster();
	EEPROM_init();
	
	u8 counter;
	u8 admin_name[]={'a','d','m','i','n','\0'};
	u8 admin[5];
	EEPROM_writePage(0,admin_name,6);
	EEPROM_readPage(0,admin,5);
	u8 passAdmin[]={'1','5','5','2','\0'};
	u8 pass[4];
	EEPROM_writePage(25,passAdmin,5);
	EEPROM_readPage(25,pass,4);
	u8 user_name[]={'u','s','e','r','\0'};
	u8 user[4];
	EEPROM_writePage(11,user_name,5);
	EEPROM_readPage(11,user,4);
	u8 user_pass[]={'1','4','4','2','\0'};
	u8 pass_user[4];
	EEPROM_writePage(16,user_pass,5);
	EEPROM_readPage(16,pass_user,4);
	
	u8 AdminPass=0xff;
	u8 AdminName=0xff;
	u8 name[5];
	u8 pas[4];
	u8 emergency;
	u8 userPass=0xff;
	u8 userName=0xff;
	
	while (1)
	{
		UART_sendString("Hey,please choose the mode (admin mode enter 1 or user mode enter 2\n\r");
		_delay_ms(500);
		UART_RxChar(&mode);
		LCD_sendChar(mode);
		_delay_ms(500);
		LCD_clear();
		if (mode=='1')             // admin mode
		{
			UART_sendString("Please enter your username:\n\r");
			for (u8 i=0;i<5;i++)
			{
				UART_RxChar(&AdminName);
				name[i]=AdminName;
				LCD_sendChar(AdminName);
			}
			if (name[0]==admin[0]&&name[1]==admin[1]&&name[2]==admin[2]&&name[3]==admin[3]&&name[4]==admin[4])
			{
				_delay_ms(500);
				LCD_clear();
				UART_sendString("Please enter your password:\n\r");
				for (u8 i=0;i<4;i++)
				{
					UART_RxChar(&AdminPass);
					pas[i]=AdminPass;
					LCD_sendChar('*');
				}
				_delay_ms(500);
				LCD_clear();
				if (pas[0]==pass[0]&&pas[1]==pass[1]&&pas[2]==pass[2]&&pas[3]==pass[3])
				{
					Success_Login();
				}
				else
				{
					for (u8 i=0;i<2;i++)
					{
						UART_sendString("Sorry,the password is incorrect \n\r");
						UART_sendString("Please enter your password:\n\r");
						for (u8 i=0;i<4;i++)
						{
							UART_RxChar(&AdminPass);
							pas[i]=AdminPass;
							LCD_sendChar('*');
						}
						_delay_ms(500);
						LCD_clear();
						if (pas[0]==pass[0]&&pas[1]==pass[1]&&pas[2]==pass[2]&&pas[3]==pass[3])
						{
							Success_Login();
							break;
						}
						Theif_Mode();
					}
				}
			}
			else
			{
				for (u8 i=0;i<2;i++)
				{
					UART_sendString("Sorry,the username is incorrect \n\r");
					UART_sendString("Please enter your username:\n\r");
					for (u8 i=0;i<5;i++)
					{
						UART_RxChar(&AdminName);
						name[i]=AdminName;
						LCD_sendChar(AdminName);
					}
					_delay_ms(500);
					LCD_clear();
					if (name[0]==admin[0]&&name[1]==admin[1]&&name[2]==admin[2]&&name[3]==admin[3]&&name[4]==admin[4])
					{
						_delay_ms(500);
						LCD_clear();
						UART_sendString("Please enter your password:\n\r");
						for (u8 i=0;i<4;i++)
						{
							UART_RxChar(&AdminPass);
							pas[i]=AdminPass;
							LCD_sendChar('*');
						}
						_delay_ms(500);
						LCD_clear();
						if (pas[0]==pass[0]&&pas[1]==pass[1]&&pas[2]==pass[2]&&pas[3]==pass[3])
						{
							
							Success_Login();
						}
						else
						{
							for (u8 i=0;i<2;i++)
							{
								UART_sendString("Sorry,the password is incorrect \n\r");
								UART_sendString("Please enter your password:\n\r");
								for (u8 i=0;i<4;i++)
								{
									UART_RxChar(&AdminPass);
									pas[i]=AdminPass;
									LCD_sendChar('*');
								}
								_delay_ms(500);
								LCD_clear();
								if (pas[0]==pass[0]&&pas[1]==pass[1]&&pas[2]==pass[2]&&pas[3]==pass[3])
								{
									Success_Login();
									break;
									
								}
							}
							Theif_Mode();
						}
					}
				}
				Theif_Mode();
			}
		}
		// (user mode)
		else if(mode=='2')
		{
			UART_sendString("Please enter your username:\n\r");
			for (u8 i=0;i<4;i++)
			{
				UART_RxChar(&userName);
				name[i]=userName;
				LCD_sendChar(userName);
			}
			if (name[0]==user[0]&&name[1]==user[1]&&name[2]==user[2]&&name[3]==user[3])
			{
				_delay_ms(500);
				LCD_clear();
				UART_sendString("Please enter your password:\n\r");
				for (u8 i=0;i<4;i++)
				{
					UART_RxChar(&userPass);
					pas[i]=userPass;
					LCD_sendChar('*');
				}
				_delay_ms(500);
				LCD_clear();
				if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
				{
					
					Success_Login_USER();
				}
				else
				{
					for (u8 i=0;i<2;i++)
					{
						UART_sendString("Sorry,the password is incorrect \n\r");
						UART_sendString("Please enter your password:\n\r");
						for (u8 i=0;i<4;i++)
						{
							UART_RxChar(&userPass);
							pas[i]=userPass;
							LCD_sendChar('*');
						}
						_delay_ms(500);
						LCD_clear();
						if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
						{
							Success_Login_USER();
						}
						Theif_Mode();
					}
				}
			}
			else
			{
				for (u8 i=0;i<2;i++)
				{
					UART_sendString("Sorry,the username is incorrect \n\r");
					UART_sendString("Please enter your username:\n\r");
					for (u8 i=0;i<4;i++)
					{
						UART_RxChar(&userName);
						name[i]=userName;
						LCD_sendChar(userName);
					}
					_delay_ms(500);
					LCD_clear();
					if (name[0]==user[0]&&name[1]==user[1]&&name[2]==user[2]&&name[3]==user[3])
					{
						_delay_ms(500);
						LCD_clear();
						UART_sendString("Please enter your password:\n\r");
						for (u8 i=0;i<4;i++)
						{
							UART_RxChar(&AdminPass);
							pas[i]=AdminPass;
							LCD_sendChar('*');
						}
						_delay_ms(500);
						LCD_clear();
						if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
						{
							
							Success_Login_USER();
						}
						else
						{
							for (u8 i=0;i<2;i++)
							{
								UART_sendString("Sorry,the password is incorrect \n\r");
								UART_sendString("Please enter your password:\n\r");
								for (u8 i=0;i<4;i++)
								{
									UART_RxChar(&userPass);
									pas[i]=userPass;
									LCD_sendChar('*');
								}
								_delay_ms(500);
								LCD_clear();
								if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
								{
									Success_Login_USER();
									break;
									
								}
							}
							Theif_Mode();
						}
					}
				}
				Theif_Mode();
			}
		}
		else
		{
			UART_sendString("Sorry, choose from mode 1 or 2 \n\r");
		}

	}
}


void Theif_Mode(void)
{
	UART_sendString("sorry the system blocked\n\r");
	while(1)
	{
		DIO_setPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH);
		DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
	}
}


void Success_Login(void)
{
	UART_sendString("welcome,you are logged in\n\r");
	while (1)
	{
		UART_sendString("To open the door enter 'd' and to close the door enter 'c'\n\r");
		UART_sendString("To on lamp1 enter 1 and to off lamp1 enter 0\n\r");
		UART_sendString("To on lamp2 enter 2 and to off lamp2 enter 6\n\r");
		UART_sendString("To on lamp3 enter 3 and to off lamp3 enter 7\n\r");
		UART_sendString("To on lamp4 enter 4 and to off lamp4 enter 8\n\r");
		UART_sendString("To on lamp5 enter 5 and to off lamp1 enter 9\n\r");
		UART_RxChar(&mode);
		switch(mode)
		{
			case 'd':
			SRVM_on(90);
			LCD_clear();
			LCD_writeString("The door opened");
			break;
			case 'c':
			SRVM_on(0);
			LCD_clear();
			LCD_writeString("The door closed");
			break;
			case '1':
			SPI_tranceive(1,&data);
			if (7==data)
			{
				UART_sendString("Lamp 1 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 1 on");
			}
			break;
			case '2':
			SPI_tranceive(2,&data);
			if (7==data)
			{
				UART_sendString("Lamp 2 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 2 on");
			}
			break;
			case '3':
			SPI_tranceive(3,&data);
			if (7==data)
			{
				UART_sendString("Lamp 3 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 3 on");
			}
			break;
			case '4':
			SPI_tranceive(4,&data);
			if (7==data)
			{
				UART_sendString("Lamp 4 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 4 on");
			}
			break;
			case '5':
			SPI_tranceive(5,&data);
			if (7==data)
			{
				UART_sendString("Lamp 5 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 5 on");
			}
			break;
			case '0':
			SPI_tranceive(0,&data);
			if (7==data)
			{
				UART_sendString("Lamp 1 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 1 off");
			}
			break;
			case '6':
			SPI_tranceive(6,&data);
			if (7==data)
			{
				UART_sendString("Lamp 2 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 2 off");
			}
			break;
			case '7':
			SPI_tranceive(7,&data);
			if (7==data)
			{
				UART_sendString("Lamp 3 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 3 off");
			}
			break;
			case '8':
			SPI_tranceive(8,&data);
			if (7==data)
			{
				UART_sendString("Lamp 4 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 4 off");
			}
			break;
			case '9':
			SPI_tranceive(9,&data);
			if (7==data)
			{
				UART_sendString("Lamp 5 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 5 off");
			}
			break;
		}
	}
}

void Success_Login_USER(void)
{
	UART_sendString("welcome,you are logged in\n\r");
	while (1)
	{
		UART_sendString("To on lamp1 enter 1 and to off lamp1 enter 0\n\r");
		UART_sendString("To on lamp2 enter 2 and to off lamp2 enter 6\n\r");
		UART_sendString("To on lamp3 enter 3 and to off lamp3 enter 7\n\r");
		UART_sendString("To on lamp4 enter 4 and to off lamp4 enter 8\n\r");
		UART_sendString("To on lamp5 enter 5 and to off lamp1 enter 9\n\r");
		UART_RxChar(&mode);
		switch(mode)
		{
			case '1':
			SPI_tranceive(1,&data);
			if (7==data)
			{
				UART_sendString("Lamp 1 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 1 on");
			}
			break;
			case '2':
			SPI_tranceive(2,&data);
			if (7==data)
			{
				UART_sendString("Lamp 2 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 2 on");
			}
			break;
			case '3':
			SPI_tranceive(3,&data);
			if (7==data)
			{
				UART_sendString("Lamp 3 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 3 on");
			}
			break;
			case '4':
			SPI_tranceive(4,&data);
			if (7==data)
			{
				UART_sendString("Lamp 4 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 4 on");
			}
			break;
			case '5':
			SPI_tranceive(5,&data);
			if (7==data)
			{
				UART_sendString("Lamp 5 is on\n\r");
				LCD_clear();
				LCD_writeString("Lamp 5 on");
			}
			break;
			case '0':
			SPI_tranceive(0,&data);
			if (7==data)
			{
				UART_sendString("Lamp 1 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 1 off");
			}
			break;
			case '6':
			SPI_tranceive(6,&data);
			if (7==data)
			{
				UART_sendString("Lamp 2 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 2 off");
			}
			break;
			case '7':
			SPI_tranceive(7,&data);
			if (7==data)
			{
				UART_sendString("Lamp 3 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 3 off");
			}
			break;
			case '8':
			SPI_tranceive(8,&data);
			if (7==data)
			{
				UART_sendString("Lamp 4 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 4 off");
			}
			break;
			case '9':
			SPI_tranceive(9,&data);
			if (7==data)
			{
				UART_sendString("Lamp 5 is off\n\r");
				LCD_clear();
				LCD_writeString("Lamp 5 off");
			}
			break;
		}
	}
}

void emergency_login(void)
{
	u8 state;
	DIO_getPinValue(DIO_PORTD,DIO_PIN2,&state);
	if (state==1)
	{
		u8 data;
		u8 counter;
		u8 pas[4];
		u8 pass_user[4];
		EEPROM_readPage(16,pass_user,4);
		LCD_writeString("Please enter your password to log in");
		for (u8 i=0;i<20;i++)
		{
			_delay_ms(100);
			LCD_shiftRight(1);
		}
		_delay_ms(500);
		LCD_clear();
		LCD_writeString("The password is:");
		LCD_goTo();
		counter = 0;
		for (u8 j=0;j<4;j++)
		{
			while(1)
			{
				KPD_getValue(&data);
				if (data != KPD_NOT_PRESSED)
				{
					pas[counter]=data;
					LCD_sendChar('*');
					counter++;
					break;
				}
			}
		}
		_delay_ms(500);
		LCD_clear();
		if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
		{
			LCD_writeString("Welcome");
			LCD_goTo();
			LCD_writeString("you logged in");
			_delay_ms(500);
			LCD_clear();
			while(1)
			{
				KPD_getValue(&data);
				if (data != KPD_NOT_PRESSED)
				{
					switch (data)
					{
						case '1':
						SPI_tranceive(1,&data);
						if (7==data)
						{
							LCD_clear();
							LCD_writeString("Lamp 1 on");
						}
						break;
						case '2':
						SPI_tranceive(2,&data);
						if (7==data)
						{
							LCD_clear();
							LCD_writeString("Lamp 2 on");
						}
						break;
						case '3':
						SPI_tranceive(3,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 3 on");
						}
						break;
						case '4':
						SPI_tranceive(4,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 4 on");
						}
						break;
						case '5':
						SPI_tranceive(5,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 5 on");
						}
						break;
						case '0':
						SPI_tranceive(0,&data);
						if (7==data)
						{
							UART_sendString("Lamp 1 is off\n\r");
							LCD_clear();
							LCD_writeString("Lamp 1 off");
						}
						break;
						case '6':
						SPI_tranceive(6,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 2 off");
						}
						break;
						case '7':
						SPI_tranceive(7,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 3 off");
						}
						break;
						case '8':
						SPI_tranceive(8,&data);
						if (7==data)
						{
							
							LCD_clear();
							LCD_writeString("Lamp 4 off");
						}
						break;
						case '9':
						SPI_tranceive(9,&data);
						if (7==data)
						{
							LCD_clear();
							LCD_writeString("Lamp 5 off");
						}
						break;
					}
				}
			}
		}
		else
		{
			for (u8 i=0;i<2;i++)
			{
				LCD_writeString("Sorry,");
				LCD_goTo();
				LCD_writeString("Wrong password");
				_delay_ms(500);
				LCD_clear();
				LCD_writeString("PLease try again:");
				LCD_goTo();
				counter = 0;
				for (u8 j=0;j<4;j++)
				{
					while(1)
					{
						KPD_getValue(&data);
						if (data != KPD_NOT_PRESSED)
						{
							pas[counter]=data;
							LCD_sendChar('*');
							counter++;
							break;
						}
					}
				}
				_delay_ms(500);
				LCD_clear();
				if (pas[0]==pass_user[0]&&pas[1]==pass_user[1]&&pas[2]==pass_user[2]&&pas[3]==pass_user[3])
				{
					LCD_writeString("Welcome");
					LCD_goTo();
					LCD_writeString("you logged in");
					_delay_ms(500);
					LCD_clear();
					while(1)
					{
						KPD_getValue(&data);
						if (data != KPD_NOT_PRESSED)
						{
							switch (data)
							{
								case '1':
								SPI_tranceive(1,&data);
								if (7==data)
								{
									LCD_clear();
									LCD_writeString("Lamp 1 on");
								}
								break;
								case '2':
								SPI_tranceive(2,&data);
								if (7==data)
								{
									LCD_clear();
									LCD_writeString("Lamp 2 on");
								}
								break;
								case '3':
								SPI_tranceive(3,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 3 on");
								}
								break;
								case '4':
								SPI_tranceive(4,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 4 on");
								}
								break;
								case '5':
								SPI_tranceive(5,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 5 on");
								}
								break;
								case '0':
								SPI_tranceive(0,&data);
								if (7==data)
								{
									UART_sendString("Lamp 1 is off\n\r");
									LCD_clear();
									LCD_writeString("Lamp 1 off");
								}
								break;
								case '6':
								SPI_tranceive(6,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 2 off");
								}
								break;
								case '7':
								SPI_tranceive(7,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 3 off");
								}
								break;
								case '8':
								SPI_tranceive(8,&data);
								if (7==data)
								{
									
									LCD_clear();
									LCD_writeString("Lamp 4 off");
								}
								break;
								case '9':
								SPI_tranceive(9,&data);
								if (7==data)
								{
									LCD_clear();
									LCD_writeString("Lamp 5 off");
								}
								break;
							}
						}
						
					}
					
				}
				
			}
			LCD_writeString("The system is");
			LCD_goTo();
			LCD_writeString("blocked");
			DIO_setPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH);
			DIO_setPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
		}
	}
	
}