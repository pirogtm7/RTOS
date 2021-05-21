#include "gpio_init.h"

void initGPIO(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);						//Enable GPIOB clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);						//Enable GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);						//Enable GPIOC clock
	
	GPIO_InitTypeDef	GPIO_InitStructureB11;												//Init structure for B11
	GPIO_InitTypeDef	GPIO_InitStructureA3;													//Init structure for A3
	GPIO_InitTypeDef	GPIO_InitStructureC13;												//Init structure for C13

	GPIO_InitStructureB11.GPIO_Pin = GPIO_Pin_11;										//GPIOB pin11
	GPIO_InitStructureB11.GPIO_Mode = GPIO_Mode_IPU;								//Input Pull-Up
	GPIO_InitStructureB11.GPIO_Speed = GPIO_Speed_2MHz;							//2 MHz out mode
	
	GPIO_InitStructureA3.GPIO_Pin = GPIO_Pin_3;											//GPIOA pin3
	GPIO_InitStructureA3.GPIO_Mode = GPIO_Mode_Out_PP;							//Push&Pull
	GPIO_InitStructureA3.GPIO_Speed = GPIO_Speed_2MHz;							//2 MHz out mode
	
	GPIO_InitStructureC13.GPIO_Pin = GPIO_Pin_13;										//GPIOC pin13
	GPIO_InitStructureC13.GPIO_Mode = GPIO_Mode_Out_PP;							//Push&Pull
	GPIO_InitStructureC13.GPIO_Speed = GPIO_Speed_2MHz;							//2 MHz out mode

	GPIO_Init(GPIOB, &GPIO_InitStructureB11);												//Init GPIOB Pin11	
	GPIO_Init(GPIOA, &GPIO_InitStructureA3);												//Init GPIOA Pin3
	GPIO_Init(GPIOC, &GPIO_InitStructureC13);												//Init GPIOC Pin13

	GPIOC->ODR ^= GPIO_ODR_ODR13;																		//toggle C13
}
