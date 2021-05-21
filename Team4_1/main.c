#include "main.h"

//Vira Pyrih, Olena Fedchuk, IT-81

int main()
{
	//initGPIOStructures();
	initGPIODrivers();
	
	while(1)
	{
		//PWMStructures(15, 5, 30);												//15 ms GPIOA3, 5 ms GPIOB11, 30 ms period
		PWMDrivers(15, 5, 30);													//15 ms GPIOA3, 5 ms GPIOB11, 30 ms period
	}
}
