#ifndef _LIGHT_H
#define _LIGHT_H

#include "vector.h"
#include "source.h"

class light : public source{
    Vector3 light_position;
    color c;
    public:
    
    light();
    light(Vector3, color);
       
    Vector3 get_light_position(){return light_position;}
    color get_light_color(){return c;}
};

light::light(){
    light_position = Vector3(0.0f, 0.0f, 0.0f);
    c = color(1.0f, 1.0f, 1.0f, 0.0f);
}

light::light(Vector3 position, color c1){
    light_position = position;
    c = c1;
}


#endif

