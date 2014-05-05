#ifndef GL_TOOLS_H
#define GL_TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <math.h>

#include "vector_lib.h"

typedef enum SHADER_TYPE_t{
	VERTEX,
	GEOMETRY,
	FRAGMENT
}SHADER_TYPE;

GLuint init_shaders(char* vertex_shader_name, char* geometry_shader_name,
char* fragment_shader_name);

mat_4D Perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);

mat_4D look_at(vec_3D p, vec_3D l, vec_3D v);

#ifdef __cplusplus
}
#endif
#endif /* GL_TOOLS_H */
