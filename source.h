#ifndef _SOURCE_H
#define _SOURCE_H
#include "vector.h"
#include "color.h"

class source{
    
    public:
    
    source();
  
    virtual Vector3 get_light_position(){return Vector3(0.0f,0.0f,0.0f);} 
    virtual color get_color(){return color(1.0f,1.0f,1.0f,0.0f);}
};

source :: source(){}

#endif
