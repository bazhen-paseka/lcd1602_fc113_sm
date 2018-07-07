#define ADR_I2C_FC113 0x27
#include "lcd1602_fc113_sm.h"

//==========================================================================
void LCD1602_Write_Instruction_4bit(uint8_t inputE0)
{
	uint8_t inputE1;
	inputE1 = inputE0 + 4;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputE0, 1, 100);
	HAL_Delay(1);
}
//==========================================================================
void LCD1602_Write_Instruction_8bit(uint8_t input)
{
	uint8_t inputStE0;
	uint8_t inputStE1;
	uint8_t inputMlE0;
	uint8_t inputMlE1;

	inputStE0 = (input & 0xF0) +8;
	inputStE1 = inputStE0 + 4;
	inputMlE0 = (input<<4) + 8;
	inputMlE1 = inputMlE0 + 4;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
}

//==========================================================================
void LCD1602_Write_Data(uint8_t input)
	{
	uint8_t inputStE0;
	uint8_t inputStE1;
	uint8_t inputMlE0;
	uint8_t inputMlE1;

	inputStE0 = (input & 0xF0) + 9;
	inputStE1 = inputStE0 + 4;
	inputMlE0 = (input<<4) + 9; //((input<<4) * 0xF0) + 1;
	inputMlE1 = inputMlE0 + 4; // LED Light
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
	}

//==========================================================================
void LCD1602_Init(void)
	{
	HAL_Delay(15);
	LCD1602_Write_Instruction_4bit(0x30);	// step 1: 0011 0000
	HAL_Delay(5);
	LCD1602_Write_Instruction_4bit(0x30);	// step 2: 0011 0000
	LCD1602_Write_Instruction_4bit(0x30);	// step 3: 0011 0000
	LCD1602_Write_Instruction_4bit(0x20);	// step 4: 0010 0000
	// 4-bit is active
	LCD1602_Write_Instruction_8bit(0x28);		// step 5: 0010 1000 NF
	LCD1602_Write_Instruction_8bit(0x08);		// step 6: 0000 1000
	LCD1602_Write_Instruction_8bit(0x01);		// step 7: 0000 0001
	LCD1602_Write_Instruction_8bit(0x06);		// step 8: 0000 0110
	LCD1602_Write_Instruction_8bit(0x0C);		// step 9: 0000 1100 CB
	}
//==========================================================================
void LCD1602_Clear(void)
{
	LCD1602_Write_Instruction_8bit(0x01); 	// 0x01 clear disp
	LCD1602_Write_Instruction_8bit(0x03);		// 0x03 cursor to start
}
//==========================================================================
void LCD1602_Cursor_Shift_Right(uint32_t input)
{
	for ( ; input>0; input--)
	{
		LCD1602_Write_Instruction_8bit(0x14);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Shift_Left(uint32_t input)
{
	for ( ; input>0; input--)
	{
		LCD1602_Write_Instruction_8bit(0x10);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Return(void)
{
		LCD1602_Write_Instruction_8bit(0x2);		// Cursor Return
}
//==========================================================================

void LCD1602_Display_Shift_Right(uint32_t input)
{
	for ( ; input>0; input--)
	{
		LCD1602_Write_Instruction_8bit(0x1C);		// Shift Display Left
	}
}
//==========================================================================

void LCD1602_Display_Shift_Left(uint32_t input)
{
	for ( ; input>0; input--)
	{
		LCD1602_Write_Instruction_8bit(0x18);		// Shift Display Right
	}
}
//==========================================================================

//======================================================================
void I2C_ScanBus(void)
{
	uint8_t i = 0;
	char DataChar[32];
	uint32_t Device =0;

	for (i = 0x07; i < 0x78; i++) {
		if (HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 10, 100) == HAL_OK)
			{
			Device++;
			switch (i)
			{
				case 0x23: sprintf(DataChar,"%d) BH-1750", (int)Device ); break;
				case 0x27: sprintf(DataChar,"%d) FC-113 ", (int)Device ); break;
				case 0x57: sprintf(DataChar,"%d) AT24C32", (int)Device ); break;
				case 0x68: sprintf(DataChar,"%d) DS-3231", (int)Device ); break;
				case 0x76: sprintf(DataChar,"%d) BMP-280", (int)Device ); break;
				case 0x77: sprintf(DataChar,"%d) BMP-180", (int)Device ); break;
				default:   sprintf(DataChar,"%d) Unknown", (int)Device ); break;
			}// end switch

			LCD1602_Print_Char((uint8_t *)DataChar, strlen(DataChar));

			if (Device%2 == 0)
				{
				HAL_Delay(1000);
				LCD1602_Clear();
				}
			else
				{
				HAL_Delay(400);
				LCD1602_Cursor_Shift_Right(30);
				}
		} //end if HAL I2C

	}// end for i
	sprintf(DataChar,"Scan I2C End.\n");
	LCD1602_Print_Char((uint8_t *)DataChar, strlen(DataChar));

	HAL_Delay(500);
}// end void I2C_ScanBus
//======================================================================

//=================================================================

void LCD1602_Print_Char(uint8_t *DataChar, int32_t SizeChar)
	{
	for (int i=0; i<SizeChar; i++)
		{
		if (DataChar[i] != '\n')
			LCD1602_Write_Data(DataChar[i]);

		if (DataChar[i] == '\n')
			LCD1602_Cursor_Shift_Right(40-i);

		if (i == 15)
			LCD1602_Cursor_Shift_Right(40-i-1);

		}
	}
//=================================================================

