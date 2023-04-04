/*
 * Timer1_interface.h
 *
 *  Created on: Mar 2, 2023
 *      Author: Ahmed Hesham
 */

#ifndef TIMER_1_TIMER1_INTERFACE_H_
#define TIMER_1_TIMER1_INTERFACE_H_

void M_void_Timer1_Init (void);
void M_void_Timer1_IC_Interrupt_Enable(void);
void M_void_Timer1_IC_Interrupt_Disable(void);
void M_void_Timer1_ICU_Interrupt_SetCallBack(void(*plocalToFunc)(void));
void M_void_Timer1_zero(void);





typedef enum {
	RISING,
	FALLING

}Timer1_ICU_Mode_t;




#endif /* TIMER_1_TIMER1_INTERFACE_H_ */
