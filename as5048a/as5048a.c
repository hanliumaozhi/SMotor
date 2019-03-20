
#include "as5048a.h"

GPIO_TypeDef* AS5048A_PORT;
uint16_t AS5048A_PIN;
SPI_HandleTypeDef* AS5048A;

uint16_t cmd_word = 0xffff;
uint16_t position_val_raw;
float position_val_raw_f;
float position_val;

float joint_position_val;
float joint_position_val_pre;
float joint_velocity;
float zero_offset;

uint16_t falut_status;

float magnet_pair_;
float pi_f = 3.14159265359f;
float pi_2_f = 6.28318530718f;


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
		position_val = ((position_val_raw_f) / (16383.0f)) * 6.28318530718f;
		return true;
	}else{
		// implement some funciton
		return false;
	}
}

void encoder_setup(float magnet_pair)
{
	magnet_pair_ = magnet_pair;
	as5048a_read();
	zero_offset = position_val;
}

void encoder_setup_ex(float magnet_pair, float zero_position)
{
	magnet_pair_ = magnet_pair;
	zero_offset = zero_position;
}

void get_mech_position(float* mech_position, float inc_time)
{
	as5048a_read();
	joint_position_val_pre = joint_position_val;
	
	joint_position_val = (position_val - zero_offset + pi_f);
	if (joint_position_val < 0){
		joint_position_val += pi_2_f;
	}
	if(joint_position_val > pi_2_f){
		joint_position_val -= pi_2_f;
	}
	*mech_position = joint_position_val;
	
	//we assume the motor cant move full range
	joint_velocity = (joint_position_val - joint_position_val_pre) / inc_time;
	
	
}

void get_elec_position(float* elec_position)
{
	*elec_position = magnet_pair_*position_val;
}

void get_mech_velocity(float* mech_velocity)
{
	*mech_velocity = joint_velocity;
}

void get_elec_velocity(float* elec_velocity)
{
	*elec_velocity = joint_velocity*magnet_pair_;
}