#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "Mcu_HW.h"
#include "avr/interrupt.h"
#include "Timer1_interface.h"

/*#include "LCD_interface.h"
#include "util/delay.h"*/


static void (*PTOFUNC_ICU)(void);


void M_void_Timer1_Init (void)
{
	/*****Set to work on normal mode .. and maybe complete the driver whin have time*****/
	TCCR1A=0;         //normal mode


	TCCR1B=0x43;      //normal mode with /64 scaler so tick time=4us and ICU set to capture rising edge(initial)

}




void M_void_Timer1_IC_Interrupt_Enable(void)
{
	SET_BIT(TIMSK,TICIE1);
}

void M_void_Timer1_IC_Interrupt_Disable (void)
{
	CLR_BIT(TIMSK,TICIE1);
}

void M_void_Timer1_zero(void)
{
	TCNT1=0;
}




void M_void_Timer1_ICU_Interrupt_SetCallBack (void(*plocalToFunc)(void))
{
	PTOFUNC_ICU=plocalToFunc;
}






ISR(TIMER1_CAPT_vect)
{
	PTOFUNC_ICU();
}
