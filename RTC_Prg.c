/*
 * RTC_Prg.c
 *
 * Created: 03/25/2024 9:32:45 PM
 *  Author: Eslam Elwey
 */ 

#include "Std_Types.h"
#include "Bit_Math.h"
#include "I2C_Int.h"
#include "RTC_Int.h"
#include "LCD_Int.h"



void RTC_Init(void) 
{
	I2C_Init() ;
	I2C_Master_Gen_Clk_Val_KHZ(100) ;
	I2C_Master_Start_Condition() ;
	I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
	/*Select Seconds Register */
	I2C_Master_Write_Data(SECONDS_REGISTER_ADDRESS) ;
	/*Enable CH */
	I2C_Master_Write_Data(SECONDS_REGISTER_ADDRESS) ;
	I2C_Master_Stop_Condition() ;
}


void RTC_Set_Time(time_t *time_com) 
{
	if (time_com!=NULLPTR)
	{
		u8 i ;
		
		u8 second_d0 = (time_com->seconds)%10 ;
		u8 second_d1 = (time_com->seconds)/10 ;
		
		u8 minute_d0 = (time_com->minutes)%10 ;
		u8 minute_d1 = (time_com->minutes)/10 ;
		
		hour_format_t hour_form = time_com->hour_form ;
		
		u8 hour_d0 = (time_com->hours)%10 ;
		u8 hour_d1 = (time_com->hours)/10 ;
		
		u8 seconds_sent = 0 ;
		u8 minutes_sent = 0 ;
		u8 hours_sent = 0 ;
		
		/*Seconds Handle */
		for (i=0;i<8;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(seconds_sent,i,READ_BIT(second_d0,i));
			}
			else if (i==7)
			{
				CLR_BIT(seconds_sent,i);
			}
			else
			{
				WRITE_BIT_VAL(seconds_sent,i,READ_BIT(second_d1,i-4));
			}
		}
		
		/*Minutes Handle */
		for (i=0;i<7;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(minutes_sent,i,READ_BIT(minute_d0,i));
			}
			
			else
			{
				WRITE_BIT_VAL(minutes_sent,i,READ_BIT(minute_d1,i-4));
			}
		}
		
		/*Hours Format*/
		if (hour_form == _24_HOUR_FORMAT)
		{
			CLR_BIT(hours_sent,HOURS_DETEMINE_BIT);
		}
		else
		{
			SET_BIT(hours_sent,HOURS_DETEMINE_BIT);
		}
		
		
		/*Hours Handle */
		for (i=0;i<6;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(hours_sent,i,READ_BIT(hour_d0,i));
			}
			
			if ((hour_form==_24_HOUR_FORMAT)&&(i>=4))
			{
				WRITE_BIT_VAL(hours_sent,i,READ_BIT(hour_d1,i-4));
			}
			
			else if ((hour_form ==_12_HOUR_FORMAT_AM)&&(i>=4))
			{
				if (i==4)
				{
					WRITE_BIT_VAL(hours_sent,i,READ_BIT(hour_d1,i-4));
				}
				else
				{
					CLR_BIT(hours_sent,i) ;
				}
			}
			else if ((hour_form ==_12_HOUR_FORMAT_PM)&&(i>=4))
			{
				if (i==4)
				{
					WRITE_BIT_VAL(hours_sent,i,READ_BIT(hour_d1,i-4));
				}
				else
				{
					SET_BIT(hours_sent,i) ;
				}
			}
			
		}
		
		I2C_Master_Start_Condition() ;
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
		/*Select Seconds Register */
		I2C_Master_Write_Data(SECONDS_REGISTER_ADDRESS) ;
		
		/*Send Seconds Val*/
		I2C_Master_Write_Data(seconds_sent) ;
		
		/*Send minutes Val*/
		I2C_Master_Write_Data(minutes_sent) ;
		
		/*Send Hours Val*/
		I2C_Master_Write_Data(hours_sent) ;
		
		I2C_Master_Stop_Condition() ;
	}
	
}


void RTC_Get_Time(time_t *time_com) 
{
	if (time_com!=NULLPTR)
	{
		u8 seconds_rec ;
		
		u8 minutes_rec ;
		
		u8 hours_rec ;
		
		I2C_Master_Start_Condition() ;
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
		
		/*Select Seconds Register */
		I2C_Master_Write_Data(SECONDS_REGISTER_ADDRESS) ;
		
		/*Repeated Start */
		I2C_Repeated_Start_Condition();
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_READ);
		
		/* Seconds */
		
		I2C_Master_Read_Val(&seconds_rec);
		
		/*Minutes*/
		
		I2C_Master_Read_Val(&minutes_rec);
		
		/*Hours*/
		I2C_Master_Read_Val(&hours_rec);
		
		/*Repeated Start */
		I2C_Repeated_Start_Condition();
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);

		
		I2C_Master_Stop_Condition() ;
		
		
		
		/*Handle Seconds */
		time_com->seconds = (seconds_rec&0x0F) + ((seconds_rec&0x70)>>4) * 10 ;
		
		/*Handle Minutes */
		time_com->minutes = (minutes_rec&0x0F) + ((minutes_rec&0x70)>>4) * 10 ;
		
		/* Handle Hour Format and hour val */
		if (READ_BIT(hours_rec,HOURS_DETEMINE_BIT))
		{
			if (READ_BIT(hours_rec,HOURS_DETEMINE_BIT-1))
			{
				time_com->hour_form = _12_HOUR_FORMAT_PM ;
				time_com->hours = (hours_rec&0x0F) + ((hours_rec&0x10)>>4) * 10 ;
			}
			else
			{
				time_com->hour_form = _12_HOUR_FORMAT_AM ;
				time_com->hours = (hours_rec&0x0F) + ((hours_rec&0x10)>>4) * 10 ;
			}
		}
		else
		{
			time_com->hours = (hours_rec&0x0F) + ((hours_rec&0x30)>>4) * 10 ;
			time_com->hour_form = _24_HOUR_FORMAT ;
		}
		
	}
	
}


void RTC_Set_Date(date_t *date_com)
{
	
	if (date_com!=NULLPTR)
	{
		u8 i ;
		
		u8 date_d0 = (date_com->date_no)%10 ;
		u8 date_d1 = (date_com->date_no)/10 ;
		
		u8 month_d0 = (date_com->month)%10 ;
		u8 month_d1 = (date_com->month)/10 ;
		
		
		
		u8 year_d0 = (date_com->year)%10 ;
		u8 year_d1 = (date_com->year)/10 ;
		
		u8 date_sent = 0 ;
		u8 month_sent = 0 ;
		u8 year_sent = 0 ;
		
		/*day Handle */
		day_t day_name = date_com->day ;
		
		/*date Handle */
		for (i=0;i<6;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(date_sent,i,READ_BIT(date_d0,i));
			}
			
			else
			{
				WRITE_BIT_VAL(date_sent,i,READ_BIT(date_d1,i-4));
			}
		}
		
		/*month Format*/
		for (i=0;i<5;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(month_sent,i,READ_BIT(month_d0,i));
			}
			
			else
			{
				WRITE_BIT_VAL(month_sent,i,READ_BIT(month_d1,i-4));
			}
		}
		
		/*year Format*/
		for (i=0;i<8;i++)
		{
			if (i<4)
			{
				WRITE_BIT_VAL(year_sent,i,READ_BIT(year_d0,i));
			}
			
			else
			{
				WRITE_BIT_VAL(year_sent,i,READ_BIT(year_d1,i-4));
			}
		}
		
		
		I2C_Master_Start_Condition() ;

		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
		/*Select Seconds Register */
		I2C_Master_Write_Data(DAY_REGISTER_ADDRESS) ;
		
		/*Send day name */
		I2C_Master_Write_Data(day_name) ;
		
		/*Send day Val*/
		I2C_Master_Write_Data(date_sent) ;
		
		/*Send month Val*/
		I2C_Master_Write_Data(month_sent) ;
		
		/*Send year Val*/
		I2C_Master_Write_Data(year_sent) ;
		
		I2C_Master_Stop_Condition() ;
	}
	
	
}


void RTC_Get_Date(date_t *date_com) 
{
	if (date_com!=NULLPTR)
	{
		u8 date_rec ;
		
		u8 month_rec ;
		
		u8 year_rec ;
		
		day_t day_rec ;
		
		
		/*Receive*/
		I2C_Master_Start_Condition() ;
		
		
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
		
		
		/*Select Seconds Register */
		I2C_Master_Write_Data(DAY_REGISTER_ADDRESS) ;
	
		
		/*Repeated Start */
		I2C_Repeated_Start_Condition();
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_READ);
		
		/*Day*/
		I2C_Master_Read_Val(&day_rec);
		
		/*Date */
		I2C_Master_Read_Val(&date_rec);
		
		/*Month*/
		I2C_Master_Read_Val(&month_rec);
		
		/*Year*/
		I2C_Master_Read_Val(&year_rec);
		
		/*Repeated Start */
		I2C_Repeated_Start_Condition();
		
		I2C_Master_Select_Slave_address(RTC_SLAVE_ADREESS,MASTER_WRITE);
		
		
		/*Select Seconds Register */
		I2C_Master_Write_Data(DAY_REGISTER_ADDRESS) ;
		
		
		I2C_Master_Stop_Condition() ;
		
		
		
		/* Handle Day */
		date_com->day = day_rec ;
		
		/* Handle Date */
		date_com->date_no =(date_rec&0x0F) + ((date_rec&0x30)>>4) * 10 ;
		
		/* Handle month */
		date_com->month =(month_rec&0x0F) + ((month_rec&0x10)>>4) * 10 ;
		
		/* Handle year */
		date_com->year =(year_rec&0x0F) + ((year_rec&0xF0)>>4) * 10 ;
		
	}

}