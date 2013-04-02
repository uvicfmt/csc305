#ifndef _RAY_H
#define _RAY_H

#include "vector.h"

class ray {
    Vector3 ray_origin;
    Vector3 ray_direction;
    public:
    
    ray();
    ray(Vector3, Vector3);
       
    Vector3 get_ray_origin(){return ray_origin;}
    Vector3 get_ray_direction(){return ray_direction;}
};

ray::ray(){
    ray_origin = Vector3(0.0f, 0.0f, 0.0f);
    ray_direction = Vector3(1.0f, 0.0f, 0.0f);
}

ray::ray(Vector3 origin, Vector3 direction){
    ray_origin = origin;
    ray_direction = direction;
}


#endif

