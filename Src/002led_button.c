/*
 * 002led_button.c
 *
 *  Created on: Sep 5, 2024
 *      Author: davit
 */


#include "stm32f407xx.h"

void delay(void)
{
	for (uint32_t i = 0; i < 500000/2; i++);
}



int main(void)
{
	GPIO_Handle_t gpioLed, gpioBtn;


	gpioBtn.pGPIOx = GPIOA;
	gpioBtn.GPIO_PinCongig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpioBtn.GPIO_PinCongig.GPIO_PinMode = GPIO_MODE_IN;
	gpioBtn.GPIO_PinCongig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioBtn.GPIO_PinCongig.GPIO_PinPupdControl = GPIO_NO_PUPD;


	gpioLed.pGPIOx = GPIOD;
	gpioLed.GPIO_PinCongig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioLed.GPIO_PinCongig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.GPIO_PinCongig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinCongig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLed.GPIO_PinCongig.GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&gpioLed);
	GPIO_Init(&gpioBtn);



	while(1) {
		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)) {
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			delay();
		}
	}
}


