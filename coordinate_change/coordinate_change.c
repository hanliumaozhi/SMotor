
#include "arm_math.h"
#include "coordinate_change.h"

float angle_cos;
float angle_sin;

void Park(float alpha, float beta, float theta, float *d, float *q)
{
	angle_sin = arm_sin_f32(theta);
	angle_cos = arm_cos_f32(theta);
	*d = angle_cos*alpha + angle_sin*beta;
	*q = -angle_sin*alpha + angle_cos*beta;
}

void InvPark(float d, float q, float theta, float *alpha, float *beta)
{
	angle_sin = sinf(theta);
	angle_cos = cosf(theta);
	*alpha = d*angle_cos - q*angle_sin;
	*beta = q*angle_cos + d*angle_sin;
}

void InvPark_EX(float d, float q, float *alpha, float *beta)
{
	*alpha = d*angle_cos - q*angle_sin;
	*beta = q*angle_cos + d*angle_sin;
}

void Clarke(float a, float b, float c, float *alpha, float *beta)
{
	//cause c = -a -b;
	*alpha = a;
	*beta =  0.57735026919f*(a + 2.0f*b);
}

void InvClarke(float alpha, float beta, float *a, float *b, float *c)
{
	*a = alpha;
	*b = 0.5f*(-alpha + 1.73205080757f*beta);
	*c = 0.5f*(-alpha - 1.73205080757f*beta);
}