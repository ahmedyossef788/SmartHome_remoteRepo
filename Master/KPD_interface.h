/*
 * KPD_interface.h
 *
 * Created: 9/1/2023 8:17:42 PM
 *  Author: Kareem Hussein
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_


#define KPD_NOT_PRESSED          0xff 


void KPD_init    (void);
void KPD_getValue(u8* returnedValue);


#endif /* KPD_INTERFACE_H_ */