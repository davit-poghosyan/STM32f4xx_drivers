/*
 * 001led_toggle.c
 *
 *  Created on: Sep 5, 2024
 *      Author: davit
 */

#include "stm32f407xx.h"

void delay(void)
{
	for (uint32_t i = 0; i < 1500000; i++);
}
int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinCongig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinCongig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinCongig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinCongig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GpioLed.GPIO_PinCongig.GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&GpioLed);

	while(1) {
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		delay();
	}
}


