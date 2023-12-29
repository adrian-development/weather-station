/*
 * fw_main.c
 *
 *  Created on: Dec 28, 2023
 *      Author: adrian
 */

/* Includes */
//#include "stm32l0xx_hal_tim.h"
//#include "stm32l0xx_hal_gpio.h"

#include "bme680_code.h"
#include "debug.h"
#include "main.h"
#include "tim.h"

void fw_main()
{
	uint8_t rslt = 0;

	// Start Timer for cyclic actions
	HAL_TIM_Base_Start_IT(&htim21);

	// Start Timer for us delay function
	HAL_TIM_Base_Start(&htim22);

	debug_print("Starting BME Init...\n\r");

	// Init BME
	rslt = user_init_bme();

	debug_print("BME Initialized with return %d\n\r", rslt);

	while(1)
	{
		// Blinky
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		HAL_Delay(1000);
	}
}

