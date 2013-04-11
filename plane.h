#ifndef _PLANE_H
#define _PLANE_H
#include "vector.h"
#include "color.h"
#include "ray.h"

class plane{
    Vector3 plane_normal;
    float plane_distance;
    color plane_color;

    public:
    
    plane();
    plane(Vector3, float, color);
       
    Vector3 get_plane_normal(){return plane_normal;}
    float get_plane_distance(){return plane_distance;}
    color get_plane_Color(){return plane_color;}

    Vector3 get_normal_at(Vector3 point){
        return plane_normal;
    }
    
    /*float find_intersection(ray _ray){
        Vector3 ray_direction = _ray.get_ray_direction();
        float a = ray_direction ^ plane_normal;
        if (a == 0){
            return -1.0f; 
        }else{
            //float tmp = plane_normal
            float b = plane_normal ^ (_ray.get_ray_origin() + (plane_normal.multi(plane_distance).multi(-1.0f)));
            return -1*b/a;
        }
  
    }*/

};

plane :: plane(){
    plane_normal = Vector3(1.0f, 0.0f, 0.0f);
    plane_color = color(0.5f, 0.5f, 0.5f, 0.0f);
    plane_distance = 0.0f;
}

plane :: plane(Vector3 normal, float distance, color c){
    plane_normal = normal;
    plane_distance = distance;
    plane_color = c;
    
}

#endif
