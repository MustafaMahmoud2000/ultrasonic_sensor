#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_macros.h"
unsigned short a,b,c;
void TIMER_CTC_INIT(void)
{
	sei();
	SET_BIT(TCCR0,CS00);//clock
	SET_BIT(TCCR0,CS02);//clock
	SET_BIT(TCCR0,WGM01);//mode
	OCR0=80;
	SET_BIT(TIMSK,OCIE0);//enable
}
void TIMER_WAVA_NONPWM(void)
{
	SET_BIT(DDRB,3);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	OCR0=64;
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}	
void TIMER_PWM_phase_correct(void)
{
	SET_BIT(DDRB,3);
	SET_BIT(TCCR0,WGM00);
	OCR0=64;
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
}
void TIMER2_overflow_interrupt(void)
{
	SET_BIT(ASSR,AS2);
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	sei();
	SET_BIT(TIMSK,TOIE2);
}
// void Timer1_capture_unit(void)
// {
// 	//unsigned short a,b,c;
// 	
// 	TCCR1A=0;
// 	CLEAR_BIT(TIFR,ICF1);
// 	SET_BIT(TCCR1B,CS10);
// 	SET_BIT(TCCR1B,ICNC1);
// 	SET_BIT(TCCR1B,ICES1);
// 	while(READ_BIT(TIFR,ICF1)==0);
// 	a=ICR1;
// 	CLEAR_BIT(TIFR,ICF1);
// 	SET_BIT(TCCR1B,CS10);
// 	SET_BIT(TCCR1B,ICNC1);
// 	while(READ_BIT(TIFR,ICF1)==0);
// 	b=ICR1;
// 	CLEAR_BIT(TIFR,ICF1);
// 	SET_BIT(TCCR1B,CS10);
// 	SET_BIT(TCCR1B,ICNC1);
// 	SET_BIT(TCCR1B,ICES1);
// 	while(READ_BIT(TIFR,ICF1)==0);
// 	c=ICR1;
// 	CLEAR_BIT(TIFR,ICF1);
// 	TCCR1B=0;
// }
