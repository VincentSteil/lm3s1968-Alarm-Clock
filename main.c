// main.c
// Runs on LM3S1968
// Vincent Steil && William Kelsey




#include <stdio.h>
#include "output.h"
#include "pushbuttons.h"
#include "lm3s1968.h"
#include "rit128x96x4.h"
#include "alarm.h"
#include "hands.h"
#include "personalSysTick.h"
#include "pll.h"
#include "Print_Time.h"
#include "DAC.h"



// select == 0: choose weekday of alarm
// select == 1: choose hour of alarm
// select == 2: choose minute of alarm
// select == 3: choose enabled/disabled
// select == 4: normal alarm operation
volatile unsigned char select = 4;
volatile unsigned char select_timer = 0;
volatile unsigned char select_wait = 5;

volatile unsigned char select_pressed = 0;
volatile unsigned char up_pressed = 0;
volatile unsigned char down_pressed = 0;
volatile unsigned char left_pressed = 0;
volatile unsigned char right_pressed = 0;

volatile unsigned char alarm_change = 0;
volatile unsigned char has_alarm_changed = 0;


// delay in N*10ms before a button press registers; threshold value is set in wait_threshold
volatile unsigned char button_pressed = 0;
volatile unsigned char wait_threshold = 8;

volatile unsigned long time_10ms;
volatile int time_seconds;
volatile int time_minutes;
volatile int time_hours;
// weekday: 0 == Mon... 6 == Sun
volatile unsigned long time_weekday;

volatile unsigned char print_bool;
volatile unsigned char alarms_enabled;
volatile unsigned long alarm_sound_count = 0;
volatile unsigned char alarm_sound;

volatile unsigned long TimerCount = 0;							// for debugging only

void LED_Init(void){
  signed long wait;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;             // activate port G
  wait = 0;
	wait++;
  GPIO_PORTG_DIR_R |= 0x0F;                         // make PG2 out (built-in LED)
  GPIO_PORTG_AFSEL_R &= 0x00;                       // disable alt func on PG2
  GPIO_PORTG_DEN_R |= 0x0F;                         // enable digital I/O on PG2
}
void LED_Toggle(void){
	GPIO_PORTG_DATA_R ^= 0x04;                        // toggle PG2
}
void Timer0B_Init(unsigned short period){           // init Timer0B
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;
	TimerCount = 0;
	TIMER0_CTL_R &= ~0x00000100;
	TIMER0_CFG_R = 0x00000004;
	TIMER0_TBMR_R = 0x00000002;
	TIMER0_TBILR_R = period-1;
	TIMER0_TBPR_R = 0;
	TIMER0_ICR_R = 0x00000100;
	TIMER0_IMR_R |= 0x00000100;
	NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFFFF00)|0x00000040;
	NVIC_EN0_R |= NVIC_EN0_INT20;
}


int main(void){
  PLL_Init();
  SysTick_Init(500000);                             // 20ns*500000 = 10ms period
  LED_Init();
  LED_Toggle();
  Output_Color(15);
  Output_Init();                                    // printf now points to the oled
  RIT128x96x4Init(1000000);                         // SPI clock period 20ms
  Pushbuttons_Init();
  Alarm_Init();
  DAC_Init();
  Timer0B_Init(4535);                               // 11025 Hz frequency for audio
  EnableInterrupts();
	TIMER0_CTL_R |= 0x00000100;

  print_bool = 1;
  select = 4;                                       // start system in normal alarm mode
  select_timer = 0;
  alarms_enabled = 1;
  time_minutes = 0;
  time_hours = 0;
  time_seconds = 0;
  up_pressed = 0;
  down_pressed = 0;
  select_pressed = 0;
  left_pressed = 0;
  right_pressed = 0;
  button_pressed = 0;
  alarm_sound = 0;
	
  
  while(1){
      // regulate time and day
      if(time_10ms > 99){
        time_10ms = 0;
        time_seconds++;
        print_bool = 1;
      }

      if(time_seconds > 59){
        time_seconds = 0;
        time_minutes++;
        if(time_minutes == Alarm_ReturnMinute() && time_hours == Alarm_ReturnHour() && Alarm_ReturnStatus){
          alarm_sound = 1;
        }
      }
      if(time_minutes > 59){
        time_minutes = 0;
        time_hours++;
      }
      if(time_hours > 23){
        time_hours = 0;
        Alarm_NextDay();
        time_weekday++;
        time_weekday %= 7;
      }
      
      
      // handle select menu itself; menu active on select_timer > 0
      if(select_timer){
        if(left_pressed && select){
					if (has_alarm_changed == 0) {
						alarm_change = 1;
						has_alarm_changed = 1;
					}
          left_pressed = 0;
          select--;
          if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);
        }
        else if(left_pressed && !select){
					if (has_alarm_changed == 0) {
						alarm_change = 1;
						has_alarm_changed = 1;
					}
          left_pressed = 0;
          select = 3;
					//If the left button is pressed, display the alarm time for changing
          if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);
        }
        else if(right_pressed){
					if (has_alarm_changed == 0) {
						alarm_change = 0;
						has_alarm_changed = 1;
					}
          right_pressed = 0;
          select++;
          select %= 4;
					//If the right button is pressed, display the current time for changing
					if(alarm_change == 0) print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);
					else print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
        }
				//Adding the ability to change time... DONE BUT NOT PROPERLY TESTED :(
				
				else if(up_pressed && !(alarm_change)) {
					up_pressed = 0;
          switch (select) {
            case 0:
              time_weekday++;
              break;
            case 1:
              time_hours++;
              break;
            case 2:
              time_minutes++;
              break;
            case 3:
              Alarm_ToggleEnable();
              break;
          }
					if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);					
				}
				else if(down_pressed && !(alarm_change)) {
					down_pressed = 0;
          switch (select) {
            case 0:
              time_weekday--;
              break;
            case 1:
              time_hours--;
              break;
            case 2:
              time_minutes--;
              break;
            case 3:
              Alarm_ToggleEnable();
              break;
          }
					if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);					
				}
				
        else if(up_pressed){
          up_pressed = 0;
          switch (select) {
            case 0:
              Alarm_NextDay();
              break;
            case 1:
              Alarm_IncrementHour();
              break;
            case 2:
              Alarm_IncrementMinute();
              break;
            case 3:
              Alarm_ToggleEnable();
              break;
          }
					if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);
        }
        else if(down_pressed){
          down_pressed = 0;
          switch (select) {
            case 0:
              Alarm_PreviousDay();
              break;
            case 1:
              Alarm_DecrementHour();
              break;
            case 2:
              Alarm_DecrementMinute();
              break;
            case 3:
              Alarm_ToggleEnable();
              break;
          }
					if(alarm_change == 1) print_screen(print_bool, Alarm_CurrentDay(), 0, Alarm_ReturnMinute(), Alarm_ReturnHour(), Alarm_ReturnStatus(), select);
					else print_screen(print_bool, time_weekday, 0, time_minutes, time_hours, Alarm_ReturnStatus(), select);
        }
      }
      else{
        while(!(time_weekday == Alarm_CurrentDay())){
          Alarm_NextDay();
        }
        select = 4;
        print_screen(print_bool, time_weekday, time_seconds, time_minutes, time_hours, Alarm_ReturnStatus(), select);
        if (print_bool){
          RIT128x96x4_ShowTime(time_hours, time_minutes);
        }
				
				has_alarm_changed = 0;
				alarm_change = 0;
				
        print_bool = 0;
      
      }
  } 
    

}



void SysTick_Handler(void){
    // read pushbuttons
    // I should refactor this to use edge triggered interrupts
    if(Pushbuttons_Up_Read() || Pushbuttons_Down_Read() || Pushbuttons_Left_Read() || Pushbuttons_Right_Read() || Pushbuttons_Select_Read()){
      button_pressed++;
    }
    else{
      button_pressed = 0;
    }
    
    if(button_pressed > wait_threshold){
      button_pressed = 0;
      up_pressed =  Pushbuttons_Up_Read();  
      down_pressed = Pushbuttons_Down_Read();  
      left_pressed = Pushbuttons_Left_Read();  
      right_pressed = Pushbuttons_Right_Read();
      select_pressed = Pushbuttons_Select_Read();
      select_timer = select_wait;
      if(select_pressed){
        select_pressed = 0;
        select_timer = 0;
      }
    }
    
    time_10ms++;
    
    if(!(time_10ms%100)){
      if(select_timer){
        select_timer--;
        LED_Toggle();
      }
    }
}

void Timer0B_Handler(void){																	
  // handles sound output by cycling through a const char array of 4 bit data when global flags are set
	int z, k;
	TIMER0_ICR_R = 0x00000100;
	if(alarm_sound) {
			DAC_Out(SmallExplosion[alarm_sound_count]);
			alarm_sound_count++;
			if(alarm_sound_count>1500){
				alarm_sound = 0;
				alarm_sound_count = 0;
			}
	}
}
