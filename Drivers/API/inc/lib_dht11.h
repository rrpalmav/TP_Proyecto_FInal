/*
 * lib_dht11.h
 *
 *  Created on: Apr 17, 2023
 *      Author: palmaventura
 */

#ifndef INC_LIB_DHT11_H
#define INC_LIB_DHT11_H

#include "stdint.h"
#include "stm32f4xx_hal.h"

typedef enum {
	OFF_DHT11,
	INIT_DHT11,
	READY_DHT11,
	READ_DHT11,
	ERROR_DHT11
} dht11State_t;

void dht11_init (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void dht11_start();
uint8_t dht11_check_response (void);
uint8_t dht11_read_data (void);
void set_pin_output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void set_pin_input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void set_GPIOx_Port(GPIO_TypeDef *GPIOx);
void set_GPIOx_Port_Pin(uint16_t GPIO_Pin);
void dht11_state();

#endif /* INC_LIB_DHT11_H */
