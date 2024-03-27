/*
 * RTC_Int.h
 *
 * Created: 03/25/2024 9:33:01 PM
 *  Author: Eslam Elwey
 */ 


#ifndef RTC_INT_H_
#define RTC_INT_H_


/* Register Addresses */
#define SECONDS_REGISTER_ADDRESS						0x00
#define MINUTES_REGISTER_ADDRESS						0x01
#define HOURS_REGISTER_ADDRESS							0x02
#define DAY_REGISTER_ADDRESS							0x03
#define DATE_REGISTER_ADDRESS							0x04
#define MONTH_REGISTER_ADDRESS							0x05
#define YEAR_REGISTER_ADDRESS							0x06
#define SQW_REGISTER_ADDRESS							0x07

#define RTC_SLAVE_ADREESS								0b01101000
#define HOURS_DETEMINE_BIT								6

/*****************************************************************************/

/*DATA Types */

typedef enum 
{
	_24_HOUR_FORMAT,
	_12_HOUR_FORMAT_AM,
	_12_HOUR_FORMAT_PM,
}hour_format_t;


typedef enum
{
	SUNDAY=1 ,
	MONDAY ,
	TUESDAY ,
	WEDNESDAY,
	THURSDAY,
	FRIDAY ,
	SATURDAY
}day_t;


typedef struct 
{
	u8 seconds ;
	u8 minutes ;
	u8 hours ;
	hour_format_t hour_form ;
}time_t;


typedef struct
{
	day_t day ;
	u8 date_no ;
	u8 month ;
	u8 year ;
}date_t;

/************************************* Prototypes *************************************/
void RTC_Init(void) ;
void RTC_Set_Time(time_t *time_com) ;
void RTC_Get_Time(time_t *time_com) ;
void RTC_Set_Date(date_t *date_com) ;
void RTC_Get_Date(date_t *date_com) ;


/*************************************************************************************/

#endif /* RTC_INT_H_ */