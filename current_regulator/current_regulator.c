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
float i_q_sample_;
float i_d_sample_;
float i_q_pre_;
float i_d_pre_;
float kp_;
float ki_;
float theta_elec_;
float integration_max_;

float current_max_val;

float i_d_error_;
float i_q_error_;

float i_d_integration_;
float i_q_integration_;

//ki 0.1535 kp 0.2046
void current_regulator_setup(float kp, float ki)
{
	kp_ = kp;
	ki_ = ki;
}

void current_regulator_init()
{
	current_max_val = 40.0f;
	integration_max_ = 0.9f;
	i_d_integration_ = 0.0f;
	i_q_integration_ = 0.0f;
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

void current_commutate(float theta_elec)
{
	
	inverter_get_current(&i_a_, &i_b_, &i_c_);
	Clarke(i_a_, i_b_, i_c_, &i_alpha_, &i_beta_);
	Park(i_alpha_, i_beta_, theta_elec, &i_d_sample_, &i_q_sample_);
	// low_pass filter
	i_d_ = 0.95f*i_d_sample_ + 0.05f*i_d_pre_;
	i_q_ = 0.95f*i_q_sample_ + 0.05f*i_q_pre_;
	i_d_pre_ = i_d_;
	i_q_pre_ = i_q_;
	
	current_controller();
	InvPark(v_d_, v_q_, theta_elec, &v_alpha_, &v_beta_);
	svpwm_cal(v_alpha_, v_beta_);
	inverter_set_pwm(T_a_sv, T_b_sv, T_c_sv);
}

void current_controller()
{
	// this is a implement of imc, cutoff frequency is 1k hz. sample frequency is 20k hz;
	i_d_error_ = i_d_ref - i_d_;
	i_q_error_ = i_q_ref - i_q_;
	
	i_q_integration_ += i_q_error_*ki_*kp_;
	i_d_integration_ += i_d_error_*ki_*kp_;
	
	if (i_q_integration_ > integration_max_) i_q_integration_ = integration_max_;
	if (i_q_integration_ < -integration_max_) i_q_integration_ = -integration_max_;
	if (i_d_integration_ > integration_max_) i_d_integration_ = integration_max_;
	if (i_d_integration_ < -integration_max_) i_d_integration_ = -integration_max_;
	
	v_q_ = i_q_integration_ + kp_*i_q_error_;
	v_d_ = i_d_integration_ + kp_*i_d_error_;
	
}