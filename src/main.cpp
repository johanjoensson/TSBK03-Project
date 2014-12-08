#include "MicroGlut.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "GL_utilities.h"
#include <GL/gl.h>
#include <cmath>
#include "world.h"
#include "object.h"
#include "body.h"
#include "math.h"      

int window_width = 300;
int window_height = 300;

int old_mouse_x = 150;
int old_mouse_y = 150;
//Model *m;
World w;

vec4 lightSourceDirection = vec4{5,3,-5,1};
vec3 lightSourceColor = vec3{1,1,1};
GLfloat t;
GLuint program;
bool leftMB;

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
  if((abs(x - mouse_x) < 2) && (abs(y - mouse_y) < 2)){
    return true;
  }
}

void MouseClickFunc( int button, int state, int x, int y) {
  float mouse_x = (window_width/2 - x)/(window_width/2);
  float mouse_y = (window_height/2 - y)/(window_height/2);
 
  if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) {
    if(inside_range(w.o.position.x, w.o.position.y, mouse_x, mouse_y)){
      leftMB = !leftMB;
    }
  }
 
} 



void init(void)
{
  
  dumpInfo();
  t=0;
  //Init MouseButton state
  leftMB = false;
 
  // GL inits
  glClearColor(0.2,0.2,0.5,0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  printError("GL inits");
  // Load and compile shader
  program = loadShadersG("src/simple.vert", "src/simple.frag", "src/simple.geom");
  printError("init shader");
 
  w = World();



  // Ladda upp ljusfarg
  glUniform3fv(glGetUniformLocation(program, "lightSourceColor"),1, &lightSourceColor.x);


}

void display(void)
{
  printError("pre display");

  // clear the screen
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  //activate the program, and set its variables
  glUseProgram(program);
  lightSourceDirection.x = (float)(sin(t*M_PI/180));
  lightSourceDirection.y= 3.0f;
  lightSourceDirection.z= (float)(5*cos(t*M_PI/180));
  lightSourceDirection.w= 2.0f;
  glUniform4fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);
  t+=0.02;
  if(t>359)
    {
      t=0.0;}
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
  window_width = width;
  window_height = height;
  glViewport(0,0,width, height);
}

void mouse_passive_move(int x, int y)
{
  /* Dimensions of the window */
  int win_width = window_width;
  int win_height = window_height;

  float dx = ((float)old_mouse_x - x)/win_width;
  float dy = ((float)y - old_mouse_y)/win_height;

  old_mouse_x = x;
  old_mouse_y = y;

  w.cam.h_rotate(dx*M_PI*2);
  w.cam.v_rotate(dy*M_PI*2);
  if(leftMB){
    w.o.place(w.cam.position + w.cam.forward);
  }
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
  glutPassiveMotionFunc(mouse_passive_move);
  glutMouseFunc(&MouseClickFunc);
  init ();
  glutMainLoop();
}
