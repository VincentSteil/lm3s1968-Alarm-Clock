// Pushbuttons.h
// Vincent Steil & William Kelsey
// Runs on LM3S1968 or LM3S8962
// February 6, 2013




// Initialise the pushbuttons on the proto-board
void Pushbuttons_Init(void);

// Read and return, if select is pressed
unsigned char Pushbuttons_Select_Read(void);

// Read and return, if right is pressed
unsigned char Pushbuttons_Right_Read(void);

// Read and return, if left is pressed
unsigned char Pushbuttons_Left_Read(void);

// Read and return, if down is pressed
unsigned char Pushbuttons_Down_Read(void);

// Read and return, if up is pressed
unsigned char Pushbuttons_Up_Read(void);

// Test all 5 pushbuttons
void Pushbuttons_Test(void);
