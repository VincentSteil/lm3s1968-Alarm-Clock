// Vincent Steil && William Kelsey
// modified functions from rit128x96x4.h
// original (C) by TI

#include "hands.h"
#include "rit128x96x4.h"
#include "clockNumbers.h"

unsigned char bitMap_hand[][4];

void RIT128x96x4_ClearImage(void);
//*************RIT128x96x4_Line********************************************
// Draws one line in the RAM version of the image
// Inputs: (x1,y1) is the start point
// (x2,y2) is the end point
// color is 0 (off) to 15 (white)
// coordinates range from 0 to MAX, 0 is bottom or left, MAX is top or right
// Outputs: none
void RIT128x96x4_Line(int x1, int y1, int x2, int y2, unsigned char color){
	/*DEFINE THE MAX VALUES*/
	signed int incX, incY, N,j;
	unsigned char ourColor = '0xFF';
	
	
	/*Define how many pixels we are drawing*/
	N = 100;
	
	if(((x1 && x2) > 127) && ((y1 && y2) > 100)) {
		/*Still using printf??*/
	//	printf("Yo numbers outside the range!");
//		exit(0);
	} else {
		
		//Y is inverted
		y1 = 96-y1;
		y2 = 96-y2;

		//Calculate amount to increment in each direction before drawing the pixel
		//500 eliminates the rounding error
		incX = ((x2 - x1)*1000) / N;
		incY = ((y2 - y1)*1000) / N;
		
		
		
			for(j=0; j<N; j++){
				RIT128x96x4ImageDraw(&ourColor, (1000*x1 +j*incX + 500)/1000, (1000*y1+ j*incY + 500)/1000, 2, 1);
			}			
		
		}

}
//Lab 2 Performance Debugging Spring 2013 (January 13, 2013) Page 2.7
//Jonathan W. Valvano
//*************RIT128x96x4_ShowImage**************************************
// Copies the RAM version of the image to the OLED
// Inputs: none
// Outputs: none
void RIT128x96x4_ShowTime(int hour, int minutes){
	int hourX=0,hourY=0,j=minutes;
	int minutePositionsX[] = {60,64,68,72,76,80,83,86,89,92,94,96,97,98,99,100};
	int minutePositionsY[] = {85,84,83,82,81,80,78,76,73,70,67,64,60,56,52,48};//Ymax = 85 Ymin = 5
	int hourPointsX[] = {60,80,93,98,93,80,60,42,27,22,27,42};
	int hourPointsY[] = {7,15,27,45,65,80,85,80,65,45,25,10};

	/*Display the minutes*/
	if(minutes <15) {
		RIT128x96x4_Line(64, 48, minutePositionsX[minutes], minutePositionsY[minutes]-2,  'b');
		
	} else if(minutes <30) {
		minutes-=15;
		RIT128x96x4_Line(64, 48, minutePositionsX[15-minutes], 96 - minutePositionsY[15-minutes]-2,  'b');
		
	} else if(minutes<45) {
		minutes-=30;
		RIT128x96x4_Line(64, 48,120 - minutePositionsX[minutes], 96 - minutePositionsY[minutes]-2,  'b');
		
	} else { /*Must be in the 45-60 minute quartile*/
		minutes-=45;
		RIT128x96x4_Line(64, 48, 120 - minutePositionsX[15-minutes], minutePositionsY[15-minutes]-2,  'b');
	}
	
	minutes=j;
	
	/*Display the hour*/
	if((hour == 0) || (hour == 12)) {
		/*If the hour is 6 or 12 then the hour hand basically only moves in =ve or -ve X*/
		hourX = hourPointsX[hour];// + (hour==0)?1:2;//(minutes/12):-(minutes/12);
		if(hour==0) hourX+=4*minutes/12;
		else hourX-=minutes/12;
		hourY = hourPointsY[hour];
	} else if ((hour == 3 )||(hour==9)) {
		/*Only really changes in y*/
		hourY = hourPointsY[hour];// + (hour==3)?(minutes/12) -3 : 3-(minutes/12);
		if(hour == 3) hourY-=minutes/12;
		else hourY-=minutes/12;
		hourX = hourPointsX[hour];
	} else {
		/*All other hours have a change in X and Y*/
		hourX = hourPointsX[hour];// + (hour == (1 || 2 || 10 || 11))?(minutes/12)-2:2-(minutes/12);
		if((hour == 1) || (hour==2) || (hour==10) || (hour==11)) hourX+=4*minutes/12;
		else hourX-=4*minutes/12;
		
		hourY = hourPointsY[hour];// + (hour == (7 || 8 || 10 || 11))?(minutes/12)-2:2-(minutes/12);
		if((hour == 7) || (hour==8) || (hour==10) || (hour==11)) hourY-=minutes/12;
		else hourY+=minutes/12;
	}
	RIT128x96x4_Line(64, 48, hourX, 96-hourY,  'b');
	
	
	/*Draw the clock*/
	clockNumbers();
	
}

//ALL THIS BELOW IS FOR SYSTICK

