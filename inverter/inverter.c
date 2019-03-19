
#include "inverter.h"


TIM_HandleTypeDef* motor_pwm;
GPIO_TypeDef* DRV8301_PORT;
uint16_t DRV8301_PIN;
SPI_HandleTypeDef* DRV8301;
ADC_HandleTypeDef* a_adc;
ADC_HandleTypeDef* b_adc;

GPIO_TypeDef* POWER_PORT;
uint16_t POWER_PIN;

uint16_t so_1_raw_val;
uint16_t so_2_raw_val;

float so_1_voltage;
float so_2_voltage;

void inverter_setup(TIM_HandleTypeDef* motor_tim, SPI_HandleTypeDef* drv8301, GPIO_TypeDef* port, uint16_t pin)
{
	motor_pwm = motor_tim;
	DRV8301 = drv8301;
	DRV8301_PORT = port;
	DRV8301_PIN = pin;
	drv8301_setup(drv8301, port, pin);
}

void inverter_init(ADC_HandleTypeDef* a, ADC_HandleTypeDef* b, GPIO_TypeDef* power_port, uint16_t power_pin)
{
	a_adc = a;
	b_adc = b;
	
	POWER_PORT = power_port;
	POWER_PIN = power_pin;
	
	HAL_ADCEx_Calibration_Start(a_adc, ADC_SINGLE_ENDED);
	HAL_ADC_Start(a_adc);
	
	HAL_Delay(500);
	HAL_ADCEx_Calibration_Start(b_adc, ADC_SINGLE_ENDED);
	HAL_ADC_Start(b_adc);
	
	HAL_GPIO_WritePin(POWER_PORT, POWER_PIN, GPIO_PIN_SET);
	drv8301_init();
	
	HAL_Delay(500);
	
	
}

void inverter_zero_current()
{
	
}

void inverter_get_voltage()
{
	HAL_ADC_PollForConversion(a_adc, 0);
	so_1_raw_val = HAL_ADC_GetValue(a_adc);
	
	HAL_ADC_PollForConversion(b_adc, 0);
	so_2_raw_val = HAL_ADC_GetValue(b_adc);
	
	so_1_voltage = ((float)so_1_raw_val) / 4095.0f * 3.3f;
	so_2_voltage = ((float)so_2_raw_val) / 4095.0f * 3.3f;
}