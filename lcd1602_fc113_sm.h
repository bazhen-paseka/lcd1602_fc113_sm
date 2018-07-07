#ifndef LCD1602_FC113_SM_H_
#define LCD1602_FC113_SM_H_

#include "stm32f1xx_hal.h"
#include "i2c.h"

typedef struct
{
	I2C_HandleTypeDef 	*i2c;
	uint8_t 			 device_i2c_address;
} lcd1602_fc113_struct;

void LCD1602_Print_Line             (lcd1602_fc113_struct *lcd1602_fc113_handler, char *DataChar, uint8_t);

void LCD1602_Init                   (lcd1602_fc113_struct *lcd1602_fc113_handler );
void I2C_ScanBus                    (lcd1602_fc113_struct *lcd1602_fc113_handler );
void LCD1602_Clear                  (lcd1602_fc113_struct *lcd1602_fc113_handler );
void LCD1602_Cursor_Return          (lcd1602_fc113_struct *lcd1602_fc113_handler );

void LCD1602_Display_Shift_Left     (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Display_Shift_Right    (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Cursor_Shift_Left      (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);
void LCD1602_Cursor_Shift_Right     (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t step);

	/*
	#define ADR_I2C_FC113 0x27
	uint8_t SizeChar;
	char DataChar[32];

	lcd1602_fc113_struct h1_lcd1602_fc113 =
	{
		.i2c = &hi2c1,
		.device_i2c_address = ADR_I2C_FC113
	};

	LCD1602_Init(&h1_lcd1602_fc113);
	I2C_ScanBus(&h1_lcd1602_fc113);
	sprintf(DataChar,"AB1,AB2,AB3,AB4,AB5,AB6,AB7.");
	SizeChar = strlen(DataChar);
	LCD1602_Print_Char(&h1_lcd1602_fc113, DataChar, SizeChar);
	HAL_Delay(1000);
	LCD1602_Clear(&h1_lcd1602_fc113);
	*/

#endif
