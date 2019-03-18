//
// Created by han on 19-3-13.
//

#ifndef COORDINATE_CHANGE_H
#define COORDINATE_CHANGE_H

void Park(float alpha, float beta, float theta, float *d, float *q);
void InvPark(float d, float q, float theta, float *alpha, float *beta);
void Clarke(float a, float b, float c, float *alpha, float *beta);
void InvClarke(float alpha, float beta, float *a, float *b, float *c);

#endif // !COORDINATE_CHANGE_H
