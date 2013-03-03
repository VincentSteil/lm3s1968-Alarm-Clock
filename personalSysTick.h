// personalSysTick.h
// Vincent Steil & William Kelsey
// initialises systick interrupts 


// initialise systick with period*clockcycleperiod as period
void SysTick_Init(unsigned long period);

// Time delay using busy wait.
// The delay parameter is in units of the core clock. (units of 20 nsec for 50 MHz clock)
void SysTick_Wait(unsigned long delay);

// Time delay using busy wait.
// This assumes 50 MHz system clock.
void SysTick_10ms_wait(unsigned long delay);
