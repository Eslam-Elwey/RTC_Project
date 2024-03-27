
#include "Std_Types.h"
#include "Bit_Math.h"
#include "MemMap.h"
#include "Timers_Int.h"

/*******************************************************************************************/

static void	(*Timer0_OVF_PFunc) (void);
static void	(*Timer0_CMP_Match_PFunc) (void);

static void	(*Timer2_OVF_PFunc) (void);
static void	(*Timer2_CMP_Match_PFunc) (void);

static void	(*Timer1_OVF_PFunc) (void);
static void	(*Timer1_CMP_A_Match_PFunc) (void);
static void	(*Timer1_CMP_B_Match_PFunc) (void);
static void	(*Timer1_ICU_PFunc) (void);


/*******************************************************************************************/
/* Timer0 */

void Timer0_Init(Timer0_modes_t mode , Timer0_Prescaler_t prescaler)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE :
		CLR_BIT(TCCR0,WGM01);
		CLR_BIT(TCCR0,WGM00);
		break ;
		
		case TIMER0_PWM_PHASE_CORRECT :
		CLR_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		break ;
		
		case TIMER0_CTC_MODE :
		SET_BIT(TCCR0,WGM01);
		CLR_BIT(TCCR0,WGM00);
		break ;
		
		case TIMER0_FAST_PWM_MODE :
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		break ;
	}
	
	TCCR0 &= 0xF8 ;
	TCCR0 |= prescaler ;
	
}

void Timer0_OC0_Mode(Timer0_OC0_Mode_t mode)
{
	switch(mode)
	{
		case Timer0_OC0_DISCONNECTED :
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break ;
		
		case Timer0_OC0_TOGGLE_COMPARE_MATCH :
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break ;
		
		case Timer0_OC0_CLEAR_COMPARE_MATCH :
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break ;
		
		case Timer0_OC0_SET_COMPARE_MATCH :
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break ;
	}

}




void Timer0_SET_OVF_Call_Back(void (*lpf)(void))
{
	Timer0_OVF_PFunc = lpf ;
}

void Timer0_SET_Com_match_Call_Back(void (*lpf)(void))
{
	Timer0_CMP_Match_PFunc = lpf ;
}


ISR (TIMER0_OVF_vect)
{
	if (Timer0_OVF_PFunc!=NULLPTR)
	{
		Timer0_OVF_PFunc();
	}
}

ISR(TIMER0_COMP_vect)
{
	if (Timer0_CMP_Match_PFunc!=NULLPTR)
	{
		Timer0_CMP_Match_PFunc();
	}
}


/*******************************************************************************************/
/* Timer1 */

void Timer1_Init (Timer1_mode_t mode , Timer1_Prescaler_t prescaler )
{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE :
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_CR_8_BIT_TOP :
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_CR_9_BIT_TOP :
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_CR_10_BIT_TOP :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_CTC_OCR1A_TOP :
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_FAST_PWM_8_BIT_TOP :
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_FAST_PWM_9_BIT_TOP :
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_FAST_PWM_10_BIT_TOP :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_FREQ_ICR1_TOP :
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_FREQ_OCR1A_TOP :
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_CR_ICR1_TOP :
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_PWM_PHASE_CR_OCR1A_TOP :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_CTC_ICR1_TOP :
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_FAST_PWM_ICR1_TOP :
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
		case TIMER1_FAST_PWM_OCR1A_TOP :
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break ;
		
	}
	
	TCCR1B &= 0xF8 ;
	TCCR1B |= prescaler ;
}

void Timer1_Set_OC1A_Mode (Timer1_OC1A_mode_t oc1a_mode)
{
	switch (oc1a_mode)
	{
		case TIMER1_OC1A_DISCONNECTED :
		CLR_BIT (TCCR1A , COM1A0);
		CLR_BIT (TCCR1A , COM1A1);
		break;
		
		case TIMER1_OC1A_TOGGLE :
		SET_BIT (TCCR1A , COM1A0);
		CLR_BIT (TCCR1A , COM1A1);
		break;
		
		case TIMER1_OC1A_CLEAR :
		CLR_BIT (TCCR1A , COM1A0);
		SET_BIT (TCCR1A , COM1A1);
		break;
		
		case TIMER1_OC1A_SET :
		SET_BIT (TCCR1A , COM1A0);
		SET_BIT (TCCR1A , COM1A1);
		break;
		
	}
	
	
}

void Timer1_Set_OC1B_Mode (Timer1_OC1B_mode_t oc1b_mode)
{
	
	switch (oc1b_mode)
	{
		case TIMER1_OC1B_DISCONNECTED :
		CLR_BIT (TCCR1A , COM1B0);
		CLR_BIT (TCCR1A , COM1B1);
		break;
		
		case TIMER1_OC1B_TOGGLE :
		SET_BIT (TCCR1A , COM1B0);
		CLR_BIT (TCCR1A , COM1B1);
		break;
		
		case TIMER1_OC1B_CLEAR :
		CLR_BIT (TCCR1A , COM1B0);
		SET_BIT (TCCR1A , COM1B1);
		break;
		
		case TIMER1_OC1B_SET :
		SET_BIT (TCCR1A , COM1B0);
		SET_BIT (TCCR1A , COM1B1);
		break;
		
	}
	
}

void Timer1_Set_OVF_Call_Back(void (*pf)(void))
{
	Timer1_OVF_PFunc = pf ;
}

void Timer1_Set_ComA_Match_Call_Back(void (*pf)(void))
{
	Timer1_CMP_A_Match_PFunc = pf ;
}

void Timer1_Set_ComB_Match_Call_Back(void (*pf)(void))
{
	Timer1_CMP_B_Match_PFunc = pf ;
}

void Timer1_Set_ICU_Call_Back(void (*pf)(void))
{
	Timer1_ICU_PFunc = pf ;
}

void Timer1_ICU_Edge_Mode (Timer1_ICU_Edge_t edge_mode)
{
	switch (edge_mode)
	{
		case ICES1_FALLING :
		CLR_BIT (TCCR1B,ICES1);
		break;
		
		case ICES1_RISING :
		SET_BIT (TCCR1B,ICES1);
		break;
	}
	
}

#if FREE_RTOS_STATUS == FREE_RTOS_UNUSED

ISR(TIMER1_OVF_vect)
{
	if (Timer1_OVF_PFunc!=NULLPTR)
	{
		Timer1_OVF_PFunc();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (Timer1_CMP_A_Match_PFunc!=NULLPTR)
	{
		Timer1_CMP_A_Match_PFunc();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if (Timer1_CMP_B_Match_PFunc!=NULLPTR)
	{
		Timer1_CMP_B_Match_PFunc();
	}
}

ISR(TIMER1_CAPT_vect)
{
	if (Timer1_ICU_PFunc!=NULLPTR)
	{
		Timer1_ICU_PFunc();
	}
}

#endif

/*******************************************************************************************/
/* Timer2 */

void Timer2_Init(Timer2_modes_t mode , Timer2_Prescaler_t prescaler)
{
	switch(mode)
	{
		case TIMER2_NORMAL_MODE :
		CLR_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break ;
		
		case TIMER2_PWM_PHASE_CORRECT :
		SET_BIT(TCCR2,WGM20);
		CLR_BIT(TCCR2,WGM21);
		break ;
		
		case TIMER2_CTC_MODE :
		CLR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break ;
		
		case TIMER2_FAST_PWM_MODE :
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		break ;
	}
	
	TCCR2 &= 0xF8 ;
	TCCR2 |= prescaler ;
}

void Timer2_OC2_Mode(Timer2_OC2_Mode_t mode)
{
	switch (mode)
	{
		case Timer2_OC2_DISCONNECTED :
		CLR_BIT (TCCR2 , COM20);
		CLR_BIT (TCCR2 , COM21);
		break;
		
		case Timer2_OC2_TOGGLE_COMPARE_MATCH :
		SET_BIT (TCCR2 , COM20);
		CLR_BIT (TCCR2 , COM21);
		break;
		
		case Timer2_OC2_CLEAR_COMPARE_MATCH :
		CLR_BIT (TCCR2 , COM20);
		SET_BIT (TCCR2 , COM21);
		break;
		
		case Timer2_OC2_SET_COMPARE_MATCH :
		SET_BIT (TCCR2 , COM20);
		SET_BIT (TCCR2 , COM21);
		break;
		
	}
}

void Timer2_SET_OVF_Call_Back(void (*pf)(void))
{
	Timer2_OVF_PFunc = pf ;
}

void Timer2_SET_Com_match_Call_Back(void (*pf)(void))
{
	Timer2_CMP_Match_PFunc = pf ;
}


ISR(TIMER2_OVF_vect)
{
	if (Timer2_OVF_PFunc!=NULLPTR)
	{
		Timer2_OVF_PFunc();
	}
}

ISR(TIMER2_COMP_vect)
{
	if (Timer2_CMP_Match_PFunc!=NULLPTR)
	{
		Timer2_CMP_Match_PFunc();
	}
}

/*******************************************************************************************/