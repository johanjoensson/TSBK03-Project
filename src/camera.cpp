#include <GL/gl.h>
#include "camera.h"

Camera::Camera()
{
    far = 1000;
    near = 0.1;
    right = 1;
    left = -1;
    top = 1;
    bottom = -1;


    projectionMatrix = perspective(90, 1.0, 0.1, 1000);
//    projectionMatrix = frustum(left, right, bottom, top, near, far);

    forward = vec3(0,0,-1);
    up = vec3(0,1,0);
    position = vec3(0,0,1);


    view_matrix = lookAtv(position,forward,up); 
}

void Camera::update()
{
    position = trans_mat*position;
    forward = rot_mat*forward;
    up = rot_mat*up;
    
    view_matrix = lookAtv(position,VectorAdd(position,forward),up); 
}

void Camera::rotate(char direction, float angle)
{
    switch (direction) {
        case 'x':
            // Rotate around x
            rot_mat = Rx(angle) * rot_mat;
            break;
        case 'y':
            // Rotate around y
            rot_mat = rot_mat * Ry(angle) * rot_mat;
            break;
        case 'z':
            // Rotate around z
            rot_mat = Rz(angle) * rot_mat;
            break;
    }
    update();
}

void Camera::draw(int program)
{
    glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, projectionMatrix.m);
    glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_TRUE, view_matrix.m);
}
