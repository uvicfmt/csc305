#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
#include <iostream>

/**
 *  @todo assignment two
 *  1. extend these matrix classes to support all the basic linear algebra functions
 *  (add, subtract, multiply)
 *  2. add convenience functions to create scale & rotation matrices around the available axes,
 *  and a translation matrix
 *  3. add functions to create the projection matrix versions.
 *  for perspective projection, this function should take the field of view, image ratio, near plane and far plane distance
 *  for orthographic projection it should take the left, right, top, bottom, near plane and far plane values
 *  4. add functions to create the view matrix using eye position, at position and the up vector
 */

/**
 *	@class	Matrix3x3
 *	@brief	3 by 3 Matrix class
 *	Homogenous 3x3 Matrix, onedimensional array (like opengl), column major
 *	|0 3 6|
 *	|1 4 7|
 *	|2 5 8|
 */
class Matrix3x3
{
public:

    float elements[9];/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix3x3();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();
    Matrix3x3 operator+(Matrix3x3);//matrix 3x3 addition
    Matrix3x3 operator-(Matrix3x3);//matrix 3x3 substraction
    Matrix3x3 operator*(Matrix3x3);//matrix 3x3 multiplication

    //prototypes for scale matrix xyz
    Matrix3x3 scaleXmatirx(float factor);
    Matrix3x3 scaleYmatirx(float factor);
    Matrix3x3 scaleZmatirx(float factor);

    //prototypes for translation matrix xyz
    Matrix3x3 translationMatirx(Vector3 translation);

    //prototypes for rotation matrix xyz
    Matrix3x3 rotationXmatrix(float factor);
    Matrix3x3 rotationYmatrix(float factor);
    Matrix3x3 rotationZmatrix(float factor);


};

/**
 *	@class	Matrix4x4
 *	@brief	4 by 4 matrix
 *	Homogenous 4x4 Matrix, onedimensional array (like opengl), column major
 *	|0 4 8  12|
 *	|1 5 9  13|
 *	|2 6 10 14|
 *	|3 7 11 15|
 */
class Matrix4x4
{
public:

    float elements[16];	/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix4x4();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();
    Matrix3x3 convert(Matrix4x4);//convert matrix 4x4 to matrix 3x3
    Matrix4x4 operator+(Matrix4x4);//matrix addition
    Matrix4x4 operator-(Matrix4x4);//substraction matrix
    Matrix4x4 operator*(Matrix4x4);//Multiply matrix by matrix
    Matrix4x4 operator*(float factor);//Multiply matrix by a scaler

    //prototypes for scale matrix xyz
    Matrix4x4 scaleXmatirx(float factor);
    Matrix4x4 scaleYmatirx(float factor);
    Matrix4x4 scaleZmatirx(float factor);
    Matrix4x4 scaleMatrix(float X, float Y, float Z);

    //prototypes for translation matrix xyz
    Matrix4x4 translationMatirx(Vector3 translation);
    Matrix4x4 zeroMatrix();

    //prototypes for rotation matrix xyz
    Matrix4x4 rotationXmatrix(float factor);
    Matrix4x4 rotationYmatrix(float factor);
    Matrix4x4 rotationZmatrix(float factor);

    Matrix4x4 orthographicMatrix(Vector3 viewNear, Vector3 viewFar);//prototype for orthographic matrix
    Matrix4x4 perspectiveMatrix(float fov, float aspectRatio, float n, float f);//prototype for perspective matrix
    Matrix4x4 viewMatrix(Vector3 eyep, Vector3 atp, Vector3 upv); //prototype for view matrix

    Matrix4x4 inverse(Matrix4x4 m);//prototype for inverse
    Matrix4x4 transpose(Matrix4x4 tran);//transpose
};

#endif // MATRIX_H
