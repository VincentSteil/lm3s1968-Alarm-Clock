// Alarm.h
// Vincent Steil & William Kelsey
// Runs on LM3S1968 or LM3S8962
// February 6, 2013


// Initialise the alarm fsm
void Alarm_Init(void);

// Move to the next day 
void Alarm_NextDay(void);

// Move to the previous day
void Alarm_PreviousDay(void);

// Return the current day as a char
// 1 == Monday
// ...
// 7 == Sunday
unsigned char Alarm_CurrentDay(void);

// Increment the hour counter on the current day
void Alarm_IncrementHour(void);

// Decrement the hour counter on the current day
void Alarm_DecrementHour(void);

// Increment the minute counter on the current day
void Alarm_IncrementMinute(void);

// Decrement the minute counter on the current day
void Alarm_DecrementMinute(void);

// Enable/Disable the current alarm
void Alarm_ToggleEnable(void);

// Returns, if the current alarm is enabled
unsigned char Alarm_ReturnStatus(void);

// Return current hour value of this alarm
int Alarm_ReturnHour(void);

// Return current minute value of this alarm
int Alarm_ReturnMinute(void);

// alarm sound as array 
extern const unsigned char SmallExplosion[];
