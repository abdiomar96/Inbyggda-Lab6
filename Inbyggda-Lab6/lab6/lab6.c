/*
 * Labb6.c file contains code where the main program
 * is using a state machine following the Moores principle. Components 
 * used for this to achieve the information is a Temperature sensor, Arduino Leonardo and
 * Hitachi LCD display 
 *
 * Created: 17/12-19
 * Author : Henrik Goth & Abdirahman Omar Ali
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "hmi/hmi.h"
#include "numkey/numkey.h"
#include "regulator/regulator.h"
#include "lcd/lcd.h"
#include "delay/delay.h"
#include "motor/motor.h"

	char temp_str[17];
	char p_str1 [17];

enum state{

	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
	
};

typedef enum state state_t;



int main(void)
{
	// initialize HMI (LCD and numeric keyboard)
	hmi_init();
	
	//Initialize the ADC and ISR.
	regulator_init();
	
	motor_init();
	
	uint8_t key;
	uint8_t reg_val;
	
	

	
	
	state_t CURRENT_STATE = MOTOR_OFF;
	state_t NEXT_STATE = MOTOR_OFF;
	
	//sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
	//output_msg(p_str1, temp_str, 0);s
	


	while (1)
	{
		
		key =  numkey_read();
		reg_val = regulator_read();
		
		switch(CURRENT_STATE) {
		 case MOTOR_OFF:
			sprintf(temp_str, "%u%c", reg_val, 0x25);
			sprintf(p_str1 ,"Motor OFF");
			output_msg(p_str1, temp_str, 0);
			motor_set_speed(0);
			
			if (key== NO_KEY && reg_val == 0 ){
				NEXT_STATE = MOTOR_ON;			
				} 
			break;
			
				case MOTOR_ON:
				//2nd state
				motor_set_speed(0);
				sprintf(temp_str, "%u%c", reg_val, 0x25);
				sprintf(p_str1 ,"Motor ON");
				output_msg(p_str1, temp_str ,0);
				 
				if (reg_val > 0){
					NEXT_STATE = MOTOR_RUNNING;
					
			} /*else if (key == '2' && reg_val == 0){
					NEXT_STATE = MOTOR_ON;
					motor_set_speed(0);
					*/
					} else if (numkey_read()== '1'){
					NEXT_STATE = MOTOR_OFF;
					
					} 
				break;
				
				
				case MOTOR_RUNNING:
					//2nd state
					motor_set_speed(reg_val);
					sprintf(temp_str, "%u%c", reg_val, 0x25);
					sprintf(p_str1, "motor Runnning");
					output_msg("Motor OFF",p_str1 ,0);
						
						 if (numkey_read()== '1'){
						NEXT_STATE = MOTOR_OFF;
						
						}
						
						break;
					}
					CURRENT_STATE = NEXT_STATE;
				
			-

			}
			
 }

		
			
		
		
		
