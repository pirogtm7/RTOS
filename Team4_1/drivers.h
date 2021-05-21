#include "stm32f10x.h"

void initGPIODrivers(void);

void PWMDrivers(uint32_t GPIOAWorkTime, uint32_t GPIOBWorkTime, uint32_t period);

void _delay_ms_dr(uint32_t ms);
