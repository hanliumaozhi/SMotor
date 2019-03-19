
#include "as5048a.h"

GPIO_TypeDef* AS5048A_PORT;
uint16_t AS5048A_PIN;
SPI_HandleTypeDef* AS5048A;

uint16_t cmd_word = 0xffff;
uint16_t position_val_raw;
float position_val_raw_f;
float position_val;

uint16_t falut_status;


void as5048a_setup(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* as5048a_port, uint16_t as5048a_pin)
{
	AS5048A = spiHandle;
	AS5048A_PORT = as5048a_port;
	AS5048A_PIN = as5048a_pin;
	
	HAL_GPIO_WritePin(AS5048A_PORT, AS5048A_PIN, GPIO_PIN_SET);
}

bool as5048a_read()
{
	HAL_GPIO_WritePin(AS5048A_PORT, AS5048A_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&cmd_word, (uint8_t *)&position_val_raw, 1, 0);
	HAL_GPIO_WritePin(AS5048A_PORT, AS5048A_PIN, GPIO_PIN_SET);
	  
	HAL_GPIO_WritePin(AS5048A_PORT, AS5048A_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&cmd_word, (uint8_t *)&position_val_raw, 1, 0);
	HAL_GPIO_WritePin(AS5048A_PORT, AS5048A_PIN, GPIO_PIN_SET);
	
	falut_status = position_val_raw & 0x4000;
	position_val_raw &= 0x3fff;
	if (falut_status == 0){
		position_val_raw_f = (float)position_val_raw;
		position_val = ((position_val_raw_f) / (16383.0f)) * 3.14159265f;
		return true;
	}else{
		// implement some funciton
		return false;
	}
}