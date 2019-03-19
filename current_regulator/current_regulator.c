#include "current_regulator.h"

float i_q_ref;
float i_d_ref;
float v_q_;
float v_d_;
float v_alpha_;
float v_beta_;
float i_a_;
float i_b_;
float i_c_;
float i_alpha_;
float i_beta_;
float i_q_;
float i_d_;
float i_q_pre_;
float i_d_pre_;
float kp_;
float ki_;

float current_max_val;

void current_regulator_setup(float kp, float ki)
{
	kp_ = kp;
	ki_ = ki;
}

void current_regulator_init()
{
	current_max_val = 40.0;
}

void current_regulator_set_current(float i_q, float i_d)
{
	if (i_d > current_max_val){
		i_d = current_max_val;
	}
	if (i_d < -current_max_val){
		i_d = -current_max_val;
	}
	if (i_q > current_max_val) {
		i_q = current_max_val;
	}
	if (i_q < -current_max_val) {
		i_q = -current_max_val;
	}
	i_q_ref = i_q;
	i_d_ref = i_d;
}