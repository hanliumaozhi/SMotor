
#ifndef AS5048A_H
#define AS5048A_H

#include "stdbool.h"
#include "spi.h"

extern uint16_t position_val_raw;
extern float position_val;
extern uint16_t falut_status;

void as5048a_setup(SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* as5048a_port, uint16_t as5048a_pin);
bool as5048a_read();
#endif // !AS5048A_H
