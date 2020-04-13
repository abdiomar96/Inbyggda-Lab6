/*
 * temp.c
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius, Abdirahman Omar Ali & Henrik Goth
 *
 * Date:	17/12-19
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint8_t adc;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	// read ADC value
	// UPPGIFT: Läs in ADC-värdet. Börja med att läsa av det "låga" registret, därefter det "höga" registret!
	adc = ADCH;

}

/*
 * Initialize the ADC and ISR.
 */
//void temp_init(void)
void regulator_init(void)
{
	// UPPGIFT: konfigurera ADC-enheten genom ställa in ADMUX och ADCSRA enligt kommentarerna nedanför!
	ADMUX |= (1<<REFS0);		// set reference voltage (internal 5V)
	ADMUX |= (1<<MUX0) ;		// select diff.amp 10x on ADC0 & ADC1
	ADMUX |= (1<<ADLAR)	;		// right adjustment of ADC value   ; VAD ÄR DU fÖR NÅT?
	
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1 )| (1<<ADPS2);		// prescaler 128
	ADCSRA |= (1<<ADATE);		// enable Auto Trigger
	ADCSRA |= (1<<ADIE);		// enable Interrupt
	ADCSRA |= (1<<ADEN);		// enable ADC

	// disable digital input on ADC0 and ADC1
	DIDR0 = 2; //3;
		
	// disable USB controller (to make interrupts possible)
	USBCON = 0;	
	// enable global interrupts
	sei();

	// start initial conversion
	ADCSRA |= (1<<ADSC);	// UPPGIFT: gör så att den initiala A/D-omvandlingen sker
}

/*
 * Returns the temperature in Celsius.
 */
uint8_t regulator_read(void)
{
	uint8_t speed = (adc*100)/255;     //128 ist för att det är 8 bitar ?
	return (uint8_t) speed;
}



/*
 * Returns the temperature in Fahrenheit.
 */




