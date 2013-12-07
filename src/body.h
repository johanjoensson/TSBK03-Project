#ifndef BODY_H
#define BODY_H

#include "object.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "GL_utilities.h"

class Body: public Object{
    protected:
        mat4 scale_mat;
        float scale;
    public:
        Model *m;
        // Functions
        void set_scale(float);
        float get_scale(); 

        float reflectivity;
        GLuint texture;

        void update();
        void rotate(char direction, float angle);
        void draw(int);

        Body();
        Body(const char*);
        Body(const char*, const char*);
};

#endif /*BODY_H*/
