/*
 * ultrasonic_sensor.c
 *
 * Created: 12/4/2023 11:50:15 PM
 *  Author: mustafa mahmoud
 */ 


#include <avr/io.h>
#include "Timre.h"
#include "LCD 8BIT.h"
#include "std_macros.h"
#include "DIO.h"
#define PORT_led (unsigned char)'D'
#define F_CPU 1000000UL
#include <util/delay.h>
int main(void)
{
	vLed_init(PORT_led,0);
	vLed_init(PORT_led,1);
	unsigned short a,b,distance,high;
	LCD_INIT();
	vDIO_SET_BIT_DIR('c',0,1);
    while(1)
    {
		TCCR1A=0;
		TIFR=1<<ICF1;
		vDIO_WRITE_BIT('c',0,1);
		_delay_us(50);
		vDIO_WRITE_BIT('c',0,0);
		TCCR1B=0xc1;
		while(READ_BIT(TIFR,ICF1)==0);
		a=ICR1;
		TIFR=1<<ICF1;
		TCCR1B=0x81;
		while(READ_BIT(TIFR,ICF1)==0);
		b=ICR1;
		TIFR=1<<ICF1;
		TCCR1B=0;
		TCNT1=0;
		high=b-a;
		distance=((high*34600)/(F_CPU*2));
		if(distance<10)
		{
			vLed_on(PORT_led,0);
			vLed_on(PORT_led,1);
			LCD_clear_screen();
			LCD_SEND_STRING("distance=");
			LCD_SEND_CHAR((distance%10)+48);
			LCD_SEND_STRING("cm");
			_delay_ms(500);
			
		}
		else if((distance<100)&&(distance>50))
		{
			vLed_on(PORT_led,1);
			LCD_clear_screen();
			LCD_SEND_STRING("distance=");
			LCD_SEND_CHAR((distance/10)+48);
			LCD_SEND_CHAR((distance%10)+48);
			LCD_SEND_STRING("cm");
			_delay_ms(500);
			vLed_off(PORT_led,0);
		}
		else if(distance<=50)
		{
			vLed_on(PORT_led,0);
			vLed_on(PORT_led,1);
			LCD_clear_screen();
			LCD_SEND_STRING("distance=");
			LCD_SEND_CHAR((distance/10)+48);
			LCD_SEND_CHAR((distance%10)+48);
			LCD_SEND_STRING("cm");
			_delay_ms(500);
			
		}

		else
		{
			LCD_clear_screen();
			LCD_SEND_STRING("no object");
			_delay_ms(300);
			vLed_off(PORT_led,1);
			vLed_off(PORT_led,0);
		}
         
    }
}