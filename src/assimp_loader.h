#ifndef ASSIMP_LOADER_H
#define ASSIMP_LOADER_H

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/gl.h>

#ifdef __cplusplus
#include <assimp/Importer.hpp>
extern "C" {

#else
#include <assimp/cimport.h>
#endif /* __cplusplus */

/* Simple struct for storing models loaded */
typedef struct model {
	GLfloat* vertices;

	GLfloat* normals;
	GLfloat* texture_coords;
	GLuint* indices;
	
	GLfloat* colours;

	uint n_vertices;
	uint n_indices;

	GLuint vertex_array_object;
	GLuint buffer_objects[5];

} model;

model** load_model(char* model_file);
model** load_model_adjacency(char* model_file);

void draw_model(model* m, GLuint shaders, char* gpu_vertex, char* gpu_normal,
		char* gpu_texcoord, char* gpu_colour);
void draw_model_adjacency(model* m, GLuint shaders, char* gpu_vertex, 
		char* gpu_normal, char* gpu_texcoord, char* gpu_colour);


#ifdef __cplusplus
}
#endif /* __cpluspluc */

#endif /* ASSIMP_LOADER_H */
