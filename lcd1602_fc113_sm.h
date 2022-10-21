#ifndef LCD1602_FC113_SM_H_
#define LCD1602_FC113_SM_H_

//*******************************************************************

	#include "main.h"
	#include "lcd1602_local_config.h"
	#include "string.h"
	#include "stdio.h"
#ifdef LCD1602
	#include "i2c.h"

//*******************************************************************

	typedef struct
	{
		I2C_HandleTypeDef 	*i2c;
		uint8_t 			 device_i2c_address;
	} lcd1602_fc113_struct;

//*******************************************************************

void LCD1602_Print_Line             (lcd1602_fc113_struct *lcd1602_fc113_handler, char *DataChar, uint8_t);

void LCD1602_Init                   (lcd1602_fc113_struct *lcd1602_fc113_handler );
void LCD1602_Scan_I2C_bus			(lcd1602_fc113_struct *lcd1602_fc113_handler );
void LCD1602_Scan_I2C_to_UART		(lcd1602_fc113_struct *lcd1602_fc113_handler, UART_HandleTypeDef * _huart);
void LCD1602_Clear                  (lcd1602_fc113_struct *lcd1602_fc113_handler );
void LCD1602_Cursor_Return          (lcd1602_fc113_struct *lcd1602_fc113_handler );

void LCD1602_Display_Shift_Left     (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Display_Shift_Right    (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Cursor_Shift_Left      (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Cursor_Shift_Right     (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);

	/*
	  	#include <string.h>
		#include "lcd1602_fc113_sm.h"

		char uart_buffer_c[100];
		#define ADR_I2C_FC113 0x27

		lcd1602_fc113_struct h1_lcd1602_fc113 =
		{
			.i2c = &hi2c1,
			.device_i2c_address = ADR_I2C_FC113
		};

		LCD1602_Init(&h1_lcd1602_fc113);
		LCD1602_Scan_I2C_bus(&h1_lcd1602_fc113);

		LCD1602_Clear(&h1_lcd1602_fc113);
		sprintf(uart_buffer_c,"Steps Counter\r\n");
		LCD1602_Print_Line(&h1_lcd1602_fc113, uart_buffer_c, strlen(uart_buffer_c));

		sprintf(uart_buffer_c," STP100M\r\n");
		LCD1602_Print_Line(&h1_lcd1602_fc113, uart_buffer_c, strlen(uart_buffer_c));

		HAL_Delay(1000);
		LCD1602_Clear(&h1_lcd1602_fc113);
	*/

#endif
#endif
