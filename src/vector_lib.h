#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

typedef struct vec_3D {
	float x;
	float y;
	float z;
}vec_3D;

typedef struct mat_4D {
	float m[16];
}mat_4D;

float norm(vec_3D v);

vec_3D normalise(vec_3D v);

float dot_product(vec_3D a, vec_3D b);

vec_3D cross_product(vec_3D a, vec_3D b);

vec_3D vector_add(vec_3D a, vec_3D b);

vec_3D vector_sub(vec_3D a, vec_3D b);

mat_4D mult(mat_4D x, mat_4D y);

mat_4D identity_matrix();

mat_4D translation(vec_3D p);

mat_4D translation_comp(float dx, float dy, float dz);

mat_4D rot_x(float phi);

mat_4D rot_y(float phi);

mat_4D rot_z(float phi);
#endif /* VECTOR_LIB_H */
