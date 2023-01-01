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

	typedef enum {
		LED_OFF	,
		LED_ON
	} LED_status ;

	typedef struct {
		I2C_HandleTypeDef 	*i2c;
		uint8_t 			 device_i2c_address;
	} lcd1602_handle;

//*******************************************************************

void LCD1602_Init                ( lcd1602_handle*	hlcd1602 );
void LCD1602_Print_Line          ( lcd1602_handle*	hlcd1602 ,
								   char*			DataChar ,
								   uint8_t			SizeChar ,
								   LED_status 		led_st   );

void LCD1602cursorToFirstPosition( lcd1602_handle*	hlcd1602, LED_status led_st );
void LCD1602_Clear               ( lcd1602_handle*	hlcd1602 );

void LCD1602_Scan_I2C_bus		 ( lcd1602_handle*		hlcd1602 );
void LCD1602_Scan_I2C_to_UART	 ( I2C_HandleTypeDef*	_i2c,
								   UART_HandleTypeDef*	_huart );

void LCD1602_Cursor_Return       ( lcd1602_handle*		hlcd1602 );

void LCD1602_Display_Shift_Left  ( lcd1602_handle*	hlcd1602, uint8_t step );
void LCD1602_Display_Shift_Right ( lcd1602_handle*	hlcd1602, uint8_t step );
void LCD1602_Cursor_Shift_Left   ( lcd1602_handle*	hlcd1602, uint8_t step );
void LCD1602_Cursor_Shift_Right  ( lcd1602_handle*	hlcd1602, uint8_t step );


/*
	#include <string.h>
	#include "lcd1602_fc113_sm.h"

	char uart_buffer_c[100];
	#define ADR_I2C_FC113 0x27

	lcd1602_handle hlcd1602 = {
		.i2c = &hi2c1,
		.device_i2c_address = ADR_I2C_FC113
	};

	LCD1602_Init(&hlcd1602);
	LCD1602_Scan_I2C_bus(&hlcd1602);

	LCD1602_Clear(&hlcd1602);
	sprintf(uart_buffer_c,"Steps Counter\r\n");
	LCD1602_Print_Line(&hlcd1602, uart_buffer_c, strlen(uart_buffer_c), LED_ON);

	sprintf(uart_buffer_c," STP100M\r\n");
	LCD1602_Print_Line(&hlcd1602, uart_buffer_c, strlen(uart_buffer_c), LED_ON);

	HAL_Delay(1000);
	LCD1602_Clear(&hlcd1602);
*/

#endif
#endif
