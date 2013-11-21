#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include "zpr.h"

Model *m;

mat4 projectionMatrix;

mat4 objectExampleMatrix;
mat4 viewMatrix;  

vec3 cam = vec3(0,0,-1);
vec3 point = vec3(0,0,0);

GLuint program;

void init(void)
{

	dumpInfo();

	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	printError("GL inits");

	projectionMatrix = perspective(90, 1.0, 0.1, 1000);

	vec3 p = vec3(0,0, -0.5);
	vec3 l = vec3(0,0,0);
	vec3 v = vec3(0,1,0);
	viewMatrix = lookAtv(p,l,v); 

	// Load and compile shader
	program = loadShaders("src/simple.vert", "src/simple.frag");
	printError("init shader");
	
	// Upload geometry to the GPU:
	m = LoadModelPlus("src/obj/stanford-bunny.obj");
	printError("load models");

	// Load textures
//	LoadTGATextureSimple("textures/maskros512.tga",&texture);
//	printError("load textures");
	objectExampleMatrix = IdentityMatrix();
}

void display(void)
{
	printError("pre display");

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//activate the program, and set its variables
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
	mat4 mat = Mult(viewMatrix, objectExampleMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_TRUE, mat.m);

	//draw the model
	DrawModel(m, program, "in_Position", "in_Normal", NULL);
	
	printError("display");
	
	glutSwapBuffers();
}

void idle()
{
  // This function is called whenever the computer is idle
  // As soon as the machine is idle, ask GLUT to trigger rendering of a new frame
  glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitContextVersion(3, 2);
	glutCreateWindow ("Simple program, start of camera stuff");
//	zprInit(&viewMatrix, cam, point);
	glutDisplayFunc(display); 
	glutIdleFunc(idle);
	init ();
	glutMainLoop();
}
