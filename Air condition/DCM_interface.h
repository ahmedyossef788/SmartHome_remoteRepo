/*
 * DCM_interface.h
 *
 * Created: 10/2/2023 6:07:07 PM
 *  Author: MUSTA
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

#define MOTOR_A					0
#define MOTOR_B					1

#define COUNTER_CLOCKWISE		0
#define CLOCKWISE				1

#define MOTOR_speed_1			25
#define MOTOR_speed_2			50
#define MOTOR_speed_3			75

void DCM_init		   (u8 DCM_ID);
void DCM_on			   (u8 DCM_ID , u8 DCM_direction);
void DCM_onControlSpeed(u8 DCM_ID , u8 DCM_direction , u8 DCM_speed);
void DCM_off		   (u8 DCM_ID);

#endif /* DCM_INTERFACE_H_ */