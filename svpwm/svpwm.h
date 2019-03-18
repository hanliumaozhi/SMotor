//
// Created by han on 19-3-13.
//

#ifndef SVPWM_SVPWM_H
#define SVPWM_SVPWM_H

#define SQRT3 1.73205080757

extern double T_a_sv;
extern double T_b_sv;
extern double T_c_sv;
extern int sector_sv;

void svpwm_setup(double Udc, double pwm_interval);
void svpwm_cal(double V_alpha, double V_beta);

#endif //SVPWM_SVPWM_H
