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
#include "color.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "source.h"
using namespace std;
struct RGBType{
    double r;//red
    double g;//green
    double b;//blue
};
float find_plane_intersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 plane_normal, float plane_distance);
float find_sphere_intersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 sphere_origin, int sphere_radius);
color tile (int intersection_x, int intersection_z);
bool checkShadow(Vector3 intersection_position);

color get_plane_at(Vector3 intersection_position, Vector3 intersection_ray_direction, vector<source*>light_sources,float accuracy, float ambientlight){
    //color _color (0.5f, 1.0f,0.5f,0.3
    //cout<<intersection_position.x<<" "<<intersection_position.y<<" "<<intersection_position.z<<endl;
    //cout<<intersection_ray_direction.x<<" "<<intersection_ray_direction.y<<" "<<intersection_ray_direction.z<<endl;

    color plane_color (0.5f, 0.25f, 0.25f, 0.0f);

    color final_color = plane_color.color_scalar(ambientlight);
    //final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
    Vector3 sphere_centre (0.0f,0.0f,0.0f);
    //Vector3 sphere_normal  = (intersection_position + sphere_centre) >> (intersection_position + sphere_centre);
    Vector3 plane_normal = Vector3 (1.0f,0.0f,0.0f);
    float plane_distance = -1.0f;
    Vector3 light_position = Vector3(-7.0f, 10.0f, -10.0f);
    //color light_color(1.0f,1.0f,1.0f,0.0f);
        Vector3 light_direction = (light_position - intersection_position);
        light_direction = light_direction >> light_direction;
        float cosine = plane_normal ^ light_direction;
        //cout<<sphere_normal.x<<sphere_normal.y<<sphere_normal.z<<endl;
        //cout<<light_direction.x<<light_direction.y<<light_direction.z<<endl;
        //cout<<light_position.x<<light_position.y<<light_position.z<<endl;
        //cout<<cosine<<endl;
        //cosine = 1;
        /*if(cosine > 0){
            //test for shadows
            bool shadow = false;
            Vector3 distance_to_light = light_position + intersection_position.multi(-1) >> light_position + intersection_position.multi(-1);
            float distance_to_light_magnitude = distance_to_light % distance_to_light; //magenitude
            //cout<<distance_to_light_magnitude<<endl;

            //ray shadow_ray (intersection_position, distance_to_light);
            Vector3 _direction = light_position + (intersection_position.multi(-1));
            _direction = _direction >> _direction;
            float second_intersection = find_sphere_intersection(intersection_position, _direction, sphere_centre,1);
            float third_intersection = find_plane_intersection(intersection_position,_direction,Vector3(1.0f,0.0f,0.0f),-1);
            //cout<<third_intersection<<endl;
            //cout<<distance_to_light_magnitude<<endl;
            if(third_intersection =! -1 && second_intersection != -1){
                //cout<< "second_intersection < 0.0f"<<endl;
                //cout<<"shadow = false"<<endl;
                if ( second_intersection<=distance_to_light_magnitude){
                    //cout<<"true"<<endl;
                    //shadow is true;
                    //final_color = plane_color.color_scalar(ambientlight);
                    final_color = color (0.0f, 0.0f, 0.0f, 0.0f);
                }
            }
         }*/
        bool s = checkShadow(intersection_position);
        //not in shadow
        if(s==false){
            final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
            //final_color = plane_color;
        }
        else{
            final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
            final_color = final_color.color_scalar(0.3);
        }
    //final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
    return final_color.clip();
}


color get_color_at(Vector3 intersection_position, Vector3 intersection_ray_direction, vector<source*>light_sources,float accuracy, float ambientlight){
    //color _color (0.5f, 1.0f,0.5f,0.3
    //cout<<intersection_position.x<<" "<<intersection_position.y<<" "<<intersection_position.z<<endl;
    //cout<<intersection_ray_direction.x<<" "<<intersection_ray_direction.y<<" "<<intersection_ray_direction.z<<endl;
    
    color sphere_color (0.0f, 0.0f,0.0f,0.3f);
    //color sphere_color (0.5f, 1.0f,0.5f,0.3f);
    color final_color = sphere_color.color_scalar(ambientlight);
    
    Vector3 sphere_centre = Vector3(0.0f,0.0f,0.0f);
    Vector3 sphere_normal  = (intersection_position + sphere_centre) >> (intersection_position + sphere_centre);
/*
    double dot1= sphere_normal ^ (intersection_ray_direction.multi(-1));
    Vector3 scalar1 = sphere_normal.multi(dot1);
    Vector3 add1 = scalar1 + intersection_ray_direction;
    Vector3 scalar2 = add1.multi(2);
    Vector3 add2 = intersection_ray_direction.multi(-1) + scalar2;
    Vector3 reflection_direction = add2 >> add2;


    //final_color = final_color.color_scalar(ambientlight);
    //ray reflection_ray(intersection_position, reflection_direction)
    float reflection_intersection = find_sphere_intersection(intersection_position,reflection_direction,sphere_centre,1);
    //cout<<reflection_intersection<<endl;
    if(reflection_intersection != -1.0f){
        if(reflection_intersection > accuracy){
            Vector3 reflection_intersection_position = intersection_position + (reflection_direction.multi(reflection_intersection));
            Vector3 reflection_ray_direction = reflection_direction;
            color reflection_intersection_color = get_plane_at(reflection_intersection_position,reflection_ray_direction,light_sources,accuracy,ambientlight);
            final_color = final_color.color_add(reflection_intersection_color.color_scalar(0.3));

        }
    }
*/
    Vector3 light_position = Vector3(-7.0f, 10.0f, -10.0f);
    //color light_color(1.0f,1.0f,1.0f,0.0f);//white
    //color light_color(0.5f,0.5f,1.0f,0.0f);//green
    color light_color(0.5f,1.0f,0.5f,0.0f);
    //color light_color(0.5f, 0.25f, 0.25f, 0.0f);//red
        Vector3 light_direction = (light_position - intersection_position);
        light_direction = light_direction >> light_direction;
        //check shadow
        float cosine = sphere_normal ^ light_direction;
        //cout<<sphere_normal.x<<sphere_normal.y<<sphere_normal.z<<endl;
        //cout<<light_direction.x<<light_direction.y<<light_direction.z<<endl;
        //cout<<light_position.x<<light_position.y<<light_position.z<<endl;
        //cout<<cosine<<endl;
        //cosine = 1;
        /*if(cosine > 0){
            //test for shadows
            bool shadow = false;
            Vector3 distance_to_light = light_position + intersection_position.multi(-1) >> light_position + intersection_position.multi(-1);
            float distance_to_light_magnitude = distance_to_light % distance_to_light; //magenitude
            //cout<<distance_to_light_magnitude<<endl;
            
            //ray shadow_ray (intersection_position, distance_to_light);
            //cout<<light_position.x<<light_position.y<<light_position.z<<endl;
            //cout<<intersection_position.x<<intersection_position.y<<intersection_position.z<<endl;
            Vector3 _direction = light_position + (intersection_position.multi(-1));
            _direction = _direction >> _direction;
           // printf("_direction %f %f %f\n",_direction.x,_direction.y,_direction.z);

            float second_intersection = find_sphere_intersection(intersection_position, _direction, sphere_centre, 1);
            float third_intersection = find_plane_intersection(intersection_position,_direction,Vector3(1.0f,0.0f,0.0f),-1);

            //cout<<second_intersection<<endl;

            if(second_intersection > accuracy){
                //cout<< "second_intersection < 0.0f"<<endl;
                //shadow = false;
                if (third_intersection <= distance_to_light_magnitude){
                   //cout<<"true111"<<endl;
                    shadow = false;
                    //return final_color.clip();

                }
            }
            //shadow = false;
            if(shadow = true){
                //cout<< "shadow false"<<endl;
                final_color = final_color.color_add((light_color.color_scalar(cosine)));
                if(sphere_color.get_color_special() > 0 && sphere_color.get_color_special()<=1.0f){
                    double dot1= sphere_normal ^ (intersection_ray_direction.multi(-1));
                    Vector3 scalar1 = sphere_normal.multi(dot1);
                    Vector3 add1 = scalar1 + intersection_ray_direction;
                    Vector3 scalar2 = add1.multi(2);
                    Vector3 add2 = intersection_ray_direction.multi(-1) + scalar2;
                    Vector3 reflection_direction = add2 >> add2;
                    float specular = reflection_direction ^ light_direction;
                    //cout<<specular<<endl;
                    if(specular > 0){
                        specular = pow(specular,10);
                        final_color = final_color.color_add(light_color.color_scalar(specular*0.3f));
                        //cout<<final_color.get_color_red()<<final_color.get_color_green()<<final_color.get_color_blue()<<endl;

                    }
                }
            }
         }*/
        /*bool t = checkShadow(intersection_position);
        if(t == false){
            //cout<<"shadow true"<<endl;
            //final_color = color (0.0f, 0.0f, 0.0f,0.0f);
        }
        else{*/
            final_color = final_color.color_add((light_color.color_scalar(cosine)));
            if(sphere_color.get_color_special() > 0 && sphere_color.get_color_special()<=1.0f){
                double dot1= sphere_normal ^ (intersection_ray_direction.multi(-1));
                Vector3 scalar1 = sphere_normal.multi(dot1);
                Vector3 add1 = scalar1 + intersection_ray_direction;
                Vector3 scalar2 = add1.multi(2);
                Vector3 add2 = intersection_ray_direction.multi(-1) + scalar2;
                Vector3 reflection_direction = add2 >> add2;
                float specular = reflection_direction ^ light_direction;
                if(specular > 0){
                    specular = pow(specular,10);
                    final_color = final_color.color_add(light_color.color_scalar(specular*0.3f));
                }
            }
        //}
    return final_color.clip();
}

color tile (int intersection_x, int intersection_z){
    int square = intersection_x + intersection_z;
    color result (0.0, 0.0,0.0,0.0);
    if(square % 2==0){
        result.set_color_red(0.0f);
        result.set_color_green(0.0f);
        result.set_color_blue(1.0f);
    }else{
        result.set_color_red(1.0f);
        result.set_color_green(1.0f);
        result.set_color_blue(1.0f);
    }
    return result;
}

bool checkShadow(Vector3 intersection_position){
    Vector3 sphere_centre = Vector3(0.0f,0.0f,0.0f);
    Vector3 sphere_normal  = (intersection_position + sphere_centre) >> (intersection_position + sphere_centre);
    Vector3 light_position = Vector3(7.0f, -10.0f, 10.0f);
    Vector3 light_direction = (light_position - intersection_position);
    light_direction = light_direction >> light_direction; // normalization

    //check shadow
    bool shadow = false;
    float cosine = sphere_normal ^ light_direction;
    if(cosine < 0){
        ;//do nothing
    }else{
        shadow = false;
        float second_intersection = find_sphere_intersection(intersection_position, light_direction, sphere_centre, 1);
        if(second_intersection != -1.0f){
            if(second_intersection <= 1.0f){
                shadow = true;
            }
        }
    }
    return shadow;
}


float find_plane_intersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 plane_normal, float plane_distance){
        Vector3 ray_direction_here = ray_direction;
        Vector3 _plane_normal = Vector3(0.0f, 1.0f, 0.0f);
        float a = ray_direction_here ^ _plane_normal;
        if(a == 0){
            //Ray is parallel to our plane
            return -1.0f;
        }else{
            float b = -1*(_plane_normal ^ (ray_origin + _plane_normal))/a;
            return b;
        }

}

float find_sphere_intersection(Vector3 ray_origin, Vector3 ray_direction, Vector3 sphere_origin, int sphere_radius){
    Vector3 ray_origin_here = ray_origin;
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
    float ambientlight = 0.2;
    float accuracy = 0.000001;
    float ratio = (float)width/(float)height; //aspect_ratio
    RGBType *pixels = new RGBType[n];

    Vector3 y = Vector3(0.0f, 1.0f, 0.0f);

    Vector3 look_at = Vector3(0.0f, 0.0f, 0.0f);//cam is looking at 0, 0, 0
    Vector3 cam_position = Vector3(3, 1.5, -4);
    Vector3 diff =  Vector3(-1*(cam_position.x - look_at.x),-1*(cam_position.y - look_at.y),-1*(cam_position.z - look_at.z));
    Vector3 cam_dir = diff >> diff; // normalize diff, operator overloading
    Vector3 cam_right = (y & cam_dir) >> (y & cam_dir);
    Vector3 cam_down = cam_right & cam_dir;
    camera scene_camera (cam_position, cam_dir, cam_right, cam_down);

    color white (1.0f, 1.0f, 1.0f,0.0f);
    
    Vector3 light_position = Vector3(-7.0f, 10.0f, -10.0f);
    light scene_light (light_position, white);
    vector<source*> light_sources;
    light_sources.push_back(dynamic_cast<source*>(&scene_light));
 
    Vector3 o = Vector3(0.0f, 0.0f, 0.0f); 
    //sphere
    //sphere scene_sphere (Vector3(0.0f,0.0f,0.0f), 1, green);
    //plane scene_plane (y, -1, plane_color);

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
            
            Vector3 cam_ray_pos = scene_camera.get_camera_position();
            Vector3 tmp = (cam_dir + (cam_right.multi(xamnt-0.5) + cam_down.multi(yamnt-0.5)));
            Vector3 cam_ray_direction = tmp >> tmp;
             
            ray cam_ray (cam_ray_pos, cam_ray_direction);

            float sphere_intersection = find_sphere_intersection(cam_ray_pos, cam_ray_direction, o, 1);
            float plane_intersection = find_plane_intersection(cam_ray_pos, cam_ray_direction, y, -1);

            if(sphere_intersection == -1.0f){
                if(plane_intersection == -1.0f ){
                    pixels[thisone].r = 0;
                    pixels[thisone].g = 0;
                    pixels[thisone].b = 0;
                }else{
                    Vector3 intersection_position = cam_ray_pos + (cam_ray_direction.multi(plane_intersection));
                    Vector3 intersection_ray_direction = cam_ray_direction;
                    color final_plane=get_plane_at(intersection_position,intersection_ray_direction, light_sources,accuracy,ambientlight);
                        if (plane_intersection <= 1 ){
                            pixels[thisone].r = 0.0f;
                            pixels[thisone].g = 0.0f;
                            pixels[thisone].b = 0.0f;
                        }else{
                            pixels[thisone].r = final_plane.get_color_red();
                            pixels[thisone].g = final_plane.get_color_green();
                            pixels[thisone].b = final_plane.get_color_blue();
                        }
                }
            }else{
                if(sphere_intersection > accuracy){
                    Vector3 intersection_position = cam_ray_pos + (cam_ray_direction.multi(sphere_intersection));
                    Vector3 intersection_ray_direction = cam_ray_direction;
                     
                    color intersection_color = get_color_at(intersection_position, intersection_ray_direction,light_sources,0.0f,ambientlight);
                    pixels[thisone].r=intersection_color.get_color_red();
                    pixels[thisone].g=intersection_color.get_color_green();
                    pixels[thisone].b=intersection_color.get_color_blue();
                }
            }
        }
    }
    
    savebmp("scene.bmp", width, height, dpi, pixels);
    return 0;
}
