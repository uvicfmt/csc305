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
#include "color.h"



int shadow_check = 1;
int pretty_blue = 0;

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
color reflection(Vector3 sphere_normal, Vector3 intersection_ray_direction, Vector3 intersection_position, float ambientlight);
color refraction(Vector3 sphere_normal, Vector3 light_direction, Vector3 intersection_position);


//calculate diffuse color
color diffuse (Vector3 light_direction, Vector3 sphere_normal, Vector3 intersection_ray_direction){
    color sphere_color (0.0f, 0.0f, 0.0f, 0.3f);
    float cosine = light_direction ^ sphere_normal;
    if(cosine > 0.0f){
        sphere_color.color_scalar(cosine);
    }
    return sphere_color;
}

//calculate phong illumination
float specular (Vector3 light_direction, Vector3 sphere_normal,Vector3 intersection_ray_direction){

    //calculate the diffuse
    float reflet =  (light_direction ^ sphere_normal)*2.0f;
    Vector3 phong = light_direction - (sphere_normal.multi(reflet));
    float phong_term = 0.0f;
    if((phong ^ intersection_ray_direction) > 0.0f){
        phong_term = (phong ^ intersection_ray_direction);
    }else{
        phong_term = 0.0f;
    }
    
    //caluclate spacular for phong_term
    phong_term = 0.3f * pow(phong_term, 32) * 1.0f;
    
    return phong_term;
}


//This function will get the color for plane
//as well as. calculate the shadow
color get_plane_at(Vector3 intersection_position, Vector3 intersection_ray_direction,float accuracy, float ambientlight){

    color plane_color (0.5f, 0.25f, 0.25f, 0.0f);

    color final_color = plane_color.color_scalar(ambientlight);
    Vector3 sphere_centre (0.0f,0.0f,0.0f);
    Vector3 plane_normal = Vector3 (1.0f,0.0f,0.0f);
    float plane_distance = -1.0f;
    Vector3 light_position = Vector3(0.0f, 13.0f, -10.0f);
    //color light_color(1.0f,1.0f,1.0f,0.0f);
    Vector3 light_direction = (light_position - intersection_position);
    light_direction = light_direction >> light_direction;
    float cosine = plane_normal ^ light_direction;
    
    bool s = checkShadow(intersection_position);
    //not in shadow
    if(s == false){
        //Not in shadow
        //Draw the plane's normal color
        final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
    
    }
    else{
        //if the sphere is in shadow, make the phane like under shadow (plane color with transparency)
        final_color = tile ((int)intersection_position.x, (int)intersection_position.z);
        final_color = final_color.color_scalar(0.3);
    }

    return final_color.clip();
}

//This function will combine light color. sphere color, 
//And add the reflection from floor to sphere color
color get_color_at(Vector3 intersection_position, Vector3 intersection_ray_direction, float accuracy, float ambientlight){
    
    color sphere_color (0.0f, 0.0f,0.0f,0.3f);
    color final_color = sphere_color.color_scalar(ambientlight);
    
    Vector3 sphere_centre = Vector3(0.0f,0.0f,0.0f);
    Vector3 sphere_normal  = (intersection_position + sphere_centre) >> (intersection_position + sphere_centre);
    Vector3 light_position = Vector3(0.0f, 15.0f, -10.0f);
    color light_color(0.6f,0.6f,0.6f,0.0f);//white
    Vector3 light_direction = (light_position - intersection_position);
    light_direction = light_direction >> light_direction;
  
    // Add light color to sphere 
    float cosine = sphere_normal ^ light_direction;
    bool t = checkShadow(intersection_position);
    final_color = final_color.color_add((light_color.color_scalar(cosine)));
    
    //phong illumination
    // Add diffuse_color to final color
    color diffuse_color = diffuse (light_direction, sphere_normal,intersection_ray_direction);
    final_color = final_color.color_add(diffuse_color);

    // Add specular to final_color
    float specular_value = specular(light_direction, sphere_normal,intersection_ray_direction);
    final_color = final_color.color_add(final_color.color_scalar(specular_value)); 

    // Generate reflection
    color tmp = reflection(sphere_normal,intersection_ray_direction,intersection_position,ambientlight);
    final_color = final_color.color_add(tmp);

    // Refraction:
    //color tmp1 = refraction(sphere_normal, light_direction, intersection_position);
    //final_color = final_color.color_add(tmp1);
    return final_color.clip();
}

//refraction vector
/*color refraction(Vector3 sphere_normal, Vector3 light_direction, Vector3 intersection_position){
    float n1 = 1.000293f;
    float n2 = 1.333;
    float n = n1/n2;
    float cosine = sphere_normal ^ light_direction;
    float sine = n*n * (1.0f - cosine*cosine);
    color refraction_color(0.0f,0.0f,0.0f,0.0f);
    if(sine < 1.0f){
        Vector3 refraction_vector = light_direction.multi(n) - sphere_normal.multi(n + sqrt(1.0-sine));
        float refraction_intersection = find_sphere_intersection(intersection_position, refraction_vector, Vector3(0.0f,0.0f,0.0f),1);
    
        if(refraction_intersection>0.0f){
            Vector3 refraction_intersection_position = intersection_position + (refraction_vector.multi(refraction_intersection));
            refraction_color = get_color_at(refraction_intersection_position, refraction_vector,0.000001,0.2);
        } 
    }
    

    return refraction_color;
    
}*/

color reflection(Vector3 sphere_normal, Vector3 intersection_ray_direction, Vector3 intersection_position, float ambientlight){
    Vector3 sphere_centre = Vector3(0.0f,0.0f,0.0f);
    float accuracy = 0.0000001;
    color sphere_color;
    if(pretty_blue == 1){
        sphere_color = color(0.0f, 1.0f,1.0f,0.0f);
    }else{
        sphere_color = color(1.0f, 0.0f, 1.0f,0.0f);
    }
    color final_color = sphere_color.color_scalar(ambientlight);

    //calculate reflection direction
    float dot1= sphere_normal ^ (intersection_ray_direction.multi(-1));
    Vector3 scalar1 = sphere_normal.multi(dot1);
    Vector3 add1 = scalar1 + intersection_ray_direction;
    Vector3 scalar2 = add1.multi(2);
    Vector3 add2 = intersection_ray_direction.multi(-1) + scalar2;
    Vector3 reflection_direction = add2 >> add2;

    //plug the reflection ray direction into find_plane_intersection
    //Try to find the intersection between reflection ray and plane
    float reflection_intersection = find_plane_intersection(intersection_position,reflection_direction,Vector3(0.0f,1.0f,0.0f),-1); 
    float _intersection = reflection_intersection;

    // if reflection_ray has intersection with floor, get the plane's color 
    if(reflection_intersection >0.0f){
        if(reflection_intersection > accuracy){
            Vector3 reflection_intersection_position = intersection_position + (reflection_direction.multi(_intersection));
            Vector3 reflection_ray_direction = reflection_direction;
            color reflection_intersection_color = get_plane_at(reflection_intersection_position,reflection_ray_direction,accuracy,ambientlight);
            final_color = final_color.color_add(reflection_intersection_color.color_scalar(0.21));
        }
    }

    return final_color;
}

// calculate the tile color for plane
color tile (int intersection_x, int intersection_z){
    int square = intersection_x + intersection_z;
    color result (0.0, 0.0,0.0,0.0);
    //set a blue tile
    if(square % 2==0){
        result.set_color_red(0.3f);
        result.set_color_green(0.3f);
        result.set_color_blue(0.3f);
    //set a white tile
    }else{
        result.set_color_red(1.0f);
        result.set_color_green(1.0f);
        result.set_color_blue(1.0f);
    }
    return result;
}

//This function will check the shadow of the sphere 
bool checkShadow(Vector3 intersection_position){
    Vector3 sphere_centre = Vector3(0.0f,0.0f,0.0f);
    Vector3 sphere_normal  = (intersection_position + sphere_centre) >> (intersection_position + sphere_centre);
    //Vector3 light_position = Vector3(7.0f, -10.0f, 10.0f);
    Vector3 light_position = Vector3(0.0f, -13.0f, 10.0f);
    Vector3 light_direction = (light_position - intersection_position);
    light_direction = light_direction >> light_direction; // normalization

    bool shadow = false;
    float cosine = sphere_normal ^ light_direction;
    
    //check shadow
    if(cosine < 0){
        if(shadow_check==1){
            shadow = true;
        }else{
            ;
        }
        //do nothing is the cosine is < 0, unless want to do a spot light
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

//This function will find the intersection of plane
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

//This function will find the intersection of sphere
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
        return -1;
    }else{
        float d = sqrt(disc);
        float p1 = ((-1*b - d)/2);
        if(p1 > 0){
            //the first root is the smallest positive root
            return p1;
        }else{
            // the second root is the smallest positive root
            float p2 = ((d - b)/2);
            return p2;
        }
    }
}


//This function will write the image into bmp file.
//reference can be found in readmy.txt
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

int image;
int main(int argc, char *argv[]){
    char str[200];
    cout<<"Choose a scene please:"<<endl;
    cout<<"Enter 1 for Normal Scene!"<<endl;
    cout<<"Enter 2 for Spot Light Scene!"<<endl;
    cout<<"Enter 3 for Beautiful Blue Scene!"<<endl;
    scanf("%s",str);
    if(strncmp(str,"1",1) == 0){
        shadow_check = 0;
    }
    else if(strncmp(str,"2",1) == 0){
        shadow_check = 1;
    }
    else if(strncmp(str,"3",1) == 0){
        pretty_blue = 1;
        shadow_check = 0; 
    }

    cout<<"Please wait, Anti-aliasing takes a 20 seconds..."<<endl;

    int dpi = 72;
    int width = 800;
    int height = 900;
    int n = width * height;
    float ambientlight = 0.2;
    float accuracy = 0.000001;
    float ratio = (float)width/(float)height; //aspect_ratio
    RGBType *pixels = new RGBType[n];
    int depth = 6;
    float threshold = 0.1f;

    Vector3 y = Vector3(0.0f, 1.0f, 0.0f);

    Vector3 look_at = Vector3(0.0f, 0.0f, 0.0f);//cam is looking at 0, 0, 0
    Vector3 cam_position = Vector3(3, 1.5, -4);
    //Vector3 cam_position = Vector3(6.0, 0.5, -5.0);
    Vector3 diff =  Vector3(-1*(cam_position.x - look_at.x),-1*(cam_position.y - look_at.y),-1*(cam_position.z - look_at.z));
    Vector3 cam_dir = diff >> diff; // normalize diff, operator overloading
    Vector3 cam_right = (y & cam_dir) >> (y & cam_dir); // normalize the cross production of y and cam_dir
    Vector3 cam_down = cam_right & cam_dir; //cross product between cam_right and cam_dir
    
    //Vector3 light_position = Vector3(-7.0f, 10.0f, -10.0f);
 
    Vector3 o = Vector3(0.0f, 0.0f, 0.0f); 

    int tmp_image;
    float red,green,blue;
    float x_tmp; float y_tmp;
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
   
            image = y * width + x;
            float red[depth*depth];
            float green[depth*depth];
            float blue[depth*depth]; 
            for(int i=0; i<depth; i++){
                for(int j=0; j<depth; j++){
                    tmp_image = j*depth + i; 
                    x_tmp = (x + (float)i/((float)depth-1)) / width;
                    y_tmp = (((height-y) + (float)i/((float)depth - 1)   )/height)/ratio - (((height-width)/(float)width)/2);
             
                    //setting camera position and direstion 
                    Vector3 cam_ray_pos = cam_position;
            
                    Vector3 tmp = Vector3(0.0f,0.0f,0.0f);
                    if(strncmp(str,"3",1) == 0){
                        tmp = (cam_dir + (cam_right.multi(x_tmp - 0.5f) + cam_down.multi(y_tmp - 0.5f)));
                    }else{
                        tmp = (cam_dir + (cam_right.multi(x_tmp - 0.65f) + cam_down.multi(y_tmp - 0.65f)));
                    }
                    Vector3 cam_ray_direction = tmp >> tmp;
             
                    //ray cam_ray  is (cam_ray_pos, cam_ray_direction);
                    //Calculate intersection btw ray and sphere, plane and ray
                    float sphere_intersection = find_sphere_intersection(cam_ray_pos, cam_ray_direction, o, 1);
                    float plane_intersection = find_plane_intersection(cam_ray_pos, cam_ray_direction, y, -1);

                    // Check if we find a sphere or not, it is not, draw the plane otherwise, draw sphere
                    if(sphere_intersection == -1.0f){
                        if(plane_intersection == -1.0f ){
                            red[tmp_image] = 0.0f;
                            green[tmp_image] = 0.0f;
                            blue[tmp_image] = 0.0f;
                        }else{
                            //calulate the point that has intersection between ray and plane and its direction 
                            Vector3 intersection_position = cam_ray_pos + (cam_ray_direction.multi(plane_intersection));
                            Vector3 intersection_ray_direction = cam_ray_direction;
                            color final_plane=get_plane_at(intersection_position,intersection_ray_direction,accuracy,ambientlight);
                                //if the ray miss the plane, draw black else draw the plane's color
                                if (plane_intersection <= 1 ){
                                    red[tmp_image] = 0.0f;
                                    green[tmp_image] = 0.0f;
                                    blue[tmp_image] = 0.0f;
                                }else{
                                        red[tmp_image] = final_plane.get_color_red();
                                        green[tmp_image] = final_plane.get_color_green();
                                        blue[tmp_image] = final_plane.get_color_blue();
                                }
                        }
                    }else{
                        if(sphere_intersection > accuracy){
                            //calulate the point that has intersection between ray and sphere and its direction 
                            Vector3 intersection_position = cam_ray_pos + (cam_ray_direction.multi(sphere_intersection));
                            Vector3 intersection_ray_direction = cam_ray_direction;
                            //calculate final color of our sphere 
                            color intersection_color = get_color_at(intersection_position, intersection_ray_direction,0.0f,ambientlight);
                            red[tmp_image]=intersection_color.get_color_red();
                            green[tmp_image]=intersection_color.get_color_green();
                            blue[tmp_image]=intersection_color.get_color_blue();
                        }
                    }
                }
            }



        //anti-aliasing, add up and average the color; it will take longer
        float total_red = 0.0f;
        float total_green = 0.0f;
        float total_blue = 0.0f;
        
        float average_red,average_green,average_blue;
        for(int ii=0; ii< depth*depth; ii++){
            total_red = total_red + red[ii];
        }

        for(int jj=0; jj< depth*depth; jj++){
            total_green = total_green + green[jj];
        }

        for(int kk=0; kk< depth*depth; kk++){
            total_blue = total_blue + blue[kk];
        }

        average_red = total_red/(depth*depth);
        average_green = total_green/(depth*depth);
        average_blue = total_blue/(depth*depth);


        pixels[image].r = average_red;
        pixels[image].g = average_green;
        pixels[image].b = average_blue;

        }
    }
    char *filename = (char*)malloc(sizeof(char)*13);
    strncpy(filename,"sphere_",7);
    strncat(filename,str,1);
    strncat(filename,".bmp",4);
    savebmp(filename, width, height, dpi, pixels);
    cout<<"Done!"<<endl;
    return 0;
}
