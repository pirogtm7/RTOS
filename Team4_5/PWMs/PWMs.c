#include "PWMs.h"

void PWM2(uint32_t workTime, uint32_t period)
{
		GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
		osDelay(workTime);
		GPIOC->ODR ^= GPIO_ODR_ODR13;																//toggle C13
		osDelay(period - workTime);
}

void PWM3(uint32_t workTime, uint32_t period)
{
		GPIOA->ODR ^= GPIO_ODR_ODR3;																//toggle A3
		osDelay(workTime);
		GPIOA->ODR ^= GPIO_ODR_ODR3;																//toggle A3
		osDelay(period - workTime);
}
