#include "impedance_controller.h"

float k_p_;
float k_b_;

float torque_;
int is_first_;

float mech_postion__;
float mech_velocity__;
float elec_velocity__;
float elec_position__;

uint32_t counter_pre_;
uint32_t counter_;

float toa_;

void impedance_controller_setup(float k_p, float k_d, float toa)
{
	k_p_ = k_p;
	k_b_ = k_d;
	is_first_ = 1;
	toa_ = toa;
}

void IC_running(float position_ref)
{
	//for simple
	/*if (is_first_)
	{
		get_mech_position(&mech_postion__, 0.00005);
		get_mech_velocity(&mech_velocity__);
		get_elec_position(&elec_position__);
		counter_pre_  = __HAL_TIM_GET_COUNTER(&htim2);
	}
	else
	{
		
	}*/
	
	get_mech_position(&mech_postion__, 0.00005);
	get_mech_velocity(&mech_velocity__);
	get_elec_position(&elec_position__);
	
	torque_ = k_p_*(position_ref - mech_postion__) - k_b_*(mech_velocity__);
	
	current_regulator_set_current((torque_ / toa_), 0);
	current_commutate(elec_position__);
}
