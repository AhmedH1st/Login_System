#include "Bit_Math.h"
#include "Mcu_HW.h"
#include <util/delay.h>
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "PORT_cfg.h"
#include "LCD_interface.h"
#include "LCD_cfg.h"
#include "Keypad_interface.h"
#include "UltraSonic_interface.h"
#include "Timer1_interface.h"
#include "GI.h"
#include "Call_Back_functions.h"
#include "Login_System.h"

int main (){

	Login_System_init();

	while(1)
	{
		Login_System_Runnable();
	}
}
