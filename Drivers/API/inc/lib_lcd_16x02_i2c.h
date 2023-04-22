/*
 * LCD_16x02_I2c.h
 *
 *  Created on: Apr 13, 2023
 *      Author: palmaventura
 */

#ifndef LIB_LCD_16X02_I2C_H
#define LIB_LCD_16X02_I2C_H


#define MAX_SIZE_LCD_16X02_I2C_ROW 		2
#define MAX_SIZE_LCD_16X02_I2C_COLUMN 	16

typedef enum {
	OFF_LCD_16x02,
	INIT_LCD_16x02,
	READY_LCD_16x02,
	SEND_LCD_16x02,
	SENDING_LCD_16x02,
	ERROR_LCD_16x02
} lcd_16x02State_t;

void lcd_16x02_init (void);   // inicializa lcd_16x02
void lcd_16x02_send_cmd (char cmd);  // envia commando a la lcd_16x20
void lcd_16x02_send_data (char data);  // envia data a la lcd_16x02
void lcd_16x02_send_string (char *str);  // envia cadenas a la ldc_16x02
void lcd_16x02_gotoxy(int y, int x);  // posiciona el curso ne la posicion fila (1 or 2), col (1-16);
void lcd_16x02_clear (void);
void lcd_16x02_state(int msg);

#endif /* LIB_LCD_16X02_I2C_H_ */
