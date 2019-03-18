//
// Created by han on 19-3-13.
//

#include "svpwm.h"


float SQRT3 = 1.73205080757;

int sector_sv;

float Udc_sv;
float pwm_interval_sv;
float T_a_sv;
float T_b_sv;
float T_c_sv;

int A_sv;
int B_sv;
int C_sv;
int N_sv;

float V_ref1;
float V_ref2;
float V_ref3;

float T_1;
float T_2;
float T_3;
float T_4;
float T_5;
float T_6;
float T_7;

void svpwm_setup(float Udc, float pwm_interval)
{
    Udc_sv = Udc;
    pwm_interval_sv = pwm_interval;
}


void svpwm_cal(float V_alpha, float V_beta)
{
    sector_sv = 0;
    T_a_sv = 0.0;
    T_b_sv = 0.0;
    T_c_sv = 0.0;

    A_sv = 0;
    B_sv = 0;
    C_sv = 0;

    V_ref1 = V_beta;
    V_ref2 = (SQRT3*V_alpha - V_beta)/2;
    V_ref3 = (-SQRT3*V_alpha - V_beta)/2;

    if(V_ref1 > 0){
        A_sv = 1;
    }

    if(V_ref2 > 0){
        B_sv = 1;
    }

    if(V_ref3 > 0){
        C_sv = 1;
    }

    N_sv = A_sv + 2*B_sv + 4*C_sv;

    if(N_sv == 3){
        sector_sv = 1;
    }else if(N_sv == 1){
        sector_sv = 2;
    }else if(N_sv == 5){
        sector_sv = 3;
    }else if(N_sv == 4){
        sector_sv = 4;
    }else if(N_sv == 6){
        sector_sv = 5;
    }else if(N_sv == 2){
        sector_sv = 6;
    }

    if(sector_sv == 1){
        T_6 = (pwm_interval_sv*SQRT3*V_beta)/Udc_sv;
        T_4 = (3*pwm_interval_sv*(V_alpha-SQRT3*V_beta/3))/(2*Udc_sv);
        if(T_6+T_4 > pwm_interval_sv){
            T_6 = (T_6/(T_4+T_6))*pwm_interval_sv;
            T_4 = (T_4/(T_4+T_6))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_6 - T_4) / 2;
        }
        T_a_sv = (T_6+T_4+T_7);
        T_b_sv = (T_6+T_7);
        T_c_sv = T_7;
    }else if(sector_sv == 2){
        T_6 = (3*pwm_interval_sv*V_alpha+SQRT3*pwm_interval_sv*V_beta)/(2*Udc_sv);
        T_2 = (SQRT3*pwm_interval_sv*V_beta-3*pwm_interval_sv*V_alpha)/(2*Udc_sv);
        if(T_6+T_2 > pwm_interval_sv){
            T_6 = (T_6/(T_2+T_6))*pwm_interval_sv;
            T_2 = (T_2/(T_2+T_6))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_6 - T_2) / 2;
        }

        T_a_sv = (T_6+T_7);
        T_b_sv = (T_2+T_6+T_7);
        T_c_sv = T_7;
    }else if(sector_sv == 3){
        T_2 = (pwm_interval_sv*SQRT3*V_beta)/Udc_sv;
        T_3 = (-3*pwm_interval_sv*V_alpha - SQRT3*pwm_interval_sv*V_beta)/(2*Udc_sv);
        if(T_3+T_2 > pwm_interval_sv){
            T_3 = (T_3/(T_2+T_3))*pwm_interval_sv;
            T_2 = (T_2/(T_2+T_3))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_3 - T_2) / 2;
        }
        T_a_sv = T_7;
        T_b_sv = T_2+T_3+T_7;
        T_c_sv = T_3+T_7;
    }else if(sector_sv == 4){
        T_1 = -(pwm_interval_sv*SQRT3*V_beta)/Udc_sv;
        T_3 = -(3*(pwm_interval_sv*(V_alpha-SQRT3*V_beta/3)))/(2*Udc_sv);
        if(T_3+T_1 > pwm_interval_sv){
            T_3 = (T_3/(T_1+T_3))*pwm_interval_sv;
            T_1 = (T_1/(T_1+T_3))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_3 - T_1) / 2;
        }
        T_a_sv = T_7;
        T_b_sv = (T_3+T_7);
        T_c_sv = (T_1 + T_3 + T_7);
    }else if(sector_sv == 5){
        T_1 = -(3*pwm_interval_sv*V_alpha+SQRT3*pwm_interval_sv*V_beta)/(2*Udc_sv);
        T_5 = (-SQRT3*pwm_interval_sv*V_beta+3*pwm_interval_sv*V_alpha)/(2*Udc_sv);

        if(T_5+T_1 > pwm_interval_sv){
            T_5 = (T_5/(T_1+T_5))*pwm_interval_sv;
            T_1 = (T_1/(T_1+T_5))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_5 - T_1) / 2;
        }

        T_a_sv = T_5 + T_7;
        T_b_sv = T_7;
        T_c_sv = T_1 + T_5 + T_7;
    }else if(sector_sv == 6){
        T_5 = -(pwm_interval_sv*SQRT3*V_beta)/Udc_sv;
        T_4 = (3*pwm_interval_sv*V_alpha+SQRT3*pwm_interval_sv*V_beta)/(2*Udc_sv);

        if(T_5+T_4 > pwm_interval_sv){
            T_5 = (T_5/(T_4+T_5))*pwm_interval_sv;
            T_4 = (T_4/(T_4+T_5))*pwm_interval_sv;
            T_7 = 0;
        }else{
            T_7 = (pwm_interval_sv - T_5 - T_4) / 2;
        }

        T_a_sv = (T_4 + T_5 + T_7);
        T_b_sv = T_7;
        T_c_sv = T_5 + T_7;
    }else{
        T_a_sv = 0.0;
        T_b_sv = 0.0;
        T_c_sv = 0.0;
    }
}


