#ifndef _SPHERE_H
#define _SPHERE_H
#include "vector.h"
#include "color.h"
#include "object.h"

class sphere : public object{
    Vector3 sphere_centre;
    float sphere_radius;
    color sphere_color;
    public:
    
    sphere();
    sphere(Vector3, float, color);
       
    Vector3 get_sphere_centre(){return sphere_centre;}
    float get_sphere_radius(){return sphere_radius;}
    color get_sphere_Color(){return sphere_color;}

};

sphere :: sphere(){
    sphere_centre = Vector3(0.0f, 0.0f, 0.0f);
    sphere_color = color(0.5f, 0.5f, 0.5f, 0.0f);
    sphere_radius = 1.0f;
}

sphere :: sphere(Vector3 position, float radius, color c){
    sphere_centre = position;
    sphere_radius = radius;
    sphere_color = c;
    
}

#endif

