#include "STD_TYPES.h"
#include "Mcu_HW.h"
#include "Bit_Math.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "Lm35_interface.h"
#include "util/delay.h"
#include "Timer1_interface.h"

/********VARIABLES RELATED TO ULTRASONIC PROJECT**********/

volatile u8 ICU_flag;
volatile u16 t1,t2;

/***********************************************************/
void Timer0_OCM_Int(void)
{
	if (ICU_flag==0)
	{
		t1=(u16)ICR1;
		ICU_flag=1;
		CLR_BIT(TCCR1B,ICES1);     //make it falling
	}

	else if (ICU_flag==1)
	{
		t2=(u16)ICR1;
		ICU_flag=2;
		SET_BIT(TCCR1B,ICES1);
	}
}




void ADC_Int_Func (void)
{
	u16 reading=0;

	reading=LM35_GetRead();

	/*reading=ADCL;
	reading=(ADCH<<8)|reading;*/

	//H_LCD_ClearDisplay();
	H_LCD_GoTOAddress_UsingLine_Col(LINE_1,0);
	H_LCD_Writestr("    ");
	H_LCD_GoTOAddress_UsingLine_Col(LINE_1,0);
	H_LCD_WriteNum(reading/10);
	H_LCD_WriteChar('.');
	H_LCD_WriteNum(reading%10);
	//_delay_ms(2000);
}

void Timer1_ICU_Int (void)
{

}





void Timer0_OV_Int(void)
{


}







