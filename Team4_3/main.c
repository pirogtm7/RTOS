#include "main.h"

//Vira Pyrih, Olena Fedchuk, IT-81

int main(void){
	initGPIO();
	TIM4_Init();
	
	osKernelInitialize();
	osThreadNew(PWM1, NULL, NULL);
	osThreadNew(PWM2, NULL, NULL);
	osKernelStart();
	
	while(1){

	}
}
	

void initGPIO(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);						//Enable GPIOC clock
	
	GPIO_InitTypeDef	GPIO_InitStructureC13;												//Init structure for C13
	
	GPIO_InitStructureC13.GPIO_Pin = GPIO_Pin_13;										//GPIOC pin13
	GPIO_InitStructureC13.GPIO_Mode = GPIO_Mode_Out_PP;							//Push&Pull
	GPIO_InitStructureC13.GPIO_Speed = GPIO_Speed_2MHz;							//2 MHz out mode
	
	GPIO_Init(GPIOC, &GPIO_InitStructureC13);												//Init GPIOC Pin13
	GPIOC->ODR ^= GPIO_ODR_ODR13;																		//Toggle C13
}

void TIM4_Init(void)
{
	TIM_TimeBaseInitTypeDef timer;																	//Init Time Base structure
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						//Enable TIM4 clock
	
	TIM_TimeBaseStructInit(&timer);																	//Fill structures's fields with default values
	timer.TIM_Prescaler = 63999; 																		//Specifies the prescaler value to one tick every 1 ms
	timer.TIM_Period = 1000 - 1;																		//1 s, Specifies the period value to be loaded into the active 
																																				//Auto-Reload Register and the time interruption is generated
	TIM_TimeBaseInit(TIM4, &timer);																	//Init TIM4
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);											//Configure TIM4 to generate interruption at update(perepovnennya)
	TIM_Cmd(TIM4, ENABLE);																					//Start TIM4
	
	//Enable the Interrupt
	NVIC_InitTypeDef nvic;																					//Init Nested Vector Interrupt Controller structure
	nvic.NVIC_IRQChannel = TIM4_IRQn;																//Specify the IRQ (Interrupt ReQuest) channel
	nvic.NVIC_IRQChannelPreemptionPriority = 0;											//Set Priority
	nvic.NVIC_IRQChannelSubPriority = 0;														//Set Subpriority
	nvic.NVIC_IRQChannelCmd = ENABLE;																//Enable IRQ Channel
	NVIC_Init(&nvic);																								//Init NVIC
}
 

uint32_t ticks_delay = 0;																										//variable for global time

void TIM4_IRQHandler(void) {																								
  ticks_delay++;																														//add 1 each time interrupt happens
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);																//clear interruption bit
}


void delay(uint32_t sec) {
  uint32_t start = ticks_delay;																							//capture time the function was called
  while((ticks_delay - start) < sec);															//compare time that passed with the delay
}

void PWM1(void* argum)
{
	while(1){
	GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
	delay(1);
	GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
	delay(14);
	}
}

void PWM2(void* argum)
{
	while(1){
	delay(6);
	GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
	delay(5);
	GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
	delay(4);
	}
}
