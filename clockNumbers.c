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
	
}

