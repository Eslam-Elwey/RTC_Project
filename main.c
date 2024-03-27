
/******************** Autor   : Eslam ELwey  ********************/
/******************** Project : RTC 		 ********************/

#define F_CPU		16000000UL
#include <util/delay.h>

#include "Std_Types.h"
#include "Bit_Math.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "Timers_Int.h"
#include "UART_Int.h"
#include "I2C_Int.h"
#include "RTC_Int.h"


static void Timer0_Func (void) ;

static char *month_arr[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"} ;

static char *week_arr[7] = {"SUN","MON","TUE","WED","THU","FRI","SAT"} ;
	
time_t time_val =
{
	48,59 ,11,_12_HOUR_FORMAT_PM
};
		
date_t date_val =
{
	SUNDAY , 31 ,12,23
};
		

static volatile u8 complete_flag = 1 ;
		

int main(void)
{
	DIO_Init();
	
	LCD_Init() ;
	
	RTC_Init() ;

	RTC_Set_Time(&time_val);
	
	RTC_Set_Date(&date_val);
	
	Timer0_Init(TIMER0_NORMAL_MODE,Timer0_PRESCALER_CLK_1024);
	
	Timer0_SET_OVF_Call_Back(&Timer0_Func);
	
	TIMER0_WRITE_VALUE(247) ;
	
	TIMER0_OVER_FLOW_INTERRUPT_ENABLE()	;
	
	GLOBAL_INTERRUPT_ENABLE() ;

	LCD_Write_String_Cursor(1,1,(u8*)"TIME:");
	
	LCD_Write_String_Cursor(2,1,(u8*)"DATE:");
	
	LCD_Write_String_Cursor(3,1,(u8*)"DAY :");
	
	while (1)
	{
			
 		if (1==complete_flag)
 		{
 			complete_flag = 0 ;
			
			RTC_Get_Time(&time_val);
			
			LCD_Clear_Cursor(4,15,2);
			
			
			RTC_Get_Date(&date_val) ;
			
			
			/*Time */
			LCD_Set_Cursor(1,6);
			LCD_Write_Number_2_Digits(time_val.hours);
			LCD_Write_Character(':');
			LCD_Write_Number_2_Digits(time_val.minutes);
			LCD_Write_Character(':');
			LCD_Write_Number_2_Digits(time_val.seconds);
			
			LCD_Set_Cursor(1,15) ;
			if (time_val.hour_form ==_12_HOUR_FORMAT_AM)
			{
				LCD_Write_String((u8*)"AM");
			}
			else if (time_val.hour_form ==_12_HOUR_FORMAT_PM)
			{
				LCD_Write_String((u8*)"PM");
			}
			else
			{
				LCD_Write_String((u8*)"  ");
			}
			
			/*Date*/
			LCD_Set_Cursor(2,6);
			LCD_Write_Number_2_Digits(date_val.date_no);
			LCD_Write_Character('/');
			LCD_Write_String((u8*)month_arr[date_val.month-1]);
			LCD_Write_Character('/');
			LCD_Write_Number_2_Digits(date_val.year);
			
			/*DAY*/
			LCD_Set_Cursor(3,6);
			LCD_Write_String((u8*)week_arr[date_val.day-1]);
		 }
	}
	
}

static void Timer0_Func (void)
{
	static u8 counter = 0 ;
	
	counter++ ;
	
	if (62 == counter)
	{
		TIMER0_WRITE_VALUE(247) ;
		complete_flag = 1 ;
		counter = 0 ; 
	}
	
	
	

}