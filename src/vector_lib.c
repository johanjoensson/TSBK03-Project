#include "vector_lib.h"
#include <math.h>
#include <stdio.h>

float norm(vec_3D v)
{
	float res;
	res = v.x*v.x + v.y*v.y + v.z*v.z;
	return sqrt(res);
}

vec_3D normalise(vec_3D v)
{
	vec_3D res;
	float a_v = norm(v);
	res.x = v.x/a_v;
	res.y = v.y/a_v;
	res.z = v.z/a_v;

	return res;
}

float dot_product(vec_3D a, vec_3D b)
{
	float res = a.x*b.x + a.y*b.y + a.z*b.z;

	return res;
}

vec_3D cross_product(vec_3D a, vec_3D b)
{
	vec_3D res;
	res.x = a.y*b.z-a.z*b.y;
	res.y = a.z*b.x - a.x*b.z;
	res.z = a.x*b.y - a.y*b.x;

	return res;
}

vec_3D vector_add(vec_3D a, vec_3D b)
{
	vec_3D res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;

	return res;
}

vec_3D vector_sub(vec_3D a, vec_3D b)
{
	vec_3D res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;

	return res;
}

mat_4D mult(mat_4D x, mat_4D y)
{
	mat_4D res;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			res.m[4*i+j] = 0;
			for(int n = 0; n < 4; n++){
				res.m[4*i+j] += x.m[4*i + n]*y.m[4*n + j];
			}
		}
	}

	return res;
}

mat_4D translation(vec_3D p)
{
	mat_4D res = identity_matrix();

	res.m[3] = p.x;
	res.m[7] = p.y;
	res.m[11] = p.z;

	return res;
}

mat_4D translation_comp(float dx, float dy, float dz)
{
	mat_4D res = identity_matrix();

	res.m[3] = dx;
	res.m[7] = dy;
	res.m[11] = dz;

	return res;
}

mat_4D rot_x(float phi)
{
	mat_4D res = identity_matrix();

	res.m[5] = cosf(phi*M_PI/180);
	res.m[6] = -sinf(phi*M_PI/180);
	res.m[9] = sinf(phi*M_PI/180);
	res.m[10] = cosf(phi*M_PI/180);

	return res;
}

mat_4D rot_y(float phi)
{
	mat_4D res = identity_matrix();

	res.m[0] = cosf(phi*M_PI/180);
	res.m[2] = sinf(phi*M_PI/180);
	res.m[8] = -sinf(phi*M_PI/180);
	res.m[10] = cosf(phi*M_PI/180);

	return res;
}

mat_4D rot_z(float phi)
{
	mat_4D res = identity_matrix();

	res.m[0] = cosf(phi*M_PI/180);
	res.m[1] = -sinf(phi*M_PI/180);
	res.m[4] = sinf(phi*M_PI/180);
	res.m[5] = cosf(phi*M_PI/180);

	return res;

}
mat_4D identity_matrix()
{
	mat_4D res;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == j){
				res.m[4*i+j] = 1;
			}else{
				res.m[4*i+j] = 0;
			}
		}
	}
	return res;
}
