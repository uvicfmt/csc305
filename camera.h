#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector.h"

class camera{
    Vector3 camera_position;
    Vector3 camera_direction;
    Vector3 camera_right;
    Vector3 camera_down;
    
    public:
    
    camera();
    camera(Vector3, Vector3, Vector3, Vector3);
       
    Vector3 get_camera_position(){return camera_position;}
    Vector3 get_camera_direction(){return camera_direction;}
    Vector3 get_camera_right(){return camera_right;}
    Vector3 get_camera_down(){return camera_down;}
};

camera::camera(){
    camera_position = Vector3(0.0f, 0.0f, 0.0f);
    camera_direction = Vector3(0.0f, 0.0f, 1.0f);
    camera_right = Vector3(0.0f,0.0f,0.0f);
    camera_down = Vector3(0.0f,0.0f,0.0f);
}

camera::camera(Vector3 position, Vector3 direction, Vector3 right, Vector3 down){
    camera_position = position;
    camera_direction = direction;
    camera_right = right;
    camera_down = down;
}


#endif
