
#ifndef INVERTER_H
#define INVERTER_H

#include "tim.h"
#include "drv8301.h"

extern uint16_t so_1_raw_val;
extern uint16_t so_2_raw_val;

extern float so_1_voltage;
extern float so_2_voltage;


void inverter_setup(TIM_HandleTypeDef* motor_tim, SPI_HandleTypeDef* drv8301, GPIO_TypeDef* port, uint16_t pin);
void inverter_init(ADC_HandleTypeDef* a, ADC_HandleTypeDef* b, GPIO_TypeDef* power_port, uint16_t power_pin);
void inverter_zero_current();

void inverter_get_voltage();
#endif // !INVERTER_H
