
#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include "zpr.h"
#include <GL/gl.h>
#include "object.h"
      

//Model *m;
Object o;
float i;
mat4 projectionMatrix;

mat4 objectExampleMatrix;
mat4 viewMatrix;  

vec3 cam = vec3(0,0,-1);
vec3 point = vec3(0,0,0);
vec3 lightSourceDirection = vec3{4, 3, 3};
vec3 lightSourceColor = vec3{1,1,1};
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
//m = LoadModelPlus("src/obj/stanford-bunny.objglUniform1i(glGetUniformLocation(program, "skyTex"), 1); ");
//printError("load models");
o = Object("src/obj/bunnyplus.obj", "src/obj/grass.tga");


// Load textures
//	LoadTGATextureSimple("textures/maskros512.tga",&texture);
//	printError("load textures");
objectExampleMatrix = IdentityMatrix();

// Ladda upp ljus
glUniform3fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);
glUniform3fv(glGetUniformLocation(program, "lightSourceColor"),1, &lightSourceColor.x);

i=0;

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
// DrawModel(m, program, "in_Position", "in_Normal", "in_TexCoord");
// printError("display");
o.rotate('y',10*i );
i = i + 1;
o.update();
o.draw(program);
glutSwapBuffers();

if(i==20){
i= 0;
}
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
zprInit(&viewMatrix, cam, point);
glutDisplayFunc(display); 
glutIdleFunc(idle);
init ();
glutMainLoop();
}
