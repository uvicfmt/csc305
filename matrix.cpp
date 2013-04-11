#include "matrix.h"
#include <math.h>

#define pi 3.1415926535897932384626433832795028841971693993751058

Matrix3x3::Matrix3x3()
{
    this->loadIdentity();
}

void Matrix3x3::loadIdentity()
{
    elements[0] = elements[4] = elements[8] = 1;
    elements[1] = elements[2] = elements[3] = elements[5] = elements[6] = elements[7] = 0;
}

//Overloading operator + for Matrix3x3
Matrix3x3 Matrix3x3::operator+(Matrix3x3 summand){
    Matrix3x3 result;
    for(int i=0;i<9;i++){
        result.elements[i] = elements[i]+summand.elements[i];
    }
    return result;
}

//Overloading operator * for Matrix3x3
Matrix3x3 Matrix3x3::operator*(Matrix3x3 multiplicand){
    Matrix3x3 result;
    float tmp[3];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                tmp[k]=elements[3*k+j]* multiplicand.elements[3*i+k];
                if(k==2){
                    result.elements[3*i+j]=tmp[0]+tmp[1]+tmp[2];
                }
            }
        }
    }
    return result;
}

//Overloading operator - for Matrix3x3
Matrix3x3 Matrix3x3::operator-(Matrix3x3 minuend){
    Matrix3x3 result;
    for(int i=0;i<9;i++){
        result.elements[i] = elements[i]-minuend.elements[i];
    }
    return result;
}

//scale matrix x for 2D
Matrix3x3 Matrix3x3 :: scaleXmatirx(float factor){
    Matrix3x3 tmp;
    tmp.elements[0] = factor;
    return tmp;
}

//scale matrix y for 2D
Matrix3x3 Matrix3x3 :: scaleYmatirx(float factor){
    Matrix3x3 tmp;
    tmp.elements[4] = factor;
    return tmp;
}

//scale matrix z for 2D
Matrix3x3 Matrix3x3 :: scaleZmatirx(float factor){
    Matrix3x3 tmp;
    tmp.elements[8] = factor;
    return tmp;
}

//translation matrix for 2D
Matrix3x3 Matrix3x3 :: translationMatirx(Vector3 translation){

    elements[6] = translation.x;
    elements[7] = translation.y;
    elements[8] = translation.z;

    return *this;
}


//Rotation Matrix X for 2D
Matrix3x3 Matrix3x3 ::rotationXmatrix(float factor){
    Matrix3x3 tmp;
    tmp.elements[4]=cos(factor);
    tmp.elements[5]=sin(factor);
    tmp.elements[7]=-sin(factor);
    tmp.elements[8]=cos(factor);

    return tmp;
}


//Rotation Matrix Y for 2D
Matrix3x3 Matrix3x3 ::rotationYmatrix(float factor){
    Matrix3x3 tmp;
    tmp.elements[0]=cos(factor);
    tmp.elements[2]=-sin(factor);
    tmp.elements[6]=sin(factor);
    tmp.elements[8]=cos(factor);

    return tmp;
}



//Rotation Matrix Z for 2D
Matrix3x3 Matrix3x3 ::rotationZmatrix(float factor){
    Matrix3x3 tmp;
    tmp.elements[0]=cos(factor);
    tmp.elements[1]=sin(factor);
    tmp.elements[3]=-sin(factor);
    tmp.elements[4]=cos(factor);

    return tmp;
}

/*************************************************************/


Matrix4x4::Matrix4x4()
{
    loadIdentity();
}

void Matrix4x4::loadIdentity()
{
    elements[0] = elements[5] = elements[10] = elements[15] = 1;
    elements[1] = elements[2] = elements[3] = elements[4] = elements[6] = elements[7]
    = elements[8] = elements[9] = elements[11] = elements[12] = elements[13] = elements[14] = 0;
}

//Overloading operator + for Matrix4x4
Matrix4x4 Matrix4x4::operator+(Matrix4x4 summand){
    Matrix4x4 result;
    for(int i=0;i<16;i++){
        result.elements[i] = elements[i] + summand.elements[i];
    }
    return result;
}


//Overloading operator * for Matrix4x4
Matrix4x4 Matrix4x4::operator*(Matrix4x4 multiplicand){
    Matrix4x4 result;
    float tmp[4];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                tmp[k]=elements[4*k+j]* multiplicand.elements[4*i+k];
                if(k==3){
                    result.elements[4*i+j] = tmp[0] + tmp[1] + tmp[2] + tmp[3];
                }
            }
        }
    }
    return result;
}


//Overloading operator - for Matrix4x4
Matrix4x4 Matrix4x4::operator-(Matrix4x4 minuend){
    Matrix4x4 result;
    for(int i=0;i<16;i++){
        result.elements[i] = elements[i]-minuend.elements[i];
    }
    return result;
}

//Convert a Matrix4x4 into a Matrix3x3
Matrix3x3 Matrix4x4 :: convert(Matrix4x4 original){

    Matrix3x3 m3d;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            m3d.elements[3*i+j]=original.elements[4*i+j];
        }
    }

    return m3d;
}

//scale matrix for x y and z
Matrix4x4 Matrix4x4 :: scaleMatrix(float X, float Y, float Z){
    Matrix4x4 result;
    result.elements[0] = X;
    result.elements[5] = Y;
    result.elements[10] = Z;
    return result;
}



//scale matrix x for 3D
Matrix4x4 Matrix4x4 :: scaleXmatirx(float factor){
    Matrix4x4 tmp;
    tmp.elements[0] = factor;
    return tmp;
}

//scale matrix y for 3D
Matrix4x4 Matrix4x4 :: scaleYmatirx(float factor){
    Matrix4x4 tmp;
    tmp.elements[5] = factor;
    return tmp;
}

//scale matrix z for 3D
Matrix4x4 Matrix4x4 :: scaleZmatirx(float factor){
    Matrix4x4 tmp;
    tmp.elements[10] = factor;
    return tmp;
}

//Translation matrix for 3D
Matrix4x4 Matrix4x4 :: translationMatirx(Vector3 translation){

    elements[12] = translation.x;
    elements[13] = translation.y;
    elements[14] = translation.z;
    return *this;
}

Matrix4x4 Matrix4x4::zeroMatrix()
{
    for(int i = 0; i < 16; i++)
        elements[i] = 0.0f;
    return *this;
}


//Rotation matrix for 3D x axis
Matrix4x4 Matrix4x4 ::rotationXmatrix(float factor){
    //Matrix4x4 tmp;
    elements[5]=cos(factor);
    elements[6]=sin(factor);
    elements[9]=-sin(factor);
    elements[10]=cos(factor);

    return *this;
}

//Rotation matrix for 3D y axis
Matrix4x4 Matrix4x4 ::rotationYmatrix(float factor){
    //Matrix4x4 tmp;
    elements[0]=cos(factor);
    elements[2]=-sin(factor);
    elements[8]=sin(factor);
    elements[10]=cos(factor);
    //tranfor * scale *  rotate
    return *this;
}


//Rotation matrix for 3D z axis
Matrix4x4 Matrix4x4 ::rotationZmatrix(float factor){
    Matrix4x4 tmp;
    elements[0]=cos(factor);
    elements[1]=sin(factor);
    elements[4]=-sin(factor);
    elements[5]=cos(factor);

    return *this;
}

Matrix4x4 Matrix4x4 :: operator*(float factor){
    Matrix4x4 tmp;
    for(int i = 0; i < 16; i++){
        tmp.elements[i] = elements[i] * factor;
    }
    return tmp;
}

//function for creating orthographic matrix
Matrix4x4 Matrix4x4 :: orthographicMatrix(Vector3 canonicalA, Vector3 canonicalB){

        elements[0] = 2.0f / (canonicalB.x - canonicalA.x);
        elements[5] = 2.0f / (canonicalB.y - canonicalA.y);
        elements[10] = 2.0f / (canonicalA.z - canonicalB.z);
        elements[12] = -(canonicalA.x + canonicalB.x) / (canonicalB.x - canonicalA.x);
        elements[13] = -(canonicalA.y + canonicalB.y) / (canonicalB.y - canonicalA.y);
        elements[14] = -(canonicalA.z + canonicalB.z) / (canonicalA.z - canonicalB.z);

        return *this;

}

//function for creating perspective matrix
Matrix4x4 Matrix4x4 :: perspectiveMatrix(float fov, float aspectRatio, float n, float f){
    //Matrix4x4 pers;
    float t = tan(0.5f*fov*pi/180.0f);
    float r = aspectRatio * t;

    elements[0] = 1.0f/r;
    elements[5] = 1.0f/t;
    elements[10] = ( (-1.0f) * ( f + n ) ) / (f-n);
    elements[11] = -1.0f;
    elements[14] = ( (-2.0f) * f * n) / (f - n);
    elements[15] = 0.0f;

    return *this;
}

//function for creating view matrix
//create the view matrix using eye position, at position and the up vector
Matrix4x4 Matrix4x4 :: viewMatrix(Vector3 eyePos,  Vector3 lookAtPos, Vector3 upVec){

        Vector3 Vw = (eyePos - lookAtPos) >> (eyePos - lookAtPos);
        Vector3 Vu = (upVec & Vw) >> (upVec & Vw);
        Vector3 Vv = Vw & Vu;

        Matrix4x4 viewMatrix;

        viewMatrix.elements[0] = Vu.x;
        viewMatrix.elements[4] = Vu.y;
        viewMatrix.elements[8] = Vu.z;

        viewMatrix.elements[1] = Vv.x;
        viewMatrix.elements[5] = Vv.y;
        viewMatrix.elements[9] = Vv.z;

        viewMatrix.elements[2] = Vw.x;
        viewMatrix.elements[6] = Vw.y;
        viewMatrix.elements[10] = Vw.z;

        viewMatrix.elements[12] = -1.0f * eyePos.x;
        viewMatrix.elements[13] = -1.0f * eyePos.y;
        viewMatrix.elements[14] = -1.0f * eyePos.z;

        for(int pos = 0; pos < 16; pos ++)
        {
            elements[pos] = viewMatrix.elements[pos];
        }
        return *this;
}

//function for transpose matrix
Matrix4x4 Matrix4x4 :: transpose(Matrix4x4 tran){

    elements[0] = tran.elements[0];
    elements[1] = tran.elements[4];
    elements[2] = tran.elements[8];
    elements[3] = tran.elements[12];
    elements[4] = tran.elements[1];
    elements[5] = tran.elements[5];
    elements[6] = tran.elements[9];
    elements[7] = tran.elements[13];
    elements[8] = tran.elements[2];
    elements[9] = tran.elements[6];
    elements[10] = tran.elements[10];
    elements[11] = tran.elements[14];
    elements[12] = tran.elements[3];
    elements[13] = tran.elements[7];
    elements[14] = tran.elements[11];
    elements[15] = tran.elements[15];

    return *this;
}

//function for inverse a matrix
Matrix4x4 Matrix4x4 :: inverse(Matrix4x4 m){
    Matrix4x4 inv;

    inv.elements[0] = m.elements[5]  * m.elements[10] * m.elements[15] -
             m.elements[5]  * m.elements[11] * m.elements[14] -
             m.elements[9]  * m.elements[6]  * m.elements[15] +
             m.elements[9]  * m.elements[7]  * m.elements[14] +
             m.elements[13] * m.elements[6]  * m.elements[11] -
             m.elements[13] * m.elements[7]  * m.elements[10];



    inv.elements[4] = -m.elements[4]  * m.elements[10] * m.elements[15] +
              m.elements[4]  * m.elements[11] * m.elements[14] +
              m.elements[8]  * m.elements[6]  * m.elements[15] -
              m.elements[8]  * m.elements[7]  * m.elements[14] -
              m.elements[12] * m.elements[6]  * m.elements[11] +
              m.elements[12] * m.elements[7]  * m.elements[10];

    inv.elements[8] = m.elements[4]  * m.elements[9] * m.elements[15] -
             m.elements[4]  * m.elements[11] * m.elements[13] -
             m.elements[8]  * m.elements[5] * m.elements[15] +
             m.elements[8]  * m.elements[7] * m.elements[13] +
             m.elements[12] * m.elements[5] * m.elements[11] -
             m.elements[12] * m.elements[7] * m.elements[9];

    inv.elements[12] = -m.elements[4]  * m.elements[9] * m.elements[14] +
               m.elements[4]  * m.elements[10] * m.elements[13] +
               m.elements[8]  * m.elements[5] * m.elements[14] -
               m.elements[8]  * m.elements[6] * m.elements[13] -
               m.elements[12] * m.elements[5] * m.elements[10] +
               m.elements[12] * m.elements[6] * m.elements[9];

    inv.elements[1] = -m.elements[1]  * m.elements[10] * m.elements[15] +
              m.elements[1]  * m.elements[11] * m.elements[14] +
              m.elements[9]  * m.elements[2] * m.elements[15] -
              m.elements[9]  * m.elements[3] * m.elements[14] -
              m.elements[13] * m.elements[2] * m.elements[11] +
              m.elements[13] * m.elements[3] * m.elements[10];

    inv.elements[5] = m.elements[0]  * m.elements[10] * m.elements[15] -
             m.elements[0]  * m.elements[11] * m.elements[14] -
             m.elements[8]  * m.elements[2] * m.elements[15] +
             m.elements[8]  * m.elements[3] * m.elements[14] +
             m.elements[12] * m.elements[2] * m.elements[11] -
             m.elements[12] * m.elements[3] * m.elements[10];

    inv.elements[9] = -m.elements[0]  * m.elements[9] * m.elements[15] +
              m.elements[0]  * m.elements[11] * m.elements[13] +
              m.elements[8]  * m.elements[1] * m.elements[15] -
              m.elements[8]  * m.elements[3] * m.elements[13] -
              m.elements[12] * m.elements[1] * m.elements[11] +
              m.elements[12] * m.elements[3] * m.elements[9];

    inv.elements[13] = m.elements[0]  * m.elements[9] * m.elements[14] -
              m.elements[0]  * m.elements[10] * m.elements[13] -
              m.elements[8]  * m.elements[1] * m.elements[14] +
              m.elements[8]  * m.elements[2] * m.elements[13] +
              m.elements[12] * m.elements[1] * m.elements[10] -
              m.elements[12] * m.elements[2] * m.elements[9];

    inv.elements[2] = m.elements[1]  * m.elements[6] * m.elements[15] -
             m.elements[1]  * m.elements[7] * m.elements[14] -
             m.elements[5]  * m.elements[2] * m.elements[15] +
             m.elements[5]  * m.elements[3] * m.elements[14] +
             m.elements[13] * m.elements[2] * m.elements[7] -
             m.elements[13] * m.elements[3] * m.elements[6];

    inv.elements[6] = -m.elements[0]  * m.elements[6] * m.elements[15] +
              m.elements[0]  * m.elements[7] * m.elements[14] +
              m.elements[4]  * m.elements[2] * m.elements[15] -
              m.elements[4]  * m.elements[3] * m.elements[14] -
              m.elements[12] * m.elements[2] * m.elements[7] +
              m.elements[12] * m.elements[3] * m.elements[6];

    inv.elements[10] = m.elements[0]  * m.elements[5] * m.elements[15] -
              m.elements[0]  * m.elements[7] * m.elements[13] -
              m.elements[4]  * m.elements[1] * m.elements[15] +
              m.elements[4]  * m.elements[3] * m.elements[13] +
              m.elements[12] * m.elements[1] * m.elements[7] -
              m.elements[12] * m.elements[3] * m.elements[5];

    inv.elements[14] = -m.elements[0]  * m.elements[5] * m.elements[14] +
               m.elements[0]  * m.elements[6] * m.elements[13] +
               m.elements[4]  * m.elements[1] * m.elements[14] -
               m.elements[4]  * m.elements[2] * m.elements[13] -
               m.elements[12] * m.elements[1] * m.elements[6] +
               m.elements[12] * m.elements[2] * m.elements[5];

    inv.elements[3] = -m.elements[1] * m.elements[6] * m.elements[11] +
              m.elements[1] * m.elements[7] * m.elements[10] +
              m.elements[5] * m.elements[2] * m.elements[11] -
              m.elements[5] * m.elements[3] * m.elements[10] -
              m.elements[9] * m.elements[2] * m.elements[7] +
              m.elements[9] * m.elements[3] * m.elements[6];

    inv.elements[7] = m.elements[0] * m.elements[6] * m.elements[11] -
             m.elements[0] * m.elements[7] * m.elements[10] -
             m.elements[4] * m.elements[2] * m.elements[11] +
             m.elements[4] * m.elements[3] * m.elements[10] +
             m.elements[8] * m.elements[2] * m.elements[7] -
             m.elements[8] * m.elements[3] * m.elements[6];

    inv.elements[11] = -m.elements[0] * m.elements[5] * m.elements[11] +
               m.elements[0] * m.elements[7] * m.elements[9] +
               m.elements[4] * m.elements[1] * m.elements[11] -
               m.elements[4] * m.elements[3] * m.elements[9] -
               m.elements[8] * m.elements[1] * m.elements[7] +
               m.elements[8] * m.elements[3] * m.elements[5];

    inv.elements[15] = m.elements[0] * m.elements[5] * m.elements[10] -
              m.elements[0] * m.elements[6] * m.elements[9] -
              m.elements[4] * m.elements[1] * m.elements[10] +
              m.elements[4] * m.elements[2] * m.elements[9] +
              m.elements[8] * m.elements[1] * m.elements[6] -
              m.elements[8] * m.elements[2] * m.elements[5];

    float det = m.elements[0] * inv.elements[0] + m.elements[1] * inv.elements[4] + m.elements[2] * inv.elements[8] + m.elements[3] * inv.elements[12];

    Matrix4x4 invertedM;

    det = 1.0f/det;

    if (det == 0)
        printf("det = 0 \n");

    for(int i=0;i<16;i++){
        invertedM.elements[i]=inv.elements[i]*det;
    }

    return invertedM;
}



