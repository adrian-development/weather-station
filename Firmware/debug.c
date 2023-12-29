/*
 * debug.c
 *
 *  Created on: Dec 28, 2023
 *      Author: adrian
 */

#include "debug.h"
#include "usart.h"
#include "stm32l0xx_hal.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void debug_print(const char *format, ...)
{
    char buffer[256]; // Adjust the buffer size as needed
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
}


