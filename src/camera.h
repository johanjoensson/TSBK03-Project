#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"

class Camera: public Object{
    protected:
        float far;
        float near;
        float top;
        float bottom;
        float right;
        float left;

        mat4 projectionMatrix;
    public:
        vec3 forward;
        vec3 up; 

        mat4 view_matrix;

        void update();
        void rotate(char direction, float angle);
        void rotate(vec3 dir, float angle);

        void draw(int program);

        Camera();
};


#endif /*CAMERA_H */
