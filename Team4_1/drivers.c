#include "drivers.h"

void initGPIODrivers()
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);						//Enable GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);						//Enable GPIOB clock
	
	GPIO_InitTypeDef  GPIO_InitStructureA3;													//Init structure
	GPIO_InitTypeDef  GPIO_InitStructureB11;													//Init second structure

	
	GPIO_InitStructureA3.GPIO_Pin = GPIO_Pin_13;											//GPIOA pin3
	GPIO_InitStructureA3.GPIO_Mode = GPIO_Mode_Out_PP;							//Push&Pull
	GPIO_InitStructureA3.GPIO_Speed = GPIO_Speed_50MHz;							//50 MHz out mode
	
	GPIO_InitStructureB11.GPIO_Pin = GPIO_Pin_11;											//GPIOB pin11
	GPIO_InitStructureB11.GPIO_Mode = GPIO_Mode_Out_PP;							//Push&Pull
	GPIO_InitStructureB11.GPIO_Speed = GPIO_Speed_50MHz;							//50 MHz out mode
	
	GPIO_Init(GPIOC, &GPIO_InitStructureA3);												//Init GPIOA Pin3
	GPIO_Init(GPIOB, &GPIO_InitStructureB11);												//Init GPIOB Pin11
}

void PWMDrivers(uint32_t GPIOAWorkTime, uint32_t GPIOBWorkTime, uint32_t period)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);												//Set GPIOA 3 pin
	GPIO_SetBits(GPIOB, GPIO_Pin_11);												//Set GPIOB 11 pin
	if(GPIOAWorkTime > GPIOBWorkTime)
	{
		_delay_ms_dr(GPIOBWorkTime);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);										//Reset GPIOB 11 pin
		_delay_ms_dr(GPIOAWorkTime-GPIOBWorkTime);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);										//Reset GPIOA 3 pin
		_delay_ms_dr(period-GPIOAWorkTime);
	}
	else
	{
		_delay_ms_dr(GPIOAWorkTime);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);										//Reset GPIOA 3 pin
		_delay_ms_dr(GPIOBWorkTime-GPIOAWorkTime);
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);										//Reset GPIOB 11 pin
		_delay_ms_dr(period-GPIOBWorkTime);
	}
}

void _delay_ms_dr(uint32_t ms)
{
	for(uint32_t i=0; i<ms; i++)
		for(uint32_t j=0; j<9550; j++) {}
}
