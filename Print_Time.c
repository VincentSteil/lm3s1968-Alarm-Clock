// Print_Time.c
// Vincent Steil & William Kelsey
// various print functions for an alarm clock

#include "Print_Time.h"
#include "output.h"
#include "hands.h"
#include "rit128x96x4.h"

void Print_Status(unsigned char enabled){
   if(enabled){
     printf("ON ");
   }
   else{
     printf("OFF");
   }
}

void Print_Day(unsigned char day){
  switch (day){
    case 0:
      printf("Mon");
      break;
    case 1:
      printf("Tue");
      break;
    case 2:
      printf("Wed");
      break;
    case 3:
      printf("Thu");
      break;
    case 4:
      printf("Fri");
      break;
    case 5:
      printf("Sat");
      break;
    case 6:
      printf("Sun");
      break;
  }
}

void print_screen(unsigned char print_boolean, unsigned long weekday, int second, int minute, int hour, unsigned char enabled, unsigned char select){
  switch (select) {
          case 0:          
            //RIT128x96x4Clear();
					  Output_Clear();
            printf("[");
            Print_Day(weekday);
            printf("] ");
            Print_Hour(hour);
            printf(":");
            Print_Minute(minute);
            printf(":00  ");
            Print_Status(enabled);
            break;
          case 1:
            //RIT128x96x4Clear();
					Output_Clear();
            Print_Day(weekday);
            printf("[");
            Print_Hour(hour);
            printf("]");
            printf(":");
            Print_Minute(minute);
            printf(":00  ");
            Print_Status(enabled);
            break;
          case 2:
           // RIT128x96x4Clear();
					Output_Clear();
            Print_Day(weekday);
            printf(" ");
            Print_Hour(hour);
            printf(":");
            printf("[");
            Print_Minute(minute);
            printf("]");
            printf(":00 ");
            Print_Status(enabled);
            break;
          case 3:
           //RIT128x96x4Clear();
					Output_Clear();
            Print_Day(weekday);
            printf(" ");
            Print_Hour(hour);
            printf(":");
            Print_Minute(minute);
            printf(":00 ");
            printf("[");
            Print_Status(enabled);
            printf("]");
            break;
          case 4:
            if(print_boolean){
             // RIT128x96x4Clear();
							Output_Clear();
              Print_Day(weekday);
              printf(" ");
              Print_Hour(hour);
              printf(":");
              Print_Minute(minute);
              printf(":");
              Print_Second(second);
              printf(" ");
              Print_Status(enabled);
            }
            break;
        } 
				//printf("\n \n \n TIME");
}

void Print_Hour(int hour){
  if(hour < 10){
    printf("0");
    printf("%d", hour);
  }
  else{
    printf("%d", hour);
  }
}
void Print_Minute(int minute){
  if(minute < 10){
    printf("0");
    printf("%d", minute);
  }
  else{
    printf("%d", minute);
  }
}
void Print_Second(int second){
  if(second < 10){
    printf("0");
    printf("%d", second);
  }
  else{
    printf("%d", second);
  }
}
