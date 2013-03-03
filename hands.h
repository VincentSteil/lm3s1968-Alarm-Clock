/*clock.h

William Kelsey, wdk279
Vincent Steil, vjs432
This file contains all the functions required for drawing a clock



*/

/*Global variable*/
extern unsigned char bitMap_hand[][4];

//Draws a line between (x1,y1) and (x2,y2)
void RIT128x96x4_Line(int x1, int y1, int x2, int y2, unsigned char color);

//Draws the clock with this time. Hours range from 0->11 and minutes 1->60 (sorry for the confusing mix of 1 and 0!!!!)
/*NOT PERFECT YET - CLOSE THOUGH :) */
void RIT128x96x4_ShowTime(int hour, int minutes);





