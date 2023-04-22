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


/*
 * Funcion que permite establecer el numero de puerto
 * @GPOIx   el numero de puerto
 */

void set_GPIOx_Port(GPIO_TypeDef *GPIOx){
	GPIOx_Port = GPIOx;
}

/*
 * Funcion que permite establecer el numero de pin
 * @GÏO_Pin  el numero de pin
 */
void set_GPIOx_Port_Pin(uint16_t GPIO_Pin){
	GPIOx_Port_Pin = GPIO_Pin;
}


/*
 * Funcion que permite establecer para escritura el numero de puerto y numero de pin
 * @GPOIx   el numero de puerto
 * @GÏO_Pin  el numero de pin
 */
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

/*
 * Funcion que permite establecer para lectura el numero de puerto y numero de pin
 * @GPOIx   el numero de puerto
 * @GÏO_Pin  el numero de pin
 */
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


/*
 * Funcion que permite y establecer el puerto y pin para iniciar el sensor dht11
 * @GPOIx   el numero de puerto
 * @GÏO_Pin  el numero de pin
 */
void dht11_init (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	dht11_state();
	set_pin_output (GPIOx, GPIO_Pin);  // establecido el pin de salida
	dht11_start();
}

/*
 * Funcion que permite realizar un inicio  el sensor dht11
 */
void dht11_start(){

	HAL_GPIO_WritePin (GPIOx_Port, GPIOx_Port_Pin, GPIO_PIN_RESET);   // establezo el pin en bajo
	HAL_Delay(20);  // wait for 18ms
	HAL_GPIO_WritePin (GPIOx_Port, GPIOx_Port_Pin, GPIO_PIN_SET);   // establezco el ping en alto
	HAL_Delay(1);  // wait for 20us
	set_pin_input(GPIOx_Port, GPIOx_Port_Pin);    // establecer el puerto y el pin
	dht11_state();
}

/*
 * Funcion que permite inicial en estado de sleep de nuestro sensor mismo devolviendo
 * @response un numero entero sin signo que se encuentra habilitado
 */
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
	dht11_state();
}

/*
 * Funcion que permite inicial en estado de sleep de nuestro sensor mismo devolviendo
 * @response un numero entero sin signo que se encuentra habilitado
 */
uint8_t dht11_read_data (void)
{
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

/*
 * Funcion que permite gestionar nuestros estados logico de nuestro controlador
 *
 */
void dht11_state(){
	switch(state_dht11){
		OFF_DHT11:
			state_dht11 = INIT_DHT11;
			break;
		INIT_DHT11:
			state_dht11 = READY_DHT11;
			break;
		READY_DHT11:
			state_dht11 = READ_DHT11;
			break;
		default:
			break;
	}

}
