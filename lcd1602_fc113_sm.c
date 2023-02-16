
#include "lcd1602_fc113_sm.h"
#ifdef LCD1602

static void LCD1602_Write_Data             (lcd1602_handle *hlcd1602, uint8_t _input_u8, LED_status led_st);
static void LCD1602_Write_Instruction_4bit (lcd1602_handle *hlcd1602, uint8_t _input_u8);
static void LCD1602_Write_Instruction_8bit (lcd1602_handle *hlcd1602, uint8_t _input_u8);
//==========================================================================

void LCD1602_Write_Data(lcd1602_handle *hlcd1602, uint8_t _input_u8, LED_status led_st) {
	if (led_st != 0) led_st = 8;

	uint8_t inputStE0 = (_input_u8 & 0xF0) 	+ 1 + led_st ;
	uint8_t inputStE1 = inputStE0 			+ 4 ;
	uint8_t inputMlE0 = (_input_u8<<4) 		+ 1 + led_st ;
	uint8_t inputMlE1 = inputMlE0 			+ 4 ;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
}

//==========================================================================
void LCD1602_Write_Instruction_4bit(lcd1602_handle *hlcd1602, uint8_t _input_u8) {
	uint8_t inputE0 = _input_u8;
	uint8_t inputE1 = inputE0 + 4;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputE0, 1, 100);
	HAL_Delay(1);
}
//==========================================================================

void LCD1602_Write_Instruction_8bit(lcd1602_handle *hlcd1602, uint8_t _input_u8) {
	uint8_t inputStE0 = ( _input_u8 & 0xF0) + 8 ;
	uint8_t inputStE1 = inputStE0 			+ 4 ;
	uint8_t inputMlE0 = ( _input_u8<<4 )	+ 8 ;
	uint8_t inputMlE1 = inputMlE0 			+ 4 ;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
}
//==========================================================================

void LCD1602_struct_init(	lcd1602_handle*		_lcd	,
							I2C_HandleTypeDef*	_i2c		,
							uint8_t				_addr		) {
	_lcd->i2c 				=	_i2c 	;
	_lcd->device_i2c_address=	_addr 	;
}
/******************************************************/

void LCD1602_Init(lcd1602_handle *hlcd1602 ) {
	HAL_Delay(15);
	LCD1602_Write_Instruction_4bit(hlcd1602, 0x30);	// step 1: 0011 0000
	HAL_Delay(5);
	LCD1602_Write_Instruction_4bit(hlcd1602, 0x30);	// step 2: 0011 0000
	LCD1602_Write_Instruction_4bit(hlcd1602, 0x30);	// step 3: 0011 0000
	LCD1602_Write_Instruction_4bit(hlcd1602, 0x20);	// step 4: 0010 0000
	// 4-bit is active
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x28);	// step 5: 0010 1000 NF
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x08);	// step 6: 0000 1000
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x01);	// step 7: 0000 0001
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x06);	// step 8: 0000 0110
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x0C);	// step 9: 0000 1100 CB
}
//==========================================================================
void LCD1602_Clear(lcd1602_handle *hlcd1602) {
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x01); 	// 0x01 clear disp
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x03);	// 0x03 cursor to start
}
//==========================================================================
void LCD1602_Cursor_Shift_Right(lcd1602_handle *hlcd1602, uint8_t _step) {
	for ( ; _step > 0; _step--) {
		LCD1602_Write_Instruction_8bit(hlcd1602, 0x14);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Shift_Left(lcd1602_handle *hlcd1602, uint8_t _step) {
	for ( ; _step > 0; _step--)	{
		LCD1602_Write_Instruction_8bit(hlcd1602, 0x10);		// Shift Cursor Right
	}
}
//==========================================================================

void LCD1602_Cursor_Return(lcd1602_handle *hlcd1602) {
	LCD1602_Write_Instruction_8bit(hlcd1602, 0x2);		// Cursor Return
}
//==========================================================================

void LCD1602_Display_Shift_Right(lcd1602_handle *hlcd1602, uint8_t _step) {
	for ( ; _step > 0; _step--) {
		LCD1602_Write_Instruction_8bit(hlcd1602, 0x1C);		// Shift Display
	}
}
//==========================================================================

void LCD1602_Display_Shift_Left(lcd1602_handle *hlcd1602, uint8_t _step) {
	for ( ; _step > 0; _step--) {
		LCD1602_Write_Instruction_8bit(hlcd1602, 0x18);		// Shift Display
	}
}
//==========================================================================

void LCD1602_Print_Line( 	lcd1602_handle*	hlcd1602						,
							char* 					DataChar				,
							uint8_t 				SizeChar 				,
							LED_status		 		led_st					) {
	for (uint8_t i=0; i<SizeChar; i++) {
		if ( (DataChar[i] == '\r') || (DataChar[i] == '\n') || (DataChar[i] == '\0')  ) {
			//LCD1602_Write_Data(hlcd1602, ' ');	// print "Space"
		} else {
			LCD1602_Write_Data(hlcd1602, DataChar[i], led_st);
		}

		if (DataChar[i] == '\n') {
			LCD1602_Cursor_Shift_Right(hlcd1602, 40-i);
		}

		if (i == 15) {
			LCD1602_Cursor_Shift_Right(hlcd1602, 40-i-1);
		}
	}
}
//=================================================================

void LCD1602_Scan_I2C_to_UART(	I2C_HandleTypeDef*	_i2c	,
								UART_HandleTypeDef* _huart	) {
	char DataChar[100];
	int device_serial_numb = 0;

	sprintf(DataChar,"Start scan I2C:\r\n" ) ;
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 1000 ) ;

	for ( int device_i2c_address_int = 0x07; device_i2c_address_int < 0x78; device_i2c_address_int++) {
		if (HAL_I2C_IsDeviceReady( _i2c , device_i2c_address_int << 1, 10, 100) == HAL_OK) {
			device_serial_numb++;
			switch (device_i2c_address_int) {
				case 0x23: sprintf(DataChar,"%d) BH1750", device_serial_numb ); break;
				case 0x27: sprintf(DataChar,"%d) FC113 ", device_serial_numb ); break;
				case 0x20: sprintf(DataChar,"%d) PCF8574", device_serial_numb ); break;
				case 0x38: sprintf(DataChar,"%d) PCF8574", device_serial_numb ); break;
				case 0x3F: sprintf(DataChar,"%d) LCD1602", device_serial_numb ); break;
				//case 0x57: sprintf(DataChar,"%d) AT24C32", device_serial_numb ); break;
				case 0x57: sprintf(DataChar,"%d) MAX30100", device_serial_numb ); break;
				case 0x68: sprintf(DataChar,"%d) DS3231", device_serial_numb ); break;
				//case 0x68: sprintf(DataChar_I2C,"%d) MPU9250", device_serial_numb ); break;
				case 0x76: sprintf(DataChar,"%d) BMP280", device_serial_numb ); break;
				case 0x77: sprintf(DataChar,"%d) BMP180", device_serial_numb ); break;
				default:   sprintf(DataChar,"%d) Unknown", device_serial_numb ); break;
			}// end switch
			char DataChar2[150];
			sprintf(DataChar2,"%s\tAdr: %x\r\n", DataChar, device_i2c_address_int ) ;
			HAL_UART_Transmit(_huart, (uint8_t *)DataChar2, strlen(DataChar2), 1000 ) ;
			HAL_Delay(10);
		} //end if HAL I2C1
	} // end for device_i2c_address_int i2c1
	sprintf(DataChar,"End scan I2C.\r\n" ) ;
	HAL_UART_Transmit(_huart, (uint8_t *)DataChar, strlen(DataChar), 1000 ) ;
}// end void I2C_ScanBus
//======================================================================

void LCD1602_Scan_I2C_bus(lcd1602_handle *hlcd1602) {
	char i2c_scan_buff[32] ;
	int  serial_number_u8 = 0 ;

	sprintf(i2c_scan_buff,"I2C scan start:\n" ) ;
	LCD1602_Print_Line(hlcd1602, i2c_scan_buff, strlen(i2c_scan_buff),1 ) ;
	HAL_Delay( 500 ) ;

	for ( uint8_t i2c_dev_addr_u8 = 0x07; i2c_dev_addr_u8 < 0x78; i2c_dev_addr_u8++) {
		if (HAL_I2C_IsDeviceReady(hlcd1602->i2c, i2c_dev_addr_u8 << 1, 10, 100) == HAL_OK) {
			serial_number_u8++;
			switch ( i2c_dev_addr_u8 ) {
				case 0x23: sprintf(i2c_scan_buff,"%d) BH-1750", serial_number_u8 ); break;
				case 0x27: sprintf(i2c_scan_buff,"%d) FC-113 ", serial_number_u8 ); break;
				//case 0x57: sprintf(i2c_scan_buff,"%d) AT24C32", serial_number_u8 ); break;
				case 0x57: sprintf(i2c_scan_buff,"%d) MAX30100", serial_number_u8 ); break;
				case 0x68: sprintf(i2c_scan_buff,"%d) DS-3231", serial_number_u8 ); break;
				case 0x76: sprintf(i2c_scan_buff,"%d) BMP-280", serial_number_u8 ); break;
				case 0x77: sprintf(i2c_scan_buff,"%d) BMP-180", serial_number_u8 ); break;
				default:   sprintf(i2c_scan_buff,"%d) Unknown", serial_number_u8 ); break;
			}// end switch

			LCD1602_Print_Line(hlcd1602, i2c_scan_buff, strlen(i2c_scan_buff),1);

			if (serial_number_u8%2 == 0) {
				HAL_Delay(1000);
				LCD1602_Clear(hlcd1602);
			} else {
				HAL_Delay(400);
				LCD1602_Cursor_Shift_Right(hlcd1602, 30);
			}
		} //end if HAL I2C
	}// end for i
	sprintf(i2c_scan_buff,"I2C end.\r\n" ) ;
	LCD1602_Print_Line(hlcd1602, i2c_scan_buff, strlen(i2c_scan_buff),1) ;
}// end LCD1602_scan_I2C_bus

void LCD1602cursorToFirstPosition (lcd1602_handle *hlcd1602, LED_status led_st) {
	if (led_st != 0)  led_st = 8;
	uint8_t _input_u8 = 0x02;	// cursor to first position
	uint8_t inputStE0 = ( _input_u8 & 0xF0) + 0 + led_st ;
	uint8_t inputStE1 = inputStE0 			+ 4 ;
	uint8_t inputMlE0 = ( _input_u8<<4 )	+ 0 + led_st ;
	uint8_t inputMlE1 = inputMlE0 			+ 4 ;

	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputStE0, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE1, 1, 100);
	HAL_Delay(1);
	HAL_I2C_Master_Transmit(hlcd1602->i2c, hlcd1602->device_i2c_address<<1, &inputMlE0, 1, 100);
	HAL_Delay(1);
} //********************************************************************************

/*
**************************************************************************
*                          			END
**************************************************************************
*/
#endif
