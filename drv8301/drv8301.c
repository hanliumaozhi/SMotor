#include "drv8301.h"

uint16_t write_word;
uint16_t response_word_drv;

GPIO_TypeDef* DRV8301_PORT;
uint16_t DRV8301_PIN;
SPI_HandleTypeDef* DRV8301;

void drv8301_setup(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* drv8301_port, uint16_t drv8301_pin)
{
	DRV8301 = spiHandle;
	DRV8301_PORT = drv8301_port;
	DRV8301_PIN = drv8301_pin;
	
	HAL_GPIO_WritePin(DRV8301_PORT, DRV8301_PIN, GPIO_PIN_SET);
}

void drv8301_init(void)
{
	write_word = 0;
	// for 3 pwm input
	write_word |= CTRL1_PWM_MODE_3_INPUT;
	// for (60/7)A current limit (only for test)
	write_word |= CTRL1_OC_ADJ_SET(0);
	write_word |= DRV_SPI_CTRL1;
	write_word |= DRV_SPI_WRITE;
	
	HAL_GPIO_WritePin(DRV8301_PORT, DRV8301_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(DRV8301, (uint8_t *)&write_word, (uint8_t *)&response_word_drv, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(DRV8301_PORT, DRV8301_PIN, GPIO_PIN_SET);

}
