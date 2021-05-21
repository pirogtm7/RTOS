#include "button_checks.h"

char checkButtonClick(void)
{
	uint32_t pin = GPIOB->IDR & GPIO_IDR_IDR11;										//Return Input Data Register value for B11
	if (!pin){																										//Check if value is 0x00 (button is pressed)
		return TRUE;																								
	}
	return FALSE;
	//return TRUE;
}
