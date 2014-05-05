#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>

#include "SDL_util.h"
#include "GL_tools.h"
#include "assimp_loader.h"
#include "vector_lib.h"

#include "adjacency.h"

#define ADJACENCY 1
#define FINAL

void initialize_adjacency_table(struct aiMesh mesh)
{
	create_adjacency_table(mesh.mNumFaces);

	int a, b, c;
	for(uint32_t i = 0; i < mesh.mNumFaces; i++){
		
		a = mesh.mFaces[i].mIndices[0];
		b = mesh.mFaces[i].mIndices[1];
		c = mesh.mFaces[i].mIndices[2];

		insert_neighbours(a,b,c);
	}
}

void calculate_indices(struct aiMesh mesh, model* m)
{
	uint32_t a, b;

	m->n_indices = mesh.mNumFaces *6;
	
	m->indices = malloc(sizeof(uint32_t)*m->n_indices);
	
	if(mesh.mFaces != NULL){
		int n = 0;
		for(uint32_t i = 0; i < mesh.mNumFaces; i++){
			for(uint32_t j = 0; j < mesh.mFaces[i].mNumIndices;
					j++){
				a = mesh.mFaces[i].mIndices[j];
				b = mesh.mFaces[i].mIndices[(j+1) % 3];
				m->indices[n + 2*j] = a;
				m->indices[n + 2*j + 1] = find_neighbour(a, b);
			}
			n += 6;
		}

	}
}


void extract_vertices(struct aiMesh mesh, model* m)
{
	uint32_t n_vertices = mesh.mNumVertices;
	m->n_vertices = n_vertices;
	m->vertices = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);

	if(mesh.mVertices != NULL){
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			m->vertices[3*i + 0] = mesh.mVertices[i].x;
			m->vertices[3*i + 1] = mesh.mVertices[i].y;
			m->vertices[3*i + 2] = mesh.mVertices[i].z;
		}
	}
}

void extract_normals(struct aiMesh mesh, model* m)
{
	m->normals = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);
	if(mesh.mNormals != NULL){
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			m->normals[3*i + 0] = mesh.mNormals[i].x;
			m->normals[3*i + 1] = mesh.mNormals[i].y;
			m->normals[3*i + 2] = mesh.mNormals[i].z;
		}
	}
}

void extract_texture_coords(struct aiMesh mesh, model* m)
{
	m->texture_coords = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);
	
	if(mesh.mTextureCoords[0] != NULL){
		/* Assumes 3D texture coordinates */
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			m->texture_coords[3*i + 0] = mesh.mTextureCoords[0][i].x;
			m->texture_coords[3*i + 1] = mesh.mTextureCoords[0][i].y;
			m->texture_coords[3*i + 2] = mesh.mTextureCoords[0][i].z;
		}

	}
}

void extract_colors(struct aiMesh mesh, model* m)
{
	m->colours = malloc(sizeof(GLfloat)*4*mesh.mNumVertices);
	if(mesh.mColors[0] != NULL){
		/* RGBA colours */
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			m->colours[4*i + 0] = mesh.mColors[0][i].r;
			m->colours[4*i + 1] = mesh.mColors[0][i].g;
			m->colours[4*i + 2] = mesh.mColors[0][i].b;
			m->colours[4*i + 3] = mesh.mColors[0][i].a;
		}
	}
}

model* extract_model_adjacency(struct aiMesh mesh)
{
	model* res = malloc(sizeof(model));

	extract_vertices(mesh, res);
	extract_normals(mesh, res);
	extract_texture_coords(mesh, res);
	extract_colors(mesh, res);

	initialize_adjacency_table(mesh);

	calculate_indices(mesh, res);

	return res;
}

model*  extract_model(struct aiMesh mesh)
{
	model *res = malloc(sizeof(model));

	uint32_t n_indices = 0;
	uint32_t n_vertices = mesh.mNumVertices;

	for(uint32_t i = 0; i < mesh.mNumFaces; i++){
		n_indices += mesh.mFaces[i].mNumIndices;
	}

	/* 
	 * Allocate all the indices, also make sure that the
	 * triangulation worked properly 
	 */
	res->indices = malloc(sizeof(unsigned int)*n_indices);
	/*
	 * Maybe remove this later?
	 * It shouldn't be needed
	 */
	assert(n_indices == 3*mesh.mNumFaces);

	res->n_indices = n_indices;
	res->n_vertices = n_vertices;

	res->vertices = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);
	res->texture_coords = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);
	res->normals = malloc(sizeof(GLfloat)*3*mesh.mNumVertices);

	res->colours = malloc(sizeof(GLfloat)*4*mesh.mNumVertices);
	
	if(mesh.mVertices != NULL){
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			res->vertices[3*i + 0] = mesh.mVertices[i].x;
			res->vertices[3*i + 1] = mesh.mVertices[i].y;
			res->vertices[3*i + 2] = mesh.mVertices[i].z;
		}
	}
	if(mesh.mNormals != NULL){
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			res->normals[3*i + 0] = mesh.mNormals[i].x;
			res->normals[3*i + 1] = mesh.mNormals[i].y;
			res->normals[3*i + 2] = mesh.mNormals[i].z;
		}
	}
	if(mesh.mColors[0] != NULL){
		/* RGBA colours */
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			res->colours[4*i + 0] = mesh.mColors[0][i].r;
			res->colours[4*i + 1] = mesh.mColors[0][i].g;
			res->colours[4*i + 2] = mesh.mColors[0][i].b;
			res->colours[4*i + 3] = mesh.mColors[0][i].a;
		}
	}
	if(mesh.mTextureCoords[0] != NULL){
		/* Assumes 3D texture coordinates */
		for(uint32_t i = 0; i < mesh.mNumVertices; i++){
			res->texture_coords[3*i + 0] = mesh.mTextureCoords[0][i].x;
			res->texture_coords[3*i + 1] = mesh.mTextureCoords[0][i].y;
			res->texture_coords[3*i + 2] = mesh.mTextureCoords[0][i].z;
		}

	}

	if(mesh.mFaces != NULL){
		int n = 0;
		for(uint32_t i = 0; i < mesh.mNumFaces; i++){
			for(uint32_t j = 0; j < mesh.mFaces[i].mNumIndices;
					j++){
				res->indices[n + j] =
					mesh.mFaces[i].mIndices[j];
			}
			n += mesh.mFaces[i].mNumIndices;
		}

	}



	return res;
}

float max(float a, float b)
{
	if(a > b){
		return a;
	}else{
		return b;
	}

	return 0;
}

float min(float a, float b)
{
	if(a > b){
		return b;
	}else{
		return a;
	}

	return 0;
}

void center_model(model *m)
{
	vec_3D maximum, minimum;

	maximum.x = m->vertices[0];
	maximum.y = m->vertices[1];
	maximum.z = m->vertices[2];

	minimum.x = m->vertices[0];
	minimum.y = m->vertices[1];
	minimum.z = m->vertices[2];

	for(uint i = 0; i < m->n_vertices; i++){
		maximum.x = max(maximum.x,m->vertices[3*i + 0]);
		maximum.y = max(maximum.y,m->vertices[3*i + 1]);
		maximum.z = max(maximum.z,m->vertices[3*i + 2]);

		minimum.x = min(minimum.x, m->vertices[3*i + 0]);
		minimum.y = min(minimum.y, m->vertices[3*i + 1]);
		minimum.z = min(minimum.z, m->vertices[3*i + 2]);
	}

	for(uint i = 0; i < m->n_vertices; i++){
		m->vertices[3*i + 0] -= (maximum.x + minimum.x)/2;
		m->vertices[3*i + 1] -= (maximum.y + minimum.y)/2;
		m->vertices[3*i + 2] -= (maximum.z + minimum.z)/2;
	}
}

void generate_vao(model *m)
{
	glGenVertexArrays(1, &m->vertex_array_object);
	glGenBuffers(5, m->buffer_objects);

	glBindVertexArray(m->vertex_array_object);

	/* Vertex buffer data */
	glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[0]);
	glBufferData(GL_ARRAY_BUFFER, m->n_vertices*3*sizeof(GLfloat),
			m->vertices, GL_STATIC_DRAW);

	/* Normal buffer data */
	glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[1]);
	glBufferData(GL_ARRAY_BUFFER, m->n_vertices*3*sizeof(GLfloat),
			m->normals, GL_STATIC_DRAW);
	
	/* Texture coordinates buffer data */
	if(m->texture_coords != NULL){
		glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[2]);
		glBufferData(GL_ARRAY_BUFFER, m->n_vertices*3*sizeof(GLfloat),
			m->texture_coords, GL_STATIC_DRAW);
	
	}

	/* Color buffer data */
	if(m->colours != NULL){
		glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[3]);
		glBufferData(GL_ARRAY_BUFFER, m->n_vertices*4*sizeof(GLfloat),
			m->colours, GL_STATIC_DRAW);
	
	}

	/* Index buffer data */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->buffer_objects[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->n_indices*sizeof(GLuint),
	m->indices, GL_STATIC_DRAW);

}

void draw_model_adjacency(model* m, GLuint shaders, char* gpu_vertex, char* gpu_normal,
		char* gpu_texcoord, char* gpu_colour)
{
	if(m == NULL){
		return;
	}

	GLint gpu_location;

	/* Vertices */
	glBindVertexArray(m->vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[0]);
	gpu_location = glGetAttribLocation(shaders, gpu_vertex);

	if(gpu_location >= 0){
		glVertexAttribPointer(gpu_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(gpu_location);
	}else{
		fprintf(stderr, "Warning: draw_model - %s not found in shader\
 program\n", gpu_vertex);
	}

	if(gpu_normal != NULL){
		gpu_location = glGetAttribLocation(shaders, gpu_normal);
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[1]);
			glVertexAttribPointer(gpu_location, 3, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_normal);
		}
	}

	if(gpu_texcoord != NULL && m->texture_coords != NULL){
		gpu_location = glGetAttribLocation(shaders, gpu_texcoord);
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[2]);
			glVertexAttribPointer(gpu_location, 3, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_texcoord);
		}
	}
	if(gpu_colour != NULL){
		gpu_location = glGetAttribLocation(shaders, "in_colour");
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[3]);
			glVertexAttribPointer(gpu_location, 4, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_colour);
		}
	}

	glPrimitiveRestartIndex(-1);
	glDrawElements(GL_TRIANGLES_ADJACENCY, m->n_indices, GL_UNSIGNED_INT, 0L);
}

void draw_model(model* m, GLuint shaders, char* gpu_vertex, char* gpu_normal,
		char* gpu_texcoord, char* gpu_colour)
{
	if(m == NULL){
		return;
	}

	GLint gpu_location;

	/* Vertices */
	glBindVertexArray(m->vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[0]);
	gpu_location = glGetAttribLocation(shaders, gpu_vertex);

	if(gpu_location >= 0){
		glVertexAttribPointer(gpu_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(gpu_location);
	}else{
		fprintf(stderr, "Warning: draw_model - %s not found in shader\
 program\n", gpu_vertex);
	}

	if(gpu_normal != NULL){
		gpu_location = glGetAttribLocation(shaders, gpu_normal);
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[1]);
			glVertexAttribPointer(gpu_location, 3, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_normal);
		}
	}

	if(gpu_texcoord != NULL && m->texture_coords != NULL){
		gpu_location = glGetAttribLocation(shaders, gpu_texcoord);
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[2]);
			glVertexAttribPointer(gpu_location, 3, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_texcoord);
		}
	}
	if(gpu_colour != NULL){
		gpu_location = glGetAttribLocation(shaders, "in_colour");
		if(gpu_location >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, m->buffer_objects[3]);
			glVertexAttribPointer(gpu_location, 4, GL_FLOAT,
					GL_FALSE, 0, 0);
			glEnableVertexAttribArray(gpu_location);
		} else {
			fprintf(stderr, "Warning: draw_model - %s not found in\
 shader program\n", gpu_colour);
		}
	}

	glDrawElements(GL_TRIANGLES, m->n_indices, GL_UNSIGNED_INT, 0L);
}

model** load_model_adjacency(char* model_file)
{
	const struct aiScene *sce = aiImportFile(model_file, 
			aiProcess_Triangulate | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_GenSmoothNormals |
			aiProcess_FixInfacingNormals |
			aiProcess_GenUVCoords |
			aiProcess_ValidateDataStructure);

	
	model **m = malloc(sce->mNumMeshes*sizeof(model));
	for(uint i = 0; i < sce->mNumMeshes; i++ ){
		m[i] = extract_model_adjacency(*sce->mMeshes[i]);
		center_model(m[i]);
		generate_vao(m[i]);
	}

	aiReleaseImport(sce);

	return m;
}

model** load_model(char* model_file)
{
	const struct aiScene *sce = aiImportFile(model_file, 
			aiProcess_Triangulate | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_GenSmoothNormals |
			aiProcess_FixInfacingNormals |
			aiProcess_GenUVCoords |
			aiProcess_ValidateDataStructure);
	
	model **m = malloc(sce->mNumMeshes*sizeof(model));
	for(uint i = 0; i < sce->mNumMeshes; i++ ){
		m[i] = extract_model(*sce->mMeshes[i]);
		center_model(m[i]);
		generate_vao(m[i]);
	}

	fflush(stdout);

	aiReleaseImport(sce);

	return m;
}

#ifndef FINAL
void event_handler(SDL_Event e)
{
	switch(e.type){
		case SDL_QUIT:
			exit_prog(0);
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym){
				case SDLK_q:
				case SDLK_ESCAPE:
					exit_prog(0);
				default: 
					break;
			}
			break;
		case SDL_VIDEORESIZE:
			resize_window(e);
			break;
		default:
			break;
	}
}

mat_4D proj_matrix;
mat_4D cam_matrix;

void display(model** m, GLuint program)
{
	glUseProgram(program);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	

	mat_4D mat = identity_matrix(); 
	mat.m[0] = 1.0/5;
	mat.m[5] = 1.0/5;
	mat.m[10] = 1.0/5;

	mat = mult(mat, rot_x(90.0));

	glUniformMatrix4fv(glGetUniformLocation(program, "proj_matrix"), 1, GL_TRUE, proj_matrix.m);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GL_TRUE, cam_matrix.m);
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_TRUE, mat.m);

#if ADJACENCY	
	draw_model_adjacency(m[0], program, "in_position", "in_normal", NULL, NULL);
#else
	draw_model(m[0], program, "in_position", "in_normal", NULL, NULL);
#endif /* ADJACENCY */

	SDL_GL_SwapBuffers();
}

void init()
{
	glClearColor(1.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
#if ADJACENCY
	glEnable(GL_PRIMITIVE_RESTART);
#endif /* ADJACENCY */
	glCullFace(GL_BACK);
	proj_matrix = perspective(90.0, 1.0, 0.1, 5000.0);

	vec_3D cam, point, up;
	cam.x = 0.0;
	cam.y = 0.0;
	cam.z = 2.0;

	point.x = 0.0;
	point.y = 0.0;
	point.z = 0.0;

	up.x = 0.0;
	up.y = 1.0;
	up.z = 0.0;
	
	cam_matrix = look_at(cam, point, up);
}
int main()
{

	init_SDL();
	init();

	printf("Init done\n");
#if ADJACENCY
	GLuint program = init_shaders("snowflake.vert", "snowflake.geom", "snowflake.frag");
#else
	GLuint program = init_shaders("simple.vert", "simple.geom", "simple.frag");
#endif /* ADJACENCY */	
	glUseProgram(program);

	printf("shaders loaded and ready to go\n");
#if ADJACENCY
	model **m = load_model_adjacency("only_quad_sphere.obj");
#else
	model **m = load_model("only_quad_sphere.obj");
#endif /* ADJACENCY */

	SDL_Event event;

	while(1){
		while(SDL_PollEvent(&event)){
			event_handler(event);
			display(m, program);
		}
	}

	return 0;
}
#endif /* FINAL */
