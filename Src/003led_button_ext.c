/*
 * 003led_button_ext.c
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


	gpioBtn.pGPIOx = GPIOB;
	gpioBtn.GPIO_PinCongig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioBtn.GPIO_PinCongig.GPIO_PinMode = GPIO_MODE_IN;
	gpioBtn.GPIO_PinCongig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioBtn.GPIO_PinCongig.GPIO_PinPupdControl = GPIO_PIN_PU;


	gpioLed.pGPIOx = GPIOA;
	gpioLed.GPIO_PinCongig.GPIO_PinNumber = GPIO_PIN_NO_8;
	gpioLed.GPIO_PinCongig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.GPIO_PinCongig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinCongig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLed.GPIO_PinCongig.GPIO_PinPupdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_PeriClockControl(GPIOB, ENABLE);

	GPIO_Init(&gpioLed);
	GPIO_Init(&gpioBtn);



	while(1) {
		if (GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == 1) {
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
		}

	}
}
