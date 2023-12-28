/*
 * bme680_code.h
 *
 *  Created on: Dec 28, 2023
 *      Author: adrian
 */

#ifndef INC_BME680_CODE_H_
#define INC_BME680_CODE_H_

/*** Neccesary includes ***/
#include "bme68x.h"
#include "main.h"
#include "i2c.h"

//#define BME680_I2C_ADDRESS 0x77

// Extern vars
extern struct bme68x_dev bme;

// Prototypes
uint8_t user_init_bme(struct bme68x_dev *bme);



#endif /* INC_BME680_CODE_H_ */
