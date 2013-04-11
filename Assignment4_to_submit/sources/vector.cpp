#include "vector.h"
#include <math.h>

Vector3::Vector3(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z)
{
}

//dot product operator overloadin
float Vector3 :: operator^(Vector3 dotProduct){
    float result=0.0f;

    result = x*dotProduct.x+y*dotProduct.y+z*dotProduct.z;

    return result;
}

//cross product operator overloading
Vector3 Vector3 :: operator&(Vector3 crossProduct){
    Vector3 result;

    result.elements[0] = y*crossProduct.elements[2]-z*crossProduct.elements[1];
    result.elements[1] = z*crossProduct.elements[0]-x*crossProduct.elements[2];
    result.elements[2] = x*crossProduct.elements[1]-y*crossProduct.elements[0];

    return result;
}

//Addition operator overloading for Vector4
Vector3 Vector3 :: operator+(Vector3 addition){
    Vector3 result;
    result.elements[0] = x + addition.elements[0];
    result.elements[1] = y + addition.elements[1];
    result.elements[2] = z + addition.elements[2];
    return result;
}

//Substraction operator overloading for Vector4
Vector3 Vector3 :: operator-(Vector3 sub){
    Vector3 result;
    result.elements[0] = x - sub.elements[0];
    result.elements[1] = y - sub.elements[1];
    result.elements[2] = z - sub.elements[2];
    return result;
}

//Multiplication operator overloading for Vector4
Vector3 Vector3 :: operator*(Vector3 multi){
    Vector3 result;
    result.elements[0] = x * multi.elements[0];
    result.elements[1] = y * multi.elements[1];
    result.elements[2] = z * multi.elements[2];
    return result;
}

//Magnitude operator overloading for Vector4
float Vector3 :: operator%(Vector3 mag){
    float result=0.0f;

    result = sqrt(mag.x*mag.x + mag.y*mag.y + mag.z*mag.z);

    return result;
}

//Normalize operator overloading for Vector4
Vector3 Vector3 :: operator>>(Vector3 norm){
   Vector3 result;
   float tmp=0.0f;

   tmp = sqrt(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z);

   result.elements[0] = norm.x/tmp;
   result.elements[1] = norm.y/tmp;
   result.elements[2] = norm.z/tmp;

   return result;
}

Vector3 Vector3 :: negative(Vector3 nega){
    Vector3 result = Vector3(-1*nega.x, -1*nega.y, -1*nega.z);
    return result;
}

Vector3 Vector3 :: multi(float scaler){
    return Vector3(x*scaler, y*scaler, z*scaler);

}


/*Vector3 Vector3 :: operator*(float scale){
    Vector3 result;
    result = (x*scale, y*scale, z*scale);
    return result;
}*/
/*************************************************/
/**********************Vector 4*******************/
/*************************************************/

Vector4::Vector4(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/, float m_w/* = 1.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z),
      w(m_w)
{

}

//dot product operator overloadin
float Vector4 :: operator^(Vector4 dotProduct){
    float result=0.0f;

    result = x*dotProduct.x + y*dotProduct.y + z*dotProduct.z + w*dotProduct.w;

    return result;
}

//convert
Vector3 Vector4 :: convert(void){

    Vector3 vector3d(x,y,z);

    return vector3d;
}

//Addition operator overloading for Vector4
Vector4 Vector4 :: operator+(Vector4 addition){
    Vector4 result;
    result.elements[0] = x + addition.elements[0];
    result.elements[1] = y + addition.elements[1];
    result.elements[2] = z + addition.elements[2];
    result.elements[3] = w + addition.elements[3];
    return result;
}

//Substraction operator overloading for Vector4
Vector4 Vector4 :: operator-(Vector4 sub){
    Vector4 result;
    result.elements[0] = x - sub.elements[0];
    result.elements[1] = y - sub.elements[1];
    result.elements[2] = z - sub.elements[2];
    result.elements[3] = w - sub.elements[3];
    return result;
}

//Multiplication operator overloading for Vector4
Vector4 Vector4 :: operator*(Vector4 multi){
    Vector4 result;
    result.elements[0] = x * multi.elements[0];
    result.elements[1] = y * multi.elements[1];
    result.elements[2] = z * multi.elements[2];
    result.elements[3] = w * multi.elements[3];
    return result;
}

//Magnitude operator overloading for Vector4
float Vector4 :: operator%(Vector4 mag){
    float result=0.0f;

    result = sqrt(mag.x*mag.x + mag.y*mag.y + mag.z*mag.z + mag.w*mag.w);

    return result;
}

//Normalize operator overloading for Vector4
Vector4 Vector4 :: operator>>(Vector4 norm){
   Vector4 result;
   float tmp=0.0f;

   tmp = sqrt(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z + norm.w*norm.w);

   result.elements[0] = norm.x/tmp;
   result.elements[1] = norm.y/tmp;
   result.elements[2] = norm.z/tmp;
   result.elements[3] = norm.w/tmp;

   return result;
}



