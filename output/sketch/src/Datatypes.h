#ifndef DATATYPES_H
#define DATATYPES_H

#include <Arduino.h>

class Vec2
{
public:
    float mX;
    float mY;

    Vec2(){};
    Vec2(float pos);
    Vec2(float x, float y);
    float magnitude();

    Vec2 operator+=(Vec2 input);
    Vec2 operator/(float input);
    Vec2 operator/(Vec2 input);
    Vec2 operator-(Vec2 input);
    bool operator==(Vec2 input);
    bool operator!=(Vec2 input);

    String toString();
};

class Vec3
{
public:
    float mX = 0;
    float mY = 0;
    float mZ = 0;

    Vec3() {};
    Vec3(float x, float y, float z);
    float magnitude();    
    Vec3 operator + (Vec3 input);        
    Vec3 operator + (float input);
    Vec3 operator - (Vec3 input);
    Vec3 operator-();
    Vec3 operator * (float input);
    void operator -= (Vec3 input);
    void operator += (Vec3 input);
    void operator = (Vec3 input);
    String toString();
};

class Vec4
{
public:
    float mX;
    float mY;
    float mZ;
    float mW;

    Vec4(){};
    Vec4(Vec3 vec, float w);
    Vec4(float x, float y, float z, float w);

    operator Vec3() const;
};

class Mat4
{    
public:
    Mat4();
    void set(float val11, float val12, float val13, float val14, float val21, float val22, float val23, float val24, float val31, float val32, float val33, float val34, float val41, float val42, float val43, float val44);
    void set(float val);
    void set(Mat4 mat);
    Vec4 multiply(const Vec4 &vec);
    Mat4 multiply(const Mat4 &matB);
    Mat4 translate(const Vec3 &translation);
    Mat4 rotate(float rad, const Vec3 &axis);
    Mat4 rotate(const Vec3 &eulerAngles);
    Mat4 inverse();
    Vec3 getPos();
    String toString();    

    //Matrix[Row][Col]
    float mMatrix[4][4];
};

#endif