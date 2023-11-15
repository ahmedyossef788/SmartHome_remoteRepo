/*
 * Automated_Door_Control.c
 *
 * Created: 10/1/2023 5:11:53 PM
 * Author :Ahmed
 */ 


//#include "GI_interface.h"
//#include "EXTI_interface.h"



#include "MASTER_APP_interface.h"




int main(void)
{
    master_program();
}











void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	emergency_login();
}
