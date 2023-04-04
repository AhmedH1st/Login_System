#include "STD_TYPES.h"
#include "util/delay.h"
#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "LCD_interface.h"
#include "GI.h"
#include "LCD_interface.h"
#include "Keypad_interface.h"
#include "Timer1_interface.h"
#include "UltraSonic_interface.h"
#include "Login_System.h"
#include "Call_Back_functions.h"

const u16 SystemPassword=1997;

u16 EnteredPassword;
u8 TrialCounter;


void Login_System_init (void)
{
	Port_Init(PORT_Config_Arr);
	H_LCD_Init();
	GI_Enable();
	M_void_Timer1_Init();

	M_void_Timer1_ICU_Interrupt_SetCallBack(Timer0_OCM_Int);


	H_LCD_Writestr("WELCOME IN LOGIN");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2,DIgit_5);
	H_LCD_Writestr("SYSTEM PROJECT");
	_delay_ms(2000);
	H_LCD_ClearDisplay();
	H_LCD_Writestr("DESIGNED BY:");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2,DIgit_1);
	H_LCD_Writestr("AHMED HESHAM");
	_delay_ms(3000);
	H_LCD_ClearDisplay();

}


void Login_System_Runnable (void)
{
	u8 Exit_flag=0;

	while(1)
	{
		System_stand_by();

		if(System_Ready() == NORESPONSE)
		{
			continue;
		}

		if (System_Enter_Password() == NORESPONSE)
		{
			continue;
		}

		else
		{
			while (TrialCounter < 3)
				{
				if (SystemPassword == EnteredPassword)
					{
						TrialCounter=0;
						H_LCD_ClearDisplay();
						M_DIO_void_setPinValue(Relay, DIO_HIGH);
						H_LCD_Writestr("HEllo AGAIN ^_^");
						H_LCD_GoTOAddress_UsingLine_Col(LINE_2,DIgit_1);
						H_LCD_Writestr("MR.AHMED HESHAM ");
						_delay_ms(2000);
						break;

					}
				else if (TrialCounter < 2)
					{
						TrialCounter++;
						H_LCD_ClearDisplay();
						H_LCD_Writestr("Wrong Password");
						H_LCD_GoTOAddress_UsingLine_Col(LINE_2,DIgit_1);
						H_LCD_Writestr("Please Try Again!");
						_delay_ms(2000);
						EnteredPassword=0;
						System_Enter_Password();
					}
				else if (TrialCounter == 2)
				{
					H_LCD_ClearDisplay();
					for (u8 i=0; i<120; i++)
					{
						_delay_ms(1000);
					}
					TrialCounter=0;
					Exit_flag=1;
					EnteredPassword=0;
				}
				}
			}

		if (Exit_flag == 1)
		{
			break;
		}
		else
		{
			System_Successful_Login();
			break;
		}

	}
}

static void System_stand_by (void)
{

	u16 distance=30;    //initial value
	UltraSonic_Status_t status;

	H_LCD_ClearDisplay();
	EnteredPassword=0;
	while (distance>15)
	{
		M_void_Timer1_IC_Interrupt_Enable();

		status=Ultrasonic_GetRead(&distance);

		M_void_Timer1_IC_Interrupt_Disable();
		_delay_ms(100);
	}
}

static Person_state_t System_Ready (void)
{
	Person_state_t state;
	u8 PB=NO_PRESSED_KEY;
	u32 Run_out_time=0;

	H_LCD_Writestr("Hello There");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2,DIgit_1);
	H_LCD_Writestr("Press Any Key To");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_3,DIgit_1);
	H_LCD_Writestr("Enter Password");

	while((PB == NO_PRESSED_KEY) && (Run_out_time < 35000))
	{
		PB=H_KEYPAD_u8_getPressedKey();
		Run_out_time++;
		_delay_us(1);
	}

	if (PB != NO_PRESSED_KEY)
	{
		state= RESPONSE;
	}
	else
	{
		state= NORESPONSE;
	}
return state;
}


static Person_state_t System_Enter_Password (void)
{
	Person_state_t state;
	u8 PB=NO_PRESSED_KEY;
	u32 Run_out_time=0;

	H_LCD_ClearDisplay();
	H_LCD_Writestr("Enter Your Password");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
	H_LCD_Writestr("Then Press =");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_4, DIgit_1);

while(((PB=H_KEYPAD_u8_getPressedKey()) != '=')  && (Run_out_time<35000))
	{
		if (PB != NO_PRESSED_KEY)
		{
			if(PB>='0' && PB<='9')
			{
				H_LCD_WriteChar('*');
				EnteredPassword=(EnteredPassword*10)+(PB-'0');
			}
			PB=NO_PRESSED_KEY;
		}
		else
		{
			Run_out_time++;
			_delay_us(1);
		}
	}

if (Run_out_time == 35000)
{
	state= NORESPONSE;
}
else
{
	state= RESPONSE;
}

return state;

}


static void System_Successful_Login (void)
{
	u8 PB=NO_PRESSED_KEY;
	H_LCD_ClearDisplay();

	H_LCD_Writestr("Press");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_2, DIgit_1);
	H_LCD_Writestr("1-->LEDS ON");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_3, DIgit_1);
	H_LCD_Writestr("2-->LEDS OFF");


	while(PB != '1'  && PB != '2')
	{
		PB=H_KEYPAD_u8_getPressedKey();

		if (PB == '1')
		{
			M_DIO_void_setPinValue(DIO_PB0, DIO_HIGH);
		}
		else if (PB =='2')
		{
			M_DIO_void_setPinValue(DIO_PB0, DIO_LOW);
		}
	}

	H_LCD_ClearDisplay();

	H_LCD_Writestr("HAVE A GOOD TIME");
	_delay_ms(50000);
	M_DIO_void_setPinValue(Relay, DIO_LOW);
	H_LCD_ClearDisplay();
}
