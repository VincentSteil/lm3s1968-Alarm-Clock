#include "clockNumbers.h"
#include "string.h"
#include "rit128x96x4.h"

void clockNumbers(void){
	
	char *pcStr;
	int shiftX=0, shiftY = 0;
	unsigned char ucLevel = '0xF';
	
	strcpy(pcStr, "A");

	RIT128x96x4StringDraw("12", 60+shiftX, 5+shiftY, ucLevel);
	RIT128x96x4StringDraw("11", 40+shiftX, 10+shiftY, ucLevel);
	RIT128x96x4StringDraw("10", 25+shiftX, 25+shiftY, ucLevel);
	
	RIT128x96x4StringDraw("9", 20+shiftX, 45+shiftY, ucLevel);
	RIT128x96x4StringDraw("8", 25+shiftX, 65+shiftY, ucLevel);
	RIT128x96x4StringDraw("7", 40+shiftX, 80+shiftY, ucLevel);
	
	RIT128x96x4StringDraw("6", 60+shiftX, 85+shiftY, ucLevel);
	RIT128x96x4StringDraw("5", 80+shiftX, 80+shiftY, ucLevel);
	RIT128x96x4StringDraw("4", 95+shiftX, 65+shiftY, ucLevel);
	
	RIT128x96x4StringDraw("3", 100+shiftX, 45+shiftY, ucLevel);
	RIT128x96x4StringDraw("2", 95+shiftX, 25+shiftY, ucLevel);
	RIT128x96x4StringDraw("1", 80+shiftX, 10+shiftY, ucLevel);
	
/* Use this function to draw the minute 'ticks'*/	
/*
	for(i=0;i++;i<4) {
		RIT128x96x4ImageDraw(ucLevel, 60 ), 45 + (y*5), 2, 2);
	
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*5)), 45 + (y*20), 2, 2);
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*15)), 45 + (y*15), 2, 2);
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*20)), 45 + (y*5), 2, 2);

		
		x=-x;
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*15)), 45 + (y*20), 2, 2);
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*5)), 45 + (y*15), 2, 2);
		RIT128x96x4ImageDraw(ucLevel, 60 + (x*20)), 45 + (y*5), 2, 2);
	}*/
}

