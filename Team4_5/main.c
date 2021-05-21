#include "main.h"

//Vira Pyrih, Olena Fedchuk, IT-81

int main(void){
	
	initGPIO();
	
 	osKernelInitialize();
	t1 = osThreadNew(thread1, NULL, NULL);							//Thread that checks the button on B11
	t2 = osThreadNew(thread2, NULL, NULL);							//Thread that creates PWM for C13 and doubles period and worktime when button is pressed
	t3 = osThreadNew(thread3, NULL, NULL);							//Thread that creates PWM for A3 and divides period and worktime by 2 when button is pressed
	osKernelStart();
	
	while(1){

	}
}

void thread1(void* argum)
{
	while(1){
		if (checkButtonClick())
		{
			flagsSet2 = osThreadFlagsSet(t2, signalFlag);									//Set signal to t2 Thread with flag 0x01
			flagsSet3 = osThreadFlagsSet(t3, signalFlag);									//Set signal to t3 Thread with flag 0x01
		}
	}
}

void thread2(void* argum)
{
	uint32_t workTime = 1000U;
	uint32_t period = 2000U;
	
	while(1){
		PWM2(workTime, period);

		flagsWait2 = osThreadFlagsWait(signalFlag, osFlagsWaitAny, 0);		//If flag 0x01 is set, returns thread flags before clearing; No time-out
		if (flagsWait2 == signalFlag)																			//True if signal from t1 Thread is set
		{
			workTime *= 2;
			period *= 2;
			flagsWait2 = 0;																									//Set to 0 to clear the value
		}
	}
}

void thread3(void* argum)
{
	uint32_t workTime = 15U;
	uint32_t period = 30U;
	
	while(1){
		PWM3(workTime, period);

		flagsWait3 = osThreadFlagsWait(signalFlag, osFlagsWaitAny, 0);			//If flag 0x01 is set, returns thread flags before clearing; No time-out
		if (flagsWait3 == signalFlag)																			//True if signal from t1 Thread is set
		{
			workTime /= 2;
			period /= 2;
			flagsWait3 = 0;																								//Set to 0 to clear the value
		}
	}
}
