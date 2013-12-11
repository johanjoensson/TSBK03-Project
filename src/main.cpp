#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include <GL/gl.h>
#include "world.h"
#include "object.h"
#include "body.h"
      

//Model *m;
World w;

vec3 lightSourceDirection = vec3{4, 3, 3};
vec3 lightSourceColor = vec3{1,1,1};
GLuint program;

void keyboard(unsigned char key, int x, int y)
{
    vec3 left = CrossProduct(w.cam.up, w.cam.forward);
    switch(key){
        case 'w':
            w.cam.place(w.cam.forward);
            break;
        case 's':
            w.cam.place(VectorSub(vec3(0,0,0),w.cam.forward));
            break;
        case 'a':
            w.cam.place(left);
            break;
        case 'd':
            w.cam.place(VectorSub(vec3(0,0,0),left));
            break;
        case  27:
            exit(0);
            break;
        default:
            break;
    }
}


void init(void)
{

dumpInfo();

// GL inits
glClearColor(0.2,0.2,0.5,0);
glEnable(GL_DEPTH_TEST);
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
printError("GL inits");

// Load and compile shader
program = loadShaders("src/simple.vert", "src/simple.frag");
printError("init shader");
	
 w = World();



// Ladda upp ljus
glUniform3fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);
glUniform3fv(glGetUniformLocation(program, "lightSourceColor"),1, &lightSourceColor.x);


}

void display(void)
{
printError("pre display");

// clear the screen
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//activate the program, and set its variables
glUseProgram(program);


// Draw the scene
w.draw(program);
glutSwapBuffers();
}

void idle()
{
// This function is called whenever the computer is idle
// As soon as the machine is idle, ask GLUT to trigger rendering of a new frame
glutPostRedisplay();
}

void window_reshape(int width, int height)
{
	glViewport(0,0,width, height);
}


int main(int argc, char *argv[])
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
glutInitContextVersion(3, 2);
glutCreateWindow ("Simple program, start of camera stuff");
glutDisplayFunc(display); 
glutReshapeFunc(&window_reshape);
glutIdleFunc(idle);
glutKeyboardUpFunc(&keyboard);
init ();
glutMainLoop();
}
