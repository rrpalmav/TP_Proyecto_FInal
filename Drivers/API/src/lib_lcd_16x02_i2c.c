/*
 * lib_lcd_16x02_i2c.C
 *
 *  Created on: Apr 13, 2023
 *      Author: palmaventura
 */

#include "lib_lcd_16x02_i2c.h"

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_hal_i2c.h"


//#define SLAVE_ADDRESS_LCD 0x40 // Direccion de esclavo binario enviado   01000000
//#define SLAVE_ADDRESS_LCD 0x42 // Direccion de esclavo binario enviado   01000010
//#define SLAVE_ADDRESS_LCD 0x44 // Direccion de esclavo binario enviado   01000100
//#define SLAVE_ADDRESS_LCD 0x48 // Direccion de esclavo binario enviado   01001000
//#define SLAVE_ADDRESS_LCD 0x46 // Direccion de esclavo binario enviado   01000110
//#define SLAVE_ADDRESS_LCD 0x4A // Direccion de esclavo binario enviado   01001010
//#define SLAVE_ADDRESS_LCD 0x4C // Direccion de esclavo binario enviado   01001100
#define SLAVE_ADDRESS_LCD 0x4E // Direccion de esclavo binario enviado   01001110

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly


static lcd_16x02State_t state_lcd_16x02 = OFF_LCD_16x02;
uint8_t current_row_lcd_16x02;
uint8_t current_column_lcd_16x02;


/*
 * Funcion que permite realizar el inicio de la lcd_16x02
 */

void lcd_16x02_init (void)
{
	// 4 bits para inicializacion
	lcd_16x02_state(0);
	HAL_Delay(50);  				// realizar espera de 40ms
	lcd_16x02_send_cmd (0x30);
	HAL_Delay(5);   				// realizar espera de 4.1ms
	lcd_16x02_send_cmd (0x30);
	HAL_Delay(1);  					// realizar espera de 1ms
	lcd_16x02_send_cmd (0x30);
	HAL_Delay(10);
	lcd_16x02_send_cmd (0x20);  	// realiza el envio de modo 4bit
	HAL_Delay(10);

  // dislay initialisation
	lcd_16x02_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_16x02_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_16x02_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_16x02_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_16x02_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	current_row_lcd_16x02 = 1;
	current_column_lcd_16x02 = 1;
	lcd_16x02_gotoxy(current_row_lcd_16x02, current_column_lcd_16x02);
	lcd_16x02_state(0);
}


/*
 * Funcion que permite transmitir un mensaje de comando para eatablecer para lectura el numero de puerto y numero de pin
 * @cmd el caracter que especifica la instruccion especifica
 */
void lcd_16x02_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

/*
 * Funcion que permite transmitir un mensaje de comando para eatablecer para lectura el numero de puerto y numero de pin
 * @GPOIx   el numero de puerto
 * @GÏO_Pin  el numero de pin
 */
void lcd_16x02_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 1000);
}

/*
 * Funcion que permite limpiar la pantalla misma del LCD 16x02
 */
void lcd_16x02_clear (void)
{
	lcd_16x02_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_16x02_send_data(' ');
	}
}

/*
 * Funcion que permite posicionarme dentro de una ubicacion de la pantalla
 * @y la posicion de la fila 1-2
 * @x la posicion de la columna  1-16
 */
void lcd_16x02_gotoxy(int y, int x)
{
	if(x < 1 && x > 16) {
		state_lcd_16x02 = ERROR_LCD_16x02;
		x = 1;
	}
	if(y < 1 && y > 2) {
		state_lcd_16x02 = ERROR_LCD_16x02;
		y = 1;
	}
	x = x - 1;
    switch (y)
    {
        case 1:
            x |= 0x80;
            break;
        case 2:
            x |= 0xC0;
            break;
    }
    lcd_16x02_send_cmd (x);
}


/*
 * Funcion que realizar transiciones de estado de nuestra libreria como tal

 */
void lcd_16x02_state(int msg){

	switch(state_lcd_16x02){
		OFF_LCD_16x02:
			state_lcd_16x02 = INIT_LCD_16x02;
			break;
		INIT_LCD_16x02:
			state_lcd_16x02 = READY_LCD_16x02;
			break;
		READY_LCD_16x02:
			state_lcd_16x02 = SEND_LCD_16x02;
			break;
		SEND_LCD_16x02:
			state_lcd_16x02 = SENDING_LCD_16x02;
			break;
		SENDING_LCD_16x02:
			if(msg == 0) state_lcd_16x02 = SEND_LCD_16x02;
			if(msg == 1) state_lcd_16x02 = ERROR_LCD_16x02;
			break;
		default:
			break;

	}
}


/*
 * Funcion que permite realizar el envio de nuestro
 */
void lcd_16x02_send_string (char *str)
{
	while (*str){
		if(++current_column_lcd_16x02 > MAX_SIZE_LCD_16X02_I2C_COLUMN){
			state_lcd_16x02 = ERROR_LCD_16x02;
			current_column_lcd_16x02 = 1;
			if(++current_row_lcd_16x02> MAX_SIZE_LCD_16X02_I2C_ROW){
				current_row_lcd_16x02 = 1;
			}
			lcd_16x02_gotoxy(current_row_lcd_16x02, current_column_lcd_16x02);
		}
		lcd_16x02_send_data (*str++);
	}
}

