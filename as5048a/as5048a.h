
#ifndef AS5048A_H
#define AS5048A_H

#include "stdbool.h"
#include "spi.h"

extern uint16_t position_val_raw;
extern float position_val;
extern uint16_t falut_status;
extern float zero_offset;

void as5048a_setup(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* as5048a_port, uint16_t as5048a_pin);
bool as5048a_read();

void encoder_setup(float magnet_pair);
void encoder_setup_ex(float magnet_pair, float zero_position);
void get_mech_position(float* mech_position, float inc_time);
void get_elec_position(float* elec_position);

void get_mech_velocity(float* mech_velocity);
void get_elec_velocity(float* elec_velocity);
#endif // !AS5048A_H
