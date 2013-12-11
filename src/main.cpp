#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include <GL/gl.h>
#include "world.h"
#include "object.h"
#include "body.h"
#include "math.h"      

//Model *m;
World w;

vec3 lightSourceDirection = vec3{4, 3, 3};
vec3 lightSourceColor = vec3{1,1,1};
GLuint program;
int leftMB;

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

bool inside_range(float x, float y, int mouse_x, int mouse_y){
  if((abs(x - mouse_x) < 5) && (abs(y - mouse_y) < 5)){
    return true;
  }
}

void MouseClickFunc( int button, int state, int x, int y) {
	
  if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) {
    if(inside_range(w.o.position.x, w.o.position.y, x, y)){
      leftMB = !leftMB;
    }
    if(leftMB == 1){
      w.o.place(vec3((float)(x), (float)(y), w.cam.position.z - 5));
    }
  }
} 



void init(void)
{

dumpInfo();

//Init MouseButton state
 leftMB = 0;

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


int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitContextVersion(3, 2);
  glutCreateWindow ("Simple program, start of camera stuff");
  glutDisplayFunc(display); 
  glutIdleFunc(idle);
  glutKeyboardUpFunc(&keyboard);
  glutMouseFunc(&MouseClickFunc);
    init ();
  glutMainLoop();
}
