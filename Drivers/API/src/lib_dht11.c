/*
 * lib_dht11.c
 *
 *  Created on: Apr 17, 2023
 *      Author: palmaventura
 */

#include "lib_dht11.h"
#include "stdio.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"


static dht11State_t state_dht11 = OFF_DHT11;

GPIO_TypeDef *GPIOx_Port;
uint16_t GPIOx_Port_Pin;


void set_GPIOx_Port(GPIO_TypeDef *GPIOx){
	GPIOx_Port = GPIOx;
}

void set_GPIOx_Port_Pin(uint16_t GPIO_Pin){
	GPIOx_Port_Pin = GPIO_Pin;
}


void set_pin_output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	set_GPIOx_Port(GPIOx);
	set_GPIOx_Port_Pin(GPIO_Pin);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void set_pin_input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	set_GPIOx_Port(GPIOx);
	set_GPIOx_Port_Pin(GPIO_Pin);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}


void dht11_init (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	set_pin_output (GPIOx, GPIO_Pin);  // establecido el pin de salida
	dht11_start();

}

void dht11_start(){
	state_dht11 = INIT_DHT11;
	HAL_GPIO_WritePin (GPIOx_Port, GPIOx_Port_Pin, GPIO_PIN_RESET);   // pull the pin low
	HAL_Delay(20);  // wait for 18ms
	HAL_GPIO_WritePin (GPIOx_Port, GPIOx_Port_Pin, GPIO_PIN_SET);   // pull the pin high
	HAL_Delay(1);  // wait for 20us
	set_pin_input(GPIOx_Port, GPIOx_Port_Pin);    // set as input
}


uint8_t dht11_check_response (void)
{

	uint8_t respuesta = 0;
	HAL_Delay(40);
	if (! (HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin)))
	{
		HAL_Delay(80);
		if ((HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin))) respuesta = 1;
		else respuesta = -1; // 255
	}
	while ((HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin)));   // wait for the pin to go low

	return respuesta;
	state_dht11 = READY_DHT11;
}

uint8_t dht11_read_data (void)
{
	state_dht11 = READ_DHT11;
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin)));   // wait for the pin to go high
		HAL_Delay(40);
		if (!(HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin)))   // if the pin is low
		{
			i&= ~(1<<(7-j));   // write 0
		}
		else i|= (1<<(7-j));  // if the pin is high, write 1
		while ((HAL_GPIO_ReadPin (GPIOx_Port, GPIOx_Port_Pin)));  // wait for the pin to go low
	}
	return i;
}
