/*
 * LM35_interface.h
 *
 * Created: 10/23/2023 5:51:55 PM
 *  Author: MUSTA
 */ 


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

void LM35_readTemperature(u16* temp);
void LM35_displayTemperature(u16 temp);
void LM35_temperatureAction(u16 temp);

#endif /* LM35_INTERFACE_H_ */