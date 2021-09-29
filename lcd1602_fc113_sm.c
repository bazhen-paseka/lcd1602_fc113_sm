
#include "lcd1602_fc113_sm.h"

static void LCD1602_Write_Data             (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t input);
static void LCD1602_Write_Instruction_4bit (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t input);
static void LCD1602_Write_Instruction_8bit (lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t input);
//==========================================================================

void LCD1602_Write_Data(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t input)
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
	//HAL_I2C_Master_Transmit(&hi2c1, ADR_I2C_FC113<<1, &inputStE1, 1, 100);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
}

//==========================================================================
void LCD1602_Write_Instruction_4bit(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t inputE0)
{
	uint8_t inputE1;
	inputE1 = inputE0 + 4;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputE0, 1, 100);
	HAL_Delay(1);
}
//==========================================================================

void LCD1602_Write_Instruction_8bit(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t input)
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
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(lcd1602_fc113_handler->i2c, lcd1602_fc113_handler->device_i2c_address<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
}
//==========================================================================

void LCD1602_Init(lcd1602_fc113_struct *lcd1602_fc113_handler )
{
	HAL_Delay(15);
	LCD1602_Write_Instruction_4bit(lcd1602_fc113_handler, 0x30);	// step 1: 0011 0000
	HAL_Delay(5);
	LCD1602_Write_Instruction_4bit(lcd1602_fc113_handler, 0x30);	// step 2: 0011 0000
	LCD1602_Write_Instruction_4bit(lcd1602_fc113_handler, 0x30);	// step 3: 0011 0000
	LCD1602_Write_Instruction_4bit(lcd1602_fc113_handler, 0x20);	// step 4: 0010 0000
	// 4-bit is active
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x28);	// step 5: 0010 1000 NF
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x08);	// step 6: 0000 1000
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x01);	// step 7: 0000 0001
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x06);	// step 8: 0000 0110
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x0C);	// step 9: 0000 1100 CB
}
//==========================================================================
void LCD1602_Clear(lcd1602_fc113_struct *lcd1602_fc113_handler)
{
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x01); 	// 0x01 clear disp
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x03);	// 0x03 cursor to start
}
//==========================================================================
void LCD1602_Cursor_Shift_Right(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t _step)
{
	for ( ; _step > 0; _step--)
	{
		LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x14);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Shift_Left(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t _step)
{
	for ( ; _step > 0; _step--)
	{
		LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x10);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Return(lcd1602_fc113_struct *lcd1602_fc113_handler)
{
	LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x2);		// Cursor Return
}
//==========================================================================

void LCD1602_Display_Shift_Right(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t _step)
{
	for ( ; _step > 0; _step--)
	{
		LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x1C);		// Shift Display
	}
}
//==========================================================================

void LCD1602_Display_Shift_Left(lcd1602_fc113_struct *lcd1602_fc113_handler, uint8_t _step)
{
	for ( ; _step > 0; _step--)
	{
		LCD1602_Write_Instruction_8bit(lcd1602_fc113_handler, 0x18);		// Shift Display
	}
}
//==========================================================================

void LCD1602_Print_Line(lcd1602_fc113_struct *lcd1602_fc113_handler, char* DataChar, uint8_t SizeChar)
{
	for (uint8_t i=0; i<SizeChar; i++)
	{
		if ( (DataChar[i] == '\r') || (DataChar[i] == '\n') )
		{
			//LCD1602_Write_Data(lcd1602_fc113_handler, ' ');	// print "Space"
		}
		else
		{
			LCD1602_Write_Data(lcd1602_fc113_handler, DataChar[i]);
		}

		if (DataChar[i] == '\n')
		{
			LCD1602_Cursor_Shift_Right(lcd1602_fc113_handler, 40-i);
		}

		if (i == 15)
		{
			LCD1602_Cursor_Shift_Right(lcd1602_fc113_handler, 40-i-1);
		}
	}
}
//=================================================================

void LCD1602_Scan_I2C_to_UART(lcd1602_fc113_struct * _lcd1602_fc113_handler, UART_HandleTypeDef * _huart) {
	char DataChar[32];
	int device_serial_numb = 0;

	sprintf(DataChar,"Start scan I2C\r\n");
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
	//HAL_Delay(100);

	for ( int device_i2c_address_int = 0x07; device_i2c_address_int < 0x78; device_i2c_address_int++) {
		if (HAL_I2C_IsDeviceReady( _lcd1602_fc113_handler->i2c , device_i2c_address_int << 1, 10, 100) == HAL_OK) {
			device_serial_numb++;
			switch (device_i2c_address_int) {
				case 0x23: sprintf(DataChar,"%d) BH1750", device_serial_numb ); break;
				case 0x27: sprintf(DataChar,"%d) FC113 ", device_serial_numb ); break;
				case 0x38: sprintf(DataChar,"%d) PCF8574", device_serial_numb ); break;
				//case 0x57: sprintf(DataChar,"%d) AT24C32", device_serial_numb ); break;
				case 0x57: sprintf(DataChar,"%d) MAX30100", device_serial_numb ); break;
				case 0x68: sprintf(DataChar,"%d) DS3231", device_serial_numb ); break;
				//case 0x68: sprintf(DataChar_I2C,"%d) MPU9250", device_serial_numb ); break;
				case 0x76: sprintf(DataChar,"%d) BMP280", device_serial_numb ); break;
				case 0x77: sprintf(DataChar,"%d) BMP180", device_serial_numb ); break;
				default:   sprintf(DataChar,"%d) Unknown", device_serial_numb ); break;
			}// end switch
			sprintf(DataChar,"%s\tAdr: %x\r\n", DataChar, device_i2c_address_int);
			HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
			HAL_Delay(10);
		} //end if HAL I2C1
	} // end for device_i2c_address_int i2c1
	sprintf(DataChar,"End scan I2C\r\n");
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 100);
	//HAL_Delay(100);
}// end void I2C_ScanBus
//======================================================================

void LCD1602_Scan_I2C_bus(lcd1602_fc113_struct *lcd1602_fc113_handler)
{
	char i2c_scan_buff[32];
	int  serial_number_u8 = 0;

	sprintf(i2c_scan_buff,"I2C scan\n");
	LCD1602_Print_Line(lcd1602_fc113_handler, i2c_scan_buff, strlen(i2c_scan_buff));

	HAL_Delay(500);

	for ( uint8_t i2c_dev_addr_u8 = 0x07; i2c_dev_addr_u8 < 0x78; i2c_dev_addr_u8++)
	{
		if (HAL_I2C_IsDeviceReady(lcd1602_fc113_handler->i2c, i2c_dev_addr_u8 << 1, 10, 100) == HAL_OK)
		{
			serial_number_u8++;
			switch (i2c_dev_addr_u8)
			{
				case 0x23: sprintf(i2c_scan_buff,"%d) BH-1750", serial_number_u8 ); break;
				case 0x27: sprintf(i2c_scan_buff,"%d) FC-113 ", serial_number_u8 ); break;
				//case 0x57: sprintf(i2c_scan_buff,"%d) AT24C32", serial_number_u8 ); break;
				case 0x57: sprintf(i2c_scan_buff,"%d) MAX30100", serial_number_u8 ); break;
				case 0x68: sprintf(i2c_scan_buff,"%d) DS-3231", serial_number_u8 ); break;
				case 0x76: sprintf(i2c_scan_buff,"%d) BMP-280", serial_number_u8 ); break;
				case 0x77: sprintf(i2c_scan_buff,"%d) BMP-180", serial_number_u8 ); break;
				default:   sprintf(i2c_scan_buff,"%d) Unknown", serial_number_u8 ); break;
			}// end switch

			LCD1602_Print_Line(lcd1602_fc113_handler, i2c_scan_buff, strlen(i2c_scan_buff));

			if (serial_number_u8%2 == 0)
			{
				HAL_Delay(1000);
				LCD1602_Clear(lcd1602_fc113_handler);
			}
			else
			{
				HAL_Delay(400);
				LCD1602_Cursor_Shift_Right(lcd1602_fc113_handler, 30);
			}
		} //end if HAL I2C

	}// end for i
	sprintf(i2c_scan_buff,"I2C end.\r\n");
	LCD1602_Print_Line(lcd1602_fc113_handler, i2c_scan_buff, strlen(i2c_scan_buff));

	//HAL_Delay(500);
}// end LCD1602_scan_I2C_bus
//======================================================================
