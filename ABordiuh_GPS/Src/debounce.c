/*
 * debounce.c
 *
 *  Created on: Dec 23, 2016
 *      Author: rhofer
 */
/* FUNCTION      : deBouncePinInit
* DESCRIPTION   : initializes a pin for input pullup pullup or
* 			      pulldown so it can be read
* PARAMETERS    : int16_t Pin - the pin to be configured
* 				  char port - either A, B or C for PortA, B or C
*		          int8_t mode – 1 = pullup or 0 = pulldown
*
* RETURNS       : nothing
* */
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"

void deBounceInit(int16_t pin, char port, int8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pin : */
	switch(pin)
	{
		case 0: GPIO_InitStruct.Pin = GPIO_PIN_0; break;
		case 1: GPIO_InitStruct.Pin = GPIO_PIN_1; break;
		case 2: GPIO_InitStruct.Pin = GPIO_PIN_2; break;
		case 3: GPIO_InitStruct.Pin = GPIO_PIN_3; break;
		case 4: GPIO_InitStruct.Pin = GPIO_PIN_4; break;
		case 5: GPIO_InitStruct.Pin = GPIO_PIN_5; break;
		case 6: GPIO_InitStruct.Pin = GPIO_PIN_6; break;
		case 7: GPIO_InitStruct.Pin = GPIO_PIN_7; break;
		case 8: GPIO_InitStruct.Pin = GPIO_PIN_8; break;
		case 9: GPIO_InitStruct.Pin = GPIO_PIN_9; break;
		case 10: GPIO_InitStruct.Pin = GPIO_PIN_10; break;
		case 11: GPIO_InitStruct.Pin = GPIO_PIN_11; break;
		case 12: GPIO_InitStruct.Pin = GPIO_PIN_12; break;
		case 13: GPIO_InitStruct.Pin = GPIO_PIN_13; break;
		case 14: GPIO_InitStruct.Pin = GPIO_PIN_14; break;
		case 15: GPIO_InitStruct.Pin = GPIO_PIN_15; break;
	}
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	switch (mode)
	{
		case 0: GPIO_InitStruct.Pull = GPIO_PULLDOWN; break;
		case 1: GPIO_InitStruct.Pull = GPIO_PULLUP; break;
	}
	switch (port)
	{
		case 'A': HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); break;
		case 'B': HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); break;
		case 'C': HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); break;
	}
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int8_t deBounceReadPin(int16_t pin, char port, int8_t stableInterval)
{
	GPIO_PinState pinState = GPIO_PIN_RESET;	//remember variables should be initialized
	int8_t pinStateWeAreLookingFor = 0;
	int32_t msTimeStamp = HAL_GetTick();		//get a timeStamp in ms

	GPIO_InitTypeDef GPIO_InitStruct;
		/*Configure GPIO pin : */
		switch(pin)
		{
			case 0: GPIO_InitStruct.Pin = GPIO_PIN_0; break;
			case 1: GPIO_InitStruct.Pin = GPIO_PIN_1; break;
			case 2: GPIO_InitStruct.Pin = GPIO_PIN_2; break;
			case 3: GPIO_InitStruct.Pin = GPIO_PIN_3; break;
			case 4: GPIO_InitStruct.Pin = GPIO_PIN_4; break;
			case 5: GPIO_InitStruct.Pin = GPIO_PIN_5; break;
			case 6: GPIO_InitStruct.Pin = GPIO_PIN_6; break;
			case 7: GPIO_InitStruct.Pin = GPIO_PIN_7; break;
			case 8: GPIO_InitStruct.Pin = GPIO_PIN_8; break;
			case 9: GPIO_InitStruct.Pin = GPIO_PIN_9; break;
			case 10: GPIO_InitStruct.Pin = GPIO_PIN_10; break;
			case 11: GPIO_InitStruct.Pin = GPIO_PIN_11; break;
			case 12: GPIO_InitStruct.Pin = GPIO_PIN_12; break;
			case 13: GPIO_InitStruct.Pin = GPIO_PIN_13; break;
			case 14: GPIO_InitStruct.Pin = GPIO_PIN_14; break;
			case 15: GPIO_InitStruct.Pin = GPIO_PIN_15; break;
		}


	/* let's do our first read of the pin
	 * and to do that we need to incorporate the port we're going to read*/
	switch (port)
	{
		case 'A': pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_InitStruct.Pin); break;
		case 'B': pinState = HAL_GPIO_ReadPin(GPIOB, GPIO_InitStruct.Pin); break;
		case 'C': pinState = HAL_GPIO_ReadPin(GPIOC, GPIO_InitStruct.Pin); break;
	}
	/* is the GPIO pin high or low 	 */
	if(pinState == GPIO_PIN_RESET )		// if low we're looking for more 0's
	{
		pinStateWeAreLookingFor = 0;
	}
	else
	{//we're looking for more 1's
		pinStateWeAreLookingFor = 1;
	}

	/* now, let's read the pin again until x stable ms have elapsed */
	while (HAL_GetTick() < (msTimeStamp + stableInterval))
	{

		switch (port)
		{
			case 'A': pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_InitStruct.Pin); break;
			case 'B': pinState = HAL_GPIO_ReadPin(GPIOB, GPIO_InitStruct.Pin); break;
			case 'C': pinState = HAL_GPIO_ReadPin(GPIOC, GPIO_InitStruct.Pin); break;
		}
		if(pinState != pinStateWeAreLookingFor)
		{
			pinStateWeAreLookingFor = !pinStateWeAreLookingFor;
			/* reset the timeStamp as we've had a change in state			 */
			msTimeStamp = HAL_GetTick();
		}
	}
	return (pinStateWeAreLookingFor);
}


