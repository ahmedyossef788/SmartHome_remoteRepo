/*
 * TMR0_interface.h
 *
 * Created: 9/9/2023 10:55:24 PM
 *  Author: ahmed
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


void TMR0_init (void);
void TMR0_start(void);
void TMR0_stop (void);
void TMR0_setCallBackOVF(void(*ptrToFun)(void));
void TMR0_setCallBackCTC(void(*ptrToFun)(void));
void TMR0_setCompareMatchValue(u8 comparevalue);
void TMR0_setDelay_ms_UsingCTC(u16 delay_ms);
void TMR0_setDutyCycle(u8 dutycycle);

#endif /* TMR0_INTERFACE_H_ */