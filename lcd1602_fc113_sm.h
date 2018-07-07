
#include "stm32f1xx_hal.h"
#include "i2c.h"

void LCD1602_Write_Instruction_4bit(uint8_t);
void LCD1602_Write_Instruction_8bit(uint8_t);
void LCD1602_Write_Data(uint8_t);
void LCD1602_Init(void);
void LCD1602_Clear(void);
void LCD1602_Cursor_Shift_Right(uint32_t input);
void LCD1602_Cursor_Shift_Left(uint32_t input);
void LCD1602_Display_Shift_Left(uint32_t input);
void LCD1602_Display_Shift_Right(uint32_t input);
void LCD1602_Cursor_Return(void);
void I2C_ScanBus(void);
void LCD1602_Print_Char(uint8_t *DataChar, int32_t);
