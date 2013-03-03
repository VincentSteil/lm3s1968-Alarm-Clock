// Pushbuttons.c
// Vincent Steil & William Kelsey
// Runs on LM3S1968 or LM3S8962
// February 6, 2013

#include "lm3s1968.h"
#include "Pushbuttons.h"

#include <stdio.h>
#include "Output.h"

// which delays 3*ulCount cycles
#ifdef __TI_COMPILER_VERSION__

	//Code Composer Studio Code
	void Delay(unsigned long ulCount){
	__asm (	"    subs    r0, #1\n"
			"    bne     Delay\n"
			"    bx      lr\n");
}

#else
	//Keil uVision Code
	__asm void
	Delay(unsigned long ulCount)
	{
    subs    r0, #1
    bne     Delay
    bx      lr
	}

#endif


void Pushbuttons_Init(void){
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG; // activate port G
  Delay(1000000);
  GPIO_PORTG_PUR_R |= 0xF8;
  GPIO_PORTG_DIR_R |= 0x04;					    // make PG2 out (built-in LED)
	GPIO_PORTG_DIR_R &= 0x07;             // make PG3-7 in PG3=Up	PG4=Down	PG5=Left	PG6=Right, PG7=Select
  GPIO_PORTG_AFSEL_R &= 0x00;           // disable alt func on PG2
  GPIO_PORTG_DEN_R |= 0xFF;             // enable digital I/O on 
}

unsigned char Pushbuttons_Select_Read(void){
  return !(GPIO_PORTG_DATA_R & 0x80);
}

unsigned char Pushbuttons_Right_Read(void){
  return !(GPIO_PORTG_DATA_R & 0x40);
}

unsigned char Pushbuttons_Left_Read(void){
  return !(GPIO_PORTG_DATA_R & 0x20);
}

unsigned char Pushbuttons_Down_Read(void){
  return !(GPIO_PORTG_DATA_R & 0x10);
}

unsigned char Pushbuttons_Up_Read(void){
  return !(GPIO_PORTG_DATA_R & 0x08);
}


void Pushbuttons_Test(void){
  Pushbuttons_Init();
  Output_Init();
  Output_Color(15);
  
  while(1){
   GPIO_PORTG_DATA_R ^= 0x04;					     // toggle PG2
   Delay(100000);
   if (Pushbuttons_Select_Read()) {
     Output_Clear();
     printf("select");
   }
   else if(Pushbuttons_Right_Read()){
     Output_Clear();
     printf("right");
   }
   else if (Pushbuttons_Left_Read()){
     Output_Clear();
     printf("left");
   }
   else if (Pushbuttons_Down_Read()){
     Output_Clear();
     printf("down");
   }
   else if (Pushbuttons_Up_Read()){
     Output_Clear();
     printf("up");
   }
  }
}

