/*
 * motor.c
 *
 * Created: 17/12-19
 *  Author: Abdirahman Omar Ali & Henrik Goth
 */ 

#include "avr/io.h"
#include <inttypes.h>
#include "motor.h"

void  motor_init(void){
	
	// set PC6 (digital pin 5) as output
	DDRC |= (1<<COM3A0);  //0b01000000;
	TCCR3A |= (1<<COM3A1);
	// Set OC3A (PC6) to be cleared on Compare Match (Channel A) TCCR3A |= .... // Waveform Generation Mode 5, Fast PWM (8-bit)
	
	//COM3A1 = 0b00000001;
	//COM3A0 = 0b00000000;
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32);
	// Timer Clock, 16/64 MHz = 1/4 MHz
	TCCR3B |= (1<<CS30) | (1<<CS31);
	
	
		
	
	
	
}

void motor_set_speed(uint8_t fart){
	uint8_t motorspeed = fart * 255;
	motorspeed = motorspeed/100;
	OCR3AL = (uint8_t)motorspeed;
	
	}