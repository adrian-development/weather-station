/*
 * bme680_code.c
 *
 *  Created on: Dec 28, 2023
 *      Author: adrian
 */

/*** Includes ****/
#include "main.h"
#include "bme680_code.h"
#include "tim.h"
#include "debug.h"
#include "bme68x.h"
#include "i2c.h"


/*** Global vars***/


/*** Module Global Vars ***/
static struct bme68x_dev bme;
static uint8_t dev_addr;

/*** Prototypes ***/
BME68X_INTF_RET_TYPE bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
BME68X_INTF_RET_TYPE bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
void bme68x_delay_us(uint32_t period, void *intf_ptr);


uint8_t user_init_bme()
{
	// Init config vars
	int8_t rslt = BME68X_OK;
    struct bme68x_conf conf;
    struct bme68x_heatr_conf heatr_conf;
    struct bme68x_data data;
    uint32_t del_period;
    uint32_t time_ms = 0;
    uint8_t n_fields;
    uint16_t sample_count = 1;

	// Set I2C Address
	dev_addr = BME68X_I2C_ADDR_HIGH;

	// Init struct
	bme.read = bme68x_i2c_read;
	bme.write = bme68x_i2c_write;
	bme.intf = BME68X_I2C_INTF;
	bme.delay_us = bme68x_delay_us;
	bme.intf_ptr = &dev_addr;
	bme.amb_temp = 20; /* The ambient temperature in deg C is used for defining the heater temperature */

    // Run API init
    rslt = bme68x_init(&bme);
    debug_print("API Init: %d\n\r",rslt);

    // Config Filter
    conf.filter = BME68X_FILTER_OFF;
    conf.odr = BME68X_ODR_NONE;
    conf.os_hum = BME68X_OS_16X;
    conf.os_pres = BME68X_OS_1X;
    conf.os_temp = BME68X_OS_2X;
    rslt = bme68x_set_conf(&conf, &bme);

    // Config heater
    heatr_conf.enable = BME68X_ENABLE;
    heatr_conf.heatr_temp = 300;
    heatr_conf.heatr_dur = 100;
    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, &bme);

    // Read Values
    while (sample_count <= 300)
        {
            rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, &bme);
            //debug_print("Set op mode: %d\n\r", rslt);

            /* Calculate delay period in microseconds */
            del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, &bme) + (heatr_conf.heatr_dur * 1000);
            bme.delay_us(del_period, bme.intf_ptr);

            time_ms = HAL_GetTick();

            /* Check if rslt == BME68X_OK, report or handle if otherwise */
            rslt = bme68x_get_data(BME68X_FORCED_MODE, &data, &n_fields, &bme);
            //debug_print("Get Data: %d\n\r", rslt);

            if(n_fields)
            {

            	debug_print("Sample: %u, Time: %lu, Temp: %d, Pres: %lu, Hum: %lu, Gas: %lu, Stat: 0x%x\n\r",
                       sample_count,
                       (long unsigned int)time_ms,
                       (data.temperature / 100),
                       (long unsigned int)data.pressure,
                       (long unsigned int)(data.humidity / 1000),
                       (long unsigned int)data.gas_resistance,
                       data.status);

                sample_count++;
            }
            HAL_Delay(100);
        }


	return 0;
}

uint8_t bme_run_measurement()
{
	return 0;
}

// Wrapper code to map I2C read
BME68X_INTF_RET_TYPE bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
	HAL_StatusTypeDef ret;

    uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;

    ret = HAL_I2C_Mem_Read(&hi2c1, (uint16_t)(device_addr<<1), (uint16_t)reg_addr,
    		(uint16_t)sizeof(uint8_t), (uint8_t *)reg_data, (uint16_t)len, 100);

    return ret;
}

// Wrapper code to map I2C write
BME68X_INTF_RET_TYPE bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
	HAL_StatusTypeDef ret;

    uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;

    ret = HAL_I2C_Mem_Write(&hi2c1, (uint16_t)(device_addr<<1), (uint16_t)reg_addr,
                                        (uint16_t) sizeof(reg_addr), (uint8_t *)reg_data, (uint16_t)len, 100);

    return ret;
}

// Wrapper code to map delay function
void bme68x_delay_us(uint32_t period, void *intf_ptr)
{
	(void)intf_ptr;

	// Check if time is over 16 bit, timer has only 16 bit
	if (period > 60000)
	{
		// Transfer us -> ms and use HAL function to wait
		uint32_t period_ms = (period / 1000);
		HAL_Delay(period_ms);

		// Calculate remaining us
		period -= period_ms * 1000;
	}


	// set the counter value to 0
	__HAL_TIM_SET_COUNTER(&htim22,0);
	// wait for the counter to reach the us input in the parameter
	while (__HAL_TIM_GET_COUNTER(&htim22) < period);

}
