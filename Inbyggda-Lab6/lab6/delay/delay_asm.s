/*
 * delay_asm.s
 *
 * Author:	Abdirahman Omar Ali & Henrik Goth
 *
 * Date:	10/1-20
 */ 

 /*
	Syftet med denna filen är att ha fördröjning mellan
	nästa instruktion där filen kallas.

 */

.global delay_1_micros
.global delay_micros
.global delay_ms
.global delay_s


 ;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================

delay_1_micros:
	NOP	
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC R24
	CPI R24, 0		
	BRNE delay_micros
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R18,R24
loop_dms:
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18
	CPI R18, 0
	BRNE loop_dms		
	RET

;==============================================================================
; Delay of X s
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_s:
	MOV R19, R24
loop_s:				;delay_1_s
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	DEC R19
	CPI R19, 0
	BRNE loop_s
	RET