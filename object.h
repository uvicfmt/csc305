#ifndef _OBJECT_H
#define _OBJECT_H

#include "vector.h"
#include "color.h"
#include "ray.h"

class object{
    
    public:
    
    object();
  
    color get_object_color(){return color(0.0f,0.0f,0.0f,0.0f);} 

    float find_intersection(ray _ray){
        return 0.0f;
    }  
};

object :: object(){}

#endif
