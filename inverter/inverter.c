
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

float so_1_current;
float so_2_current;

uint32_t a_channel_val;
uint32_t b_channel_val;
uint32_t c_channel_val;

float pwm_interval;
float total_counter;



void inverter_setup(TIM_HandleTypeDef* motor_tim, SPI_HandleTypeDef* drv8301, GPIO_TypeDef* port, uint16_t pin)
{
	motor_pwm = motor_tim;
	DRV8301 = drv8301;
	DRV8301_PORT = port;
	DRV8301_PIN = pin;
	drv8301_setup(drv8301, port, pin);
}

void inverter_init(ADC_HandleTypeDef* a, ADC_HandleTypeDef* b, GPIO_TypeDef* power_port, uint16_t power_pin, float pwm_interval_)
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
	
	HAL_Delay(500);
	
	HAL_TIM_Base_Start(motor_pwm);
	HAL_TIM_PWM_Start(motor_pwm, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(motor_pwm, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(motor_pwm, TIM_CHANNEL_3);
	
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_1, 45);
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_3, 0);
	
	HAL_Delay(500);
	
	HAL_GPIO_WritePin(POWER_PORT, POWER_PIN, GPIO_PIN_SET);
	HAL_Delay(500);
	
	drv8301_init();
	
	HAL_Delay(500);
	
	pwm_interval = pwm_interval_;
	total_counter = 449.0f;
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
	
	// for G = 10v/v;
	so_1_current = 33.0f - 20.0f*so_1_voltage;
	so_2_current = 33.0f - 20.0f*so_2_voltage;
}

void inverter_sample_current()
{
	HAL_ADC_PollForConversion(a_adc, 0);
	so_1_raw_val = HAL_ADC_GetValue(a_adc);
	
	HAL_ADC_PollForConversion(b_adc, 0);
	so_2_raw_val = HAL_ADC_GetValue(b_adc);
	
	so_1_voltage = ((float)so_1_raw_val) / 4095.0f * 3.3f;
	so_2_voltage = ((float)so_2_raw_val) / 4095.0f * 3.3f;
	
	// for G = 10v/v;
	so_1_current = 33.0f - 20.0f*so_1_voltage;
	so_2_current = 33.0f - 20.0f*so_2_voltage;
}

void inverter_get_current(float *a, float *b, float *c)
{
	*a = so_1_current;
	*b = so_2_current;
	*c = -so_1_current - so_2_current;
}

void inverter_set_pwm(float a_t, float b_t, float c_t)
{
	a_channel_val = (a_t) / pwm_interval*total_counter;
	b_channel_val = (b_t) / pwm_interval*total_counter;
	c_channel_val = (c_t) / pwm_interval*total_counter;
	if (a_channel_val < 22){
		a_channel_val = 22;
	}
	if (a_channel_val > 428){
		a_channel_val = 428;
	}
	if (b_channel_val < 22){
		b_channel_val = 22;
	}
	if (b_channel_val > 428){
		b_channel_val = 428;
	}
	if (c_channel_val < 22){
		c_channel_val = 22;
	}
	if (c_channel_val > 428){
		c_channel_val = 428;
	}
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_1, a_channel_val);
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_2, b_channel_val);
	__HAL_TIM_SET_COMPARE(motor_pwm, TIM_CHANNEL_3, c_channel_val);
}