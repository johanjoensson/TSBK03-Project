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

#include <iostream>  
/*
#define FAR 100
#define NEAR 1
#define RIGHT 0.5
#define LEFT -0.5
#define TOP  0.5
#define BOTTOM -0.5
*/

int window_width = 400;
int window_height = 400;

int old_mouse_x = 150;
int old_mouse_y = 150;
//Model *m;
World w;


vec4 lightSourceDirection = vec4{3.0,3.0,0.0,1.0};
vec3 lightSourceColor = vec3{1,1,1};
GLfloat t;
GLuint program, shadows;
bool c, leftMB, disp_volumes;
mat4 projectionMatrix;


void keyboard(unsigned char key, int x, int y)
{
  vec3 left = CrossProduct(w.cam.up, w.cam.forward);
  switch(key){
  case 'w':
    w.cam.place(0.5*w.cam.forward);
    break;
  case 's':
    w.cam.place(0.5*VectorSub(vec3(0,0,0),w.cam.forward));
    break;
  case 'a':
    w.cam.place(0.5*left);
    break;
  case 'd':
    w.cam.place(0.5*VectorSub(vec3(0,0,0),left));
    break;
  case 'v':
    disp_volumes = !disp_volumes;
  case 'c':
    c = !c;
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
  c = true;
  disp_volumes = false;
  // GL inits
  glClearColor(0.0,0.0,0.0,0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  printError("GL inits");
  // Load and compile shader
  shadows = loadShadersG("src/shadows.vert", "src/shadows.frag", "src/shadows.geom");
  program =  loadShaders("src/simple.vert", "src/simple.frag");//, "src/pass_through.geom");
//  bla =  loadShaders("src/simple.vert", "src/simple2.frag");//, "src/pass_through.geom");
printError("init shader");

//Ladda upp projectionMatrix
//projectionMatrix = frustum(LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR);
//projectionMatrix = perspective(90, 1.0, 0.1, 1000);

//glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
//glUniformMatrix4fv(glGetUniformLocation(shadows, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);


  w = World();


  // Ladda upp ljusfarg
  glUniform3fv(glGetUniformLocation(program, "lightSourceColor"),1, &lightSourceColor.x);
  glUniform4fv(glGetUniformLocation(shadows, "lightSourceDir"), 1, &lightSourceDirection.x);
   glUniform4fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);

}

void display(void)
{
  printError("pre display");
  glDepthMask(GL_TRUE);
  // clear the screen
  //lightSourceDirection = vec4(w.cam.position.x,w.cam.position.y,w.cam.position.z,1.0); 
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);  
  
  glUseProgram(program);
  glUniform4fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);

  
  // Initialize depth buffer and stencil buffer
  glColorMask(GL_TRUE,GL_TRUE,GL_FALSE,GL_FALSE);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_NEVER,0,0xFFFFFFFF);	//Write 0's in stencil buffer
  glStencilOp(GL_REPLACE,GL_KEEP,GL_KEEP);	// See above
  w.draw(program);
  
  // Set up the stencil buffer

  if (c)
 {
      glDepthMask(GL_FALSE);}	//Turn off depth-test
  

  glUseProgram(shadows);	// Switch to shadow volume generation 
  glUniform4fv(glGetUniformLocation(shadows, "lightSourceDir"), 1, &lightSourceDirection.x);

  glCullFace(GL_BACK);
  glStencilFunc(GL_ALWAYS,0,0xFFFFFFFF);
  glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);	// Increment stencil buffer on depth-pass

  w.draw(shadows);
  //w.o.draw(program);
  
  glCullFace(GL_FRONT);
  glStencilFunc(GL_ALWAYS,0,0xFFFFFFFF);

  glStencilOp(GL_KEEP,GL_KEEP,GL_DECR); // Decrement stencil buffer on depth-pass

  w.draw(shadows);   

  // w.o.draw(program);

  // Reset depth and color 
  glDepthMask(GL_TRUE);  
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
  
  
  //draw scene
  glCullFace(GL_BACK);
  glUseProgram(program);
  glUniform4fv(glGetUniformLocation(program, "lightSourceDir"), 1, &lightSourceDirection.x);


  glStencilFunc(GL_EQUAL,0,0xFFFFFFFF);	//Draw lighted areas
  glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);	//Don't change the stencil buffer
  w.draw(program);
  
  glDisable(GL_STENCIL_TEST);	//Disable stencil buffer
  
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
  float dy = ((float) y - old_mouse_y)/win_height;
  
  old_mouse_x = x;
  old_mouse_y = y;

  w.cam.h_rotate(dx*M_PI*2*0.1);
  w.cam.v_rotate(dy*M_PI*2*0.1);
  if(leftMB){
    w.o.place(w.cam.position + 4*w.cam.forward);
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_STENCIL);
  glutInitContextVersion(3, 2);
  glutCreateWindow ("Use the FORCE young yeti!");
  glutDisplayFunc(display); 
  glutReshapeFunc(&window_reshape);
  glutIdleFunc(idle);
  glutKeyboardUpFunc(&keyboard);
  glutPassiveMotionFunc(mouse_passive_move);
  glutMouseFunc(&MouseClickFunc);
  init ();


  GLint num = 5;
  glGetIntegerv(GL_STENCIL_BITS, &num);
  std::cout << "Size of stencil buffer:" << num << std::endl;

  glutMainLoop();
}
