#ifndef _COLOR_H
#define _COLOR_H

class color{
    float red, green, blue, special;
    public:
    
    color();
    color(float, float, float, float);
       
    float get_color_red(){return red;}
    float get_color_green(){return green;}
    float get_color_blue(){return blue;}
    float get_color_special(){return special;}

    float set_color_red(float the_red){red = the_red;}
    float set_color_green(float the_green){green = the_green;}
    float set_color_blue(float the_blue){blue = the_blue;}
    float set_color_speical(float the_special){special = the_special;}

    color color_scalar (float scalar){
        return color (red*scalar, green*scalar, blue*scalar, special);
    }
    color color_add(color _color){
        return color(red + _color.get_color_red(), green + _color.get_color_green(), blue + _color.get_color_blue(), special);
    }
    color color_multi(color _color){
        return color(red * _color.get_color_red(), green * _color.get_color_green(), blue * _color.get_color_blue(), special);
    }
    
    color clip(){
        float alllight = red + green + blue;
        float excesslight = alllight - 1;
        if (excesslight > 0.0f){
            red = red + excesslight*(red/alllight);
            green = green + excesslight*(green/alllight);
            blue = blue + excesslight*(blue/alllight);
        }
        if (red > 1){red = 1;}
        if (green > 1){green = 1;}
        if (blue > 1){blue = 1;}
        if (red < 0){red = 0;}
        if (green < 0){green = 0;}
        if (blue < 0){blue = 0;}

        return color(red, green,blue,special);
        
    } 
};

color::color(){
    red = 0.5;
    green = 0.5;
    blue = 0.5;
}

color::color(float r, float g, float b, float s){
    red = r;
    green = g;
    blue = b;
    special = s;
}

#endif


