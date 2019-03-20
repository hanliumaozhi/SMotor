#ifndef CURRENT_REGULATOR_H
#define CURRENT_REGULATOR_H

#include "as5048a.h"
#include "inverter.h"
#include "coordinate_change.h"
#include "svpwm.h"

void current_regulator_setup(float kp, float ki);
void current_regulator_init();

void current_regulator_set_current(float i_q, float i_d);

void current_commutate(float theta_elec);

void current_controller();

#endif // !CURRENT_REGULATOR_H
