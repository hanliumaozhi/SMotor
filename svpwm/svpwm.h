//
// Created by han on 19-3-13.
//

#ifndef SVPWM_SVPWM_H
#define SVPWM_SVPWM_H



extern float T_a_sv;
extern float T_b_sv;
extern float T_c_sv;
extern int sector_sv;

void svpwm_setup(float Udc, float pwm_interval);
void svpwm_cal(float V_alpha, float V_beta);

#endif //SVPWM_SVPWM_H
