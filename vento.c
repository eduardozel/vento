/*
 * vento.c
 *
 * Created: 27.07.2017
 *  Author: Eduardo
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#include <math.h>
#include <util/delay.h>


#define YEL_ON  PORTB  |=  0b00000001
#define YEL_OFF PORTB  &=  0b11111110

#define yel_OFF PORTB  |=  0b00001000
#define yel_ON  PORTB  &=  0b11110111

#define BLU_OFF PORTA  |=  0b00000100
#define BLU_ON  PORTA  &=  0b11111011

#define bntOn  bit_is_clear(PINB, PB1)
#define bntOff bit_is_set(PINB, PB1)

#define set_Timer_Cnt TCNT0 = (256 - 234)

const unsigned char OneSec =   5;
const int maxDelay = 2100;// =7*60*OneSec;

int delay;

ISR(INT0_vect)
{
  BLU_ON;
  set_Timer_Cnt;
//  TIMSK0 |= (unsigned char)_BV(TOIE0);
  set_sleep_mode( SLEEP_MODE_IDLE );
} // SIGNAL(SIG_PIN_CHANGE0)

//ISR(TIM0_OVF_vect)
//{
//	if ( --delay == 0 ) {
//		BLU_OFF;
//	    YEL_OFF;
//		TIMSK0 &= !(_BV(TOIE0));
//		set_sleep_mode( SLEEP_MODE_PWR_DOWN );
//    } else {
//      if        ( ( delay < BLUDelay) ) {
//	    yel_OFF;
//	  } else if ( ( delay < YELDelay ) ) {
//	    YEL_OFF;
//        BLU_ON;
//      } else if ( ( delay < (maxDelay - 5*OneSec )) ) {
//	    YEL_ON;
//      };
//      set_Timer_Cnt;
//    }; // if delay == 0

//} // ISR(TIM0_OVF_vect)



int main(void)
{
  DDRA  = ( 1 << DD2 );
  PORTA = 0b11111110;

  DDRB  = 0b10111111;
  PORTB = 0b11111110;

  GIMSK = ( 1 << INT0 );
  //  MCUCR = 0; // 0 on INT0

  wdt_disable();

//  TCCR0B = ( 1 << CS02 ) | ( 1 << CS00 ); // /1024

  sei();
  set_sleep_mode( SLEEP_MODE_PWR_DOWN );
  BLU_OFF;
  while (1) {
	  sleep_enable();
	  sleep_cpu();
  } // while
}
