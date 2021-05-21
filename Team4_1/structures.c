#include "structures.h"

void initGPIOStructures(void)
{
	RCC->APB2ENR|= RCC_APB2ENR_IOPAEN;										//Enable GPIOA clock
	RCC->APB2ENR|= RCC_APB2ENR_IOPBEN;										//Enable GPIOB clock

	GPIOA->CRL |= (GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1);					//50 MHz out mode
	GPIOA->CRL &= ~GPIO_CRL_CNF3;											//Push&Pull

	GPIOB->CRH |= (GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1);					//50 MHz out mode
	GPIOB->CRH &= ~GPIO_CRH_CNF11;											//Push&Pull
}

void PWMStructures(uint32_t GPIOAWorkTime, uint32_t GPIOBWorkTime, uint32_t period)
{
	GPIOA->BSRR |= GPIO_BSRR_BS3;											//Set GPIOA 3 pin
	GPIOB->BSRR |= GPIO_BSRR_BS11;											//Set GPIOB 11 pin
	
	if(GPIOAWorkTime > GPIOBWorkTime)
	{
		_delay_ms_str(GPIOBWorkTime);
		GPIOB->BRR |= GPIO_BRR_BR11;											//Reset GPIOB 11 pin
		_delay_ms_str(GPIOAWorkTime-GPIOBWorkTime);
		GPIOA->BRR |= GPIO_BRR_BR3;											//Reset GPIOA 3 pin
		_delay_ms_str(period-GPIOAWorkTime);
	}
	else
	{
		_delay_ms_str(GPIOAWorkTime);
		GPIOA->BRR |= GPIO_BRR_BR3;											//Reset GPIOA 3 pin
		_delay_ms_str(GPIOBWorkTime-GPIOAWorkTime);
		GPIOB->BRR |= GPIO_BRR_BR11;											//Reset GPIOB 11 pin
		_delay_ms_str(period-GPIOBWorkTime);
	}
}

void _delay_ms_str(uint32_t ms)
{
	for(uint32_t i=0; i<ms; i++)
		for(uint32_t j=0; j<9550; j++) {}
}
