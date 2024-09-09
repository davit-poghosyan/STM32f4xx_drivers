/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Sep 4, 2024
 *      Author: davit
 */


#include "stm32f407xx_gpio_driver.h"


void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;

	//configuring the mode of gpio pin
	if (pGPIOHandle->GPIO_PinCongig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		temp = pGPIOHandle->GPIO_PinCongig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//clearing
		pGPIOHandle->pGPIOx->MODER |= temp;//setting
	} else {
		if (pGPIOHandle->GPIO_PinCongig.GPIO_PinMode == GPIO_MODE_IT_FT) {
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//Clearing correspoding RTSR bit
		} else if (pGPIOHandle->GPIO_PinCongig.GPIO_PinMode == GPIO_MODE_IT_RT){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//Clearing correspoding FTSR bit
		} else if (pGPIOHandle->GPIO_PinCongig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
		}

		//Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber;
	}

	temp = 0;

	//configuring the speed
	temp = pGPIOHandle->GPIO_PinCongig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	//configuring the pupd settings
	temp = pGPIOHandle->GPIO_PinCongig.GPIO_PinPupdControl << (2 * pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	//configuring the optype
	temp = pGPIOHandle->GPIO_PinCongig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	if (pGPIOHandle->GPIO_PinCongig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		uint32_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinCongig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF<< (4 * temp2));//clearing

		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinCongig.GPIO_PinAltFunMode << (4 * temp2));
	}
}



void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA) {
			GPIOA_REG_RESET();
		}
		else if (pGPIOx == GPIOB) {
			GPIOB_REG_RESET();
		}
		else if (pGPIOx == GPIOC) {
			GPIOC_REG_RESET();
		}
		else if (pGPIOx == GPIOD) {
			GPIOD_REG_RESET();
		}
		else if (pGPIOx == GPIOE) {
			GPIOE_REG_RESET();
		}
		else if (pGPIOx == GPIOF) {
			GPIOF_REG_RESET();
		}
		else if (pGPIOx == GPIOG) {
			GPIOG_REG_RESET();
		}
		else if (pGPIOx == GPIOH) {
			GPIOH_REG_RESET();
		}
		else if (pGPIOx == GPIOI) {
			GPIOI_REG_RESET();
		}
}


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE) {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_EN();
		}
		else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_EN();
		}
		else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_EN();
		}
		else if (pGPIOx == GPIOI) {
			GPIOI_PCLK_EN();
		}

	} else {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_DI();
			}
		else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOF) {
			GPIOF_PCLK_DI();
		}
		else if (pGPIOx == GPIOG) {
			GPIOG_PCLK_DI();
		}
		else if (pGPIOx == GPIOH) {
			GPIOH_PCLK_DI();
		}
		else if (pGPIOx == GPIOI) {
			GPIOI_PCLK_DI();
			}
	}
}


uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber)  & 0x00000001);
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET) {
		pGPIOx->ODR |= (1 << PinNumber);
	} else {
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDI);
void GPIO_IRQHandling(uint8_t PinNumber);

