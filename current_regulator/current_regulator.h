#ifndef CURRENT_REGULATOR_H
#define CURRENT_REGULATOR_H

void current_regulator_setup(float kp, float ki);
void current_regulator_init();

void current_regulator_set_current(float i_q, float i_d);

#endif // !CURRENT_REGULATOR_H
