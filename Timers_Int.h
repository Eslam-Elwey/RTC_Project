
#ifndef TIMERS_INT_H_
#define TIMERS_INT_H_

#include "MemMap.h"

#define FREE_RTOS_USED							1
#define FREE_RTOS_UNUSED						0

/* FREE_RTOS_USED - FREE_RTOS_UNUSED 
   to remove ISR_Func In Timers Driver if 
   Free RTOS used
*/
#define FREE_RTOS_STATUS		FREE_RTOS_UNUSED		

/*******************************************************************************************/
/* Timer0 Driver */
/********************************** Macro Funcs **************************************/

#define TIMER0_OVER_FLOW_INTERRUPT_ENABLE()				(SET_BIT(TIMSK,TOIE0))
#define TIMER0_OVER_FLOW_INTERRUPT_DISABLE()			(CLR_BIT(TIMSK,TOIE0))

#define TIMER0_COMPARE_MATCH_INTERRUPT_ENABLE()			(SET_BIT(TIMSK,OCIE0))
#define TIMER0_COMPARE_MATCH_INTERRUPT_DISABLE()		(CLR_BIT(TIMSK,OCIE0))

#define TIMER0_WRITE_VALUE(time_val)					(TCNT0 = time_val)
#define TIMER0_READ_VALUE(ptime_val)					(*(ptime_val) = TCNT0)

#define	TIMER0_OC0_WRITE_VALUE(OC0_val)					((OCR0) = (OC0_val))
#define TIMER0_OC0_READ_VALUE(POC0_val)					(*(POC0_val) = OCR0)

#define TIMER0_FORCE_OUTPUT_COMPARE_ENABLE()			(SET_BIT(TCCR0,FOC0))
#define TIMER0_FORCE_OUTPUT_COMPARE_DISABLE()			(CLEAR_BIT(TCCR0,FOC0))

/*******************************************************************************************/
typedef enum
{
	TIMER0_NORMAL_MODE = 0 ,
	TIMER0_PWM_PHASE_CORRECT ,
	TIMER0_CTC_MODE ,
	TIMER0_FAST_PWM_MODE
}Timer0_modes_t;

typedef enum
{
	Timer0_NO_CLK_SRC_TIMER_OFF = 0 ,
	Timer0_PRESCALER_CLK_NO_SCALER ,
	Timer0_PRESCALER_CLK_8,
	Timer0_PRESCALER_CLK_64,
	Timer0_PRESCALER_CLK_256 ,
	Timer0_PRESCALER_CLK_1024,
	Timer0_EXTERNAL_CLK_FALLING_EDGE,
	Timer0_EXTERNAL_CLK_RISING_EDGE
	
}Timer0_Prescaler_t;

typedef enum
{
	Timer0_OC0_DISCONNECTED = 0 ,
	Timer0_OC0_TOGGLE_COMPARE_MATCH ,
	Timer0_OC0_CLEAR_COMPARE_MATCH ,
	Timer0_OC0_SET_COMPARE_MATCH
}Timer0_OC0_Mode_t;


/*******************************************************************************************/

void Timer0_Init(Timer0_modes_t mode , Timer0_Prescaler_t prescaler);
void Timer0_OC0_Mode(Timer0_OC0_Mode_t mode);
void Timer0_SET_OVF_Call_Back(void (*lpf)(void));
void Timer0_SET_Com_match_Call_Back(void (*lpf)(void));

/*******************************************************************************************/

/* Timer1 Driver */
/********************************** Macro Funcs **************************************/

#define TIMER1_OVER_FLOW_INTERRUPT_ENABLE()					(SET_BIT(TIMSK,TOIE1))
#define TIMER1_OVER_FLOW_INTERRUPT_DISABLE()				(CLR_BIT(TIMSK,TOIE1))

#define TIMER1_COMPARE_A_MATCH_INTERRUPT_ENABLE()			(SET_BIT(TIMSK,OCIE1A))
#define TIMER1_COMPARE_A_MATCH_INTERRUPT_DISABLE()			(CLR_BIT(TIMSK,OCIE1A))

#define TIMER1_COMPARE_B_MATCH_INTERRUPT_ENABLE()			(SET_BIT(TIMSK,OCIE1B))
#define TIMER1_COMPARE_B_MATCH_INTERRUPT_DISABLE()			(CLR_BIT(TIMSK,OCIE1B))

#define TIMER1_ICU_INTERRUPT_ENABLE()						(SET_BIT(TIMSK,TICIE1))
#define TIMER1_ICU_INTERRUPT_DISABLE()						(CLR_BIT(TIMSK,TICIE1))

#define TIMER1_WRITE_VALUE(time_val)						(TCNT1 = time_val)
#define TIMER1_READ_VALUE(ptime_val)						(*(ptime_val) = TCNT1)

#define	TIMER1_OC1A_WRITE_VALUE(OC1A_val)					(OCR1A = OC1A_val)
#define TIMER1_OC1A_READ_VALUE(POC1A_val)					(*(POC1A_val) = OCR1A)

#define	TIMER1_ICU_WRITE_VALUE(ICU_val)						(ICR1 = ICU_val)
#define TIMER1_ICU_READ_VALUE(PICU_val)						(*(PICU_val) = ICR1)

#define	TIMER1_OC1B_WRITE_VALUE(OC1B_val)					(OCR1B = OC1B_val)
#define TIMER1_OC1B_READ_VALUE(POC1B_val)					(*(POC1B_val) = OCR1B)

#define TIMER1_ICU_NOISE_CANCELLER_ENABLE()					(SET_BIT(TCCR1B,ICNC1))
#define TIMER1_ICU_NOISE_CANCELLER_DISABLE()				(CLR_BIT(TCCR1B,ICNC1))

#define TIMER1_FORCE_OUTPUT_COMPARE_A_ENABLE()				(SET_BIT(TCCR1A,FOC1A))
#define TIMER1_FORCE_OUTPUT_COMPARE_A_DISABLE()				(CLR_BIT(TCCR1A,FOC1A))

#define TIMER1_FORCE_OUTPUT_COMPARE_B_ENABLE()				(SET_BIT(TCCR1A,FOC1B))
#define TIMER1_FORCE_OUTPUT_COMPARE_B_DISABLE()				(CLR_BIT(TCCR1A,FOC1B))

/*******************************************************************************************/

typedef enum
{
	TIMER1_NO_CLK_OFF = 0 ,
	TIMER1_NO_PRESCALING_CLK_1 ,
	TIMER1_PRESCALER_CLK_8 ,
	TIMER1_PRESCALER_CLK_64 ,
	TIMER1_PRESCALER_CLK_256 ,
	TIMER1_PRESCALER_CLK_1024 ,
	TIMER1_EXT_CLK_FALLING_EDGE ,
	TIMER1_EXT_CLK_RISING_EDGE
}Timer1_Prescaler_t;

typedef enum
{
	TIMER1_NORMAL_MODE = 0 ,
	TIMER1_PWM_PHASE_CR_8_BIT_TOP ,
	TIMER1_PWM_PHASE_CR_9_BIT_TOP ,
	TIMER1_PWM_PHASE_CR_10_BIT_TOP ,
	TIMER1_CTC_OCR1A_TOP ,
	TIMER1_FAST_PWM_8_BIT_TOP ,
	TIMER1_FAST_PWM_9_BIT_TOP ,
	TIMER1_FAST_PWM_10_BIT_TOP ,
	TIMER1_PWM_PHASE_FREQ_ICR1_TOP ,
	TIMER1_PWM_PHASE_FREQ_OCR1A_TOP ,
	TIMER1_PWM_PHASE_CR_ICR1_TOP ,
	TIMER1_PWM_PHASE_CR_OCR1A_TOP ,
	TIMER1_CTC_ICR1_TOP ,
	TIMER1_FAST_PWM_ICR1_TOP = 14 ,
	TIMER1_FAST_PWM_OCR1A_TOP
}Timer1_mode_t;

typedef enum
{
	ICES1_FALLING=0 ,
	ICES1_RISING
}Timer1_ICU_Edge_t;

typedef enum
{
	TIMER1_OC1A_DISCONNECTED = 0  ,
	TIMER1_OC1A_TOGGLE,
	TIMER1_OC1A_CLEAR,
	TIMER1_OC1A_SET,
}Timer1_OC1A_mode_t;

typedef enum
{
	TIMER1_OC1B_DISCONNECTED = 0  ,
	TIMER1_OC1B_TOGGLE,
	TIMER1_OC1B_CLEAR,
	TIMER1_OC1B_SET,
}Timer1_OC1B_mode_t;

/***************************** Timer1 Interfaces *************************************/

void Timer1_Init (Timer1_mode_t mode , Timer1_Prescaler_t prescaler );
void Timer1_Set_OC1A_Mode (Timer1_OC1A_mode_t oc1a_mode);
void Timer1_Set_OC1B_Mode (Timer1_OC1B_mode_t oc1b_mode);
void Timer1_Set_OVF_Call_Back(void (*pf)(void));
void Timer1_Set_ComA_Match_Call_Back(void (*pf)(void));
void Timer1_Set_ComB_Match_Call_Back(void (*pf)(void));
void Timer1_Set_ICU_Call_Back(void (*pf)(void));
void Timer1_ICU_Edge_Mode (Timer1_ICU_Edge_t edge_mode);

/*******************************************************************************************/
/* Timer2 Driver */

/********************************** Macro Funcs **************************************/

#define TIMER2_OVER_FLOW_INTERRUPT_ENABLE()				(SET_BIT(TIMSK,TOIE2))
#define TIMER2_OVER_FLOW_INTERRUPT_DISABLE()			(CLR_BIT(TIMSK,TOIE2))

#define TIMER2_COMPARE_MATCH_INTERRUPT_ENABLE()			(SET_BIT(TIMSK,OCIE2))
#define TIMER2_COMPARE_MATCH_INTERRUPT_DISABLE()		(CLR_BIT(TIMSK,OCIE2))

#define TIMER2_WRITE_VALUE(time_val)					(TCNT2 = time_val)
#define TIMER2_READ_VALUE(ptime_val)					(*(ptime_val) = TCNT2)

#define	TIMER2_OC2_WRITE_VALUE(OC2_val)					(OCR2 = OC2_val)
#define TIMER2_OC2_READ_VALUE(POC2_val)					(*(POC2_val) = OCR2)

#define TIMER2_FORCE_OUTPUT_COMPARE_ENABLE()			(SET_BIT(TCCR2,FOC2))
#define TIMER2_FORCE_OUTPUT_COMPARE_DISABLE()			(CLR_BIT(TCCR2,FOC2))

/*******************************************************************************************/
typedef enum
{
	TIMER2_NO_CLK_OFF = 0 ,
	TIMER2_NO_PRESCALING_CLK_1 ,
	TIMER2_PRESCALER_CLK_8 ,
	TIMER2_PRESCALER_CLK_32 ,
	TIMER2_PRESCALER_CLK_64 ,
	TIMER2_PRESCALER_CLK_128 ,
	TIMER2_PRESCALER_CLK_266 ,
	TIMER2_PRESCALER_CLK_1024
}Timer2_Prescaler_t;

typedef enum
{
	TIMER2_NORMAL_MODE = 0 ,
	TIMER2_PWM_PHASE_CORRECT ,
	TIMER2_CTC_MODE ,
	TIMER2_FAST_PWM_MODE
}Timer2_modes_t;

typedef enum
{
	Timer2_OC2_DISCONNECTED = 0 ,
	Timer2_OC2_TOGGLE_COMPARE_MATCH ,
	Timer2_OC2_CLEAR_COMPARE_MATCH ,
	Timer2_OC2_SET_COMPARE_MATCH
}Timer2_OC2_Mode_t;



/***************************** Timer2 Interfaces *************************************/

void Timer2_Init(Timer2_modes_t mode , Timer2_Prescaler_t prescaler);
void Timer2_OC2_Mode(Timer2_OC2_Mode_t mode);
void Timer2_SET_OVF_Call_Back(void (*pf)(void));
void Timer2_SET_Com_match_Call_Back(void (*pf)(void));

/*******************************************************************************************/




#endif /* TIMERS_INT_H_ */