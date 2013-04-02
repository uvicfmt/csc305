#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<limits>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "vector.h" //vector operations
#include "vector.cpp"
#include "matrix.h" //matrix operations
#include "matrix.cpp"
#include "ray.h"
#include "camera.h"
using namespace std;

float t = 10000;
struct RGBType{
    double r;//red
    double g;//green
    double b;//blue
};


float find_nearest_object(float sphere_intersection, float plane_intersection){
    int i;
    if(sphere_intersection == -1 && plane_intersection == -1){
        return -1.0f;
    }
    else if((sphere_intersection != -1 && plane_intersection == -1) || (sphere_intersection == -1 && plane_intersection != -1)){
        if(sphere_intersection > 0 || plane_intersection > 0){
            return 0.0f;
        }else{
            return -1.0f;
        }
    }
    else{
        float max_value=0.0f;
        float min_value=0.0f;
        if(sphere_intersection > plane_intersection){
            max_value =  sphere_intersection;
            min_value = plane_intersection;
        }else{
            max_value =  plane_intersection;
            min_value = sphere_intersection;
        }
        if(max_value > 0){
           return min_value;      
        }else{
            return -1;
        }
    }
}

float find_plane_intersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 plane_normal, float plane_distance){
        Vector3 ray_direction_here = ray_direction;
        float a = ray_direction ^ plane_normal;
        
        if(a == 0){
            //Ray is parallel to our plane
            return -1;
        }else{
            Vector3 planeNormal = Vector3(-1*plane_normal.x*plane_distance, -1*plane_normal.y*plane_distance, -1*plane_normal.z*plane_distance);
            float b = plane_normal ^ (ray_origin + (planeNormal));
            return -1/b*a;
        }
}

float find_sphere_intersection(float t, Vector3 ray_origin, Vector3 ray_direction, Vector3 sphere_origin, int sphere_radius){
  /*  Vector3 ray_origin_here = ray_origin;
    float ray_o_x = ray_origin.x;
    float ray_o_y = ray_origin.y;
    float ray_o_z = ray_origin.z;


    Vector3 ray_direction_here = ray_direction;
    float ray_d_x = ray_direction.x;
    float ray_d_y = ray_direction.y;
    float ray_d_z = ray_direction.z;

    Vector3 sphere_origin_here = sphere_origin;
    //sphere_origin.x = 
    float sphere_origin_x = sphere_origin.x;
    float sphere_origin_y = sphere_origin.y;
    float sphere_origin_z = sphere_origin.z;

    float a = 1;
    float b = (2*(ray_o_x - sphere_origin_x)*ray_d_x)+ (2*(ray_o_y - sphere_origin_y)*ray_d_y) + (2*(ray_o_z - sphere_origin_z)*ray_d_z);
    float c = pow(ray_o_x - sphere_origin_x, 2) + pow(ray_o_y - sphere_origin_y, 2) + pow(ray_o_z - sphere_origin_z, 2) - (sphere_radius*sphere_radius);
    
    float disc = b*b - 4*c;

    if(disc <= 0){
        //then no intersction btw ray and sphere
        //cout<<"No intersection: "<<-1<<endl;
        return -1;
    }else{
        float d = sqrt(disc);
        float p1 = ((-1*b - d)/2);
        if(p1 > 0){
            //the first root is the smallest positive root
            //cout<<"Root 1: "<<p1<<endl;
            return p1;
        }else{
            // the second root is the smallest positive root
            float p2 = ((d - b)/2);
            //cout<<"Root 2: "<<p2<<endl;
            return p2;
        }
    }*/
   // float t = 10000;
    Vector3 dst =  sphere_origin - ray_origin;
    float b = (dst^ray_direction);
    float disc = b*b - (dst^dst) + (sphere_radius * sphere_radius);

    //cout << "disc : "<<disc<<endl;
    if(disc < 0.0f ){
        return -1.0;
    }
    float t0 = -1*b - sqrt(disc);
    float t1 = -1*b + sqrt(disc);
    //cout << "t0 : "<<t0<<endl;
    //cout << "t1 : "<<t1<<endl;
    if((t0 > 0.1f) && (t0 < t)){
        t = (float)t0;
        return 1.0f;
    }

    if((t1 > 0.1f) && (t1 < t)){
        t = (float)t1;
        return -1.0f;
    }
}

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data){
    FILE *f;
    int k = w*h;
    int s = 4*k;
    int filesize = 54 + s;
    double factor = 39.375;
    int m = static_cast<int>(factor);
    int ppm = dpi*m;
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize>>8);
    bmpfileheader[4] = (unsigned char)(filesize>>16);
    bmpfileheader[5] = (unsigned char)(filesize>>24);
    
    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w>>8);
    bmpinfoheader[6] = (unsigned char)(w>>16);
    bmpinfoheader[7] = (unsigned char)(w>>24);
    
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h>>8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    bmpinfoheader[21] = (unsigned char)(s);
    bmpinfoheader[22] = (unsigned char)(s>>8);
    bmpinfoheader[23] = (unsigned char)(s>>16);
    bmpinfoheader[24] = (unsigned char)(s>>24);

    bmpinfoheader[25] = (unsigned char)(ppm);
    bmpinfoheader[26] = (unsigned char)(ppm>>8);
    bmpinfoheader[27] = (unsigned char)(ppm>>16);
    bmpinfoheader[28] = (unsigned char)(ppm>>24);

    bmpinfoheader[29] = (unsigned char)(ppm);
    bmpinfoheader[30] = (unsigned char)(ppm>>8);
    bmpinfoheader[31] = (unsigned char)(ppm>>16);
    bmpinfoheader[32] = (unsigned char)(ppm>>24);
    
    f = fopen(filename,"wb");
    fwrite(bmpfileheader, 1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<k; i++){
        RGBType rgb = data[i];
        double red = (data[i].r)*255;
        double green = (data[i].g)*255;
        double blue = (data[i].b)*255;

        unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};
        fwrite(color,1,3,f);
    }
    
    fclose(f);
}

int thisone;
int main(int argc, char *argv[]){
    cout << "rendering ..."<<endl;
    int dpi = 72;
    int width = 640;
    int height = 480;
    int n = width * height;
    float ratio = (float)width/(float)height; //aspect_ratio
    RGBType *pixels = new RGBType[n];
   
    //ray has origin and direction: ray (vec3 origin, vec3 direction)
    Vector3 ray_origin = Vector3(0.0f,0.0f,0.0f);
    Vector3 ray_direction = Vector3(1.0f,0.0f,0.0f);    

    Vector3 x = Vector3(1.0f, 0.0f, 0.0);
    Vector3 y = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 z = Vector3(0.0f, 0.0f, 1.0f);
     
    Vector3 look_at = Vector3(0.0f, 0.0f, 0.0f); //let the look at be origin
    
    //camera's parameters:
    Vector3 cam_pos = Vector3(3.0f, 1.5f, -4.0f);

    // The difference between cam_pos and look_at
    Vector3 diff = Vector3(cam_pos.x - look_at.x, cam_pos.y-look_at.y, cam_pos.z-look_at.z);
    Vector3 tmp = diff.negative(diff);
    Vector3 cam_dir = (tmp)>>(tmp);//cam_dir = -diff.normailze

    Vector3 cam_right = y & cam_dir; //cross pruduct btw y and cam_dir  
    Vector3 cam_down = cam_right & cam_dir;
    // scene_cam = (cam_pos, cam_dir, cam_right, cam_down)

    //Colors: 
    Vector4 white_light = Vector4(1.0f,1.0f,1.0f,0.0f);//Color(red, green, blue, special)
    Vector4 Green = Vector4(0.5,1.0,0.5,0.3);
    Vector4 gray = Vector4(0.5,0.5,0.5,0.5);
    Vector4 black = Vector4(0.0,0.0,0.0,0.0);
    //Light = (Vector3 position, Vector4 color)
    Vector3 light_position = Vector3(-7.0f,10.0f,-10.0f);
    
   // Light = (light_position, white_light)

    //sphere has origin, radius and color (find interaction)
    //sphere (origin, 1 , pretty green)
    Vector3 sphere_origin = Vector3(0.0f,0.0f,0.0f);
    float value = -1.0f;
    int sphere_radius = 1;
    Vector4 sphere_color = Green;

    //plane has normal, distance, planeColor (find interaction)
    //plane (Y, -1,plane_color)
    Vector3 plane_normal = y;//Y
    int plane_distance = -1;
    Vector4 plane_color = Vector4(0.5f, 0.25f, 0.25f, 0.0f);

    float xamnt; float yamnt;
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            //return color
            thisone = y * width + x;
            // start with no anti-aliasing
            if(width > height){
                xamnt = ((x + 0.5)/width)*ratio - (((width-height)/(float)height)/2);
                yamnt = ((height-y)+0.5)/height;
            }
            //image is taller
            else if(height > width){
                xamnt = (x + 0.5) / width;
                yamnt = (((height-y) + 0.5)/height)/ratio - (((height-width)/(float)width)/2);
            }
            else{//image is square
                xamnt = (x + 0.5)/width;
                yamnt =((height - y)+0.5)/height;
            }
            
            Vector3 cam_ray_pos = cam_pos;

            float tmp_xamnt = xamnt - 0.5;
            float tmp_yamnt = yamnt - 0.5;
            Vector3 tmp_right = Vector3(cam_right.x*tmp_xamnt, cam_right.y*tmp_xamnt, cam_right.z*tmp_xamnt);
            Vector3 tmp_down =  Vector3(cam_down.x*tmp_yamnt, cam_down.y*tmp_yamnt, cam_down.z*tmp_yamnt);
            Vector3 cam_ray_dir = cam_dir + ((tmp_right+tmp_down)>>(tmp_right+tmp_down));
        
            //camera ray = (cam_ray_origin(pos), cam_ray_direction);
            float sphere_intersection = find_sphere_intersection(t, cam_ray_pos, cam_ray_dir, sphere_origin, sphere_radius);
            float plane_intersection = find_plane_intersection(ray_origin, ray_direction, plane_normal, plane_distance);
            float nearest_object = find_nearest_object(sphere_intersection, plane_intersection);
             
            //cout<<sphere_intersection<<" ";

            if(sphere_intersection <= 0){
                pixels[thisone].r = 0;
                pixels[thisone].g = 0;
                pixels[thisone].b = 0;
            }else{
                
                pixels[thisone].r=Green.x;
                pixels[thisone].g=Green.y;
                pixels[thisone].b=Green.z;
            
            }
        }
    }

    savebmp("scene.bmp", width, height, dpi, pixels);
    return 0;
}
