#include "Datatypes.h"
#include <math.h>

//=============================Vec2=============================
Vec2::Vec2(float x, float y)
{
    mX = x;
    mY = y;
}

float Vec2::magnitude()
{
    return sqrt(mX * mX + mY * mY);
}

Vec2 Vec2::operator+=(Vec2 input)
{
    return Vec2(mX + input.mX, mY + input.mY);
}

Vec2 Vec2::operator/(float input)
{
    return Vec2(mX/input, mY/input);
}

//=============================Vec3=============================
Vec3::Vec3(float x, float y, float z)
{
    mX = x;
    mY = y;
    mZ = z;
}

float Vec3::magnitude()
{
    return sqrt(mX * mX + mY * mY + mZ * mZ);
}

Vec3 Vec3::operator-(Vec3 input)
{
    return Vec3(mX - input.mX, mY - input.mY, mZ - input.mZ);
}

Vec3 Vec3::operator-()
{
    return Vec3(-mX, -mY, -mZ);
}

Vec3 Vec3::operator+(Vec3 input)
{
    return Vec3(mX + input.mX, mY + input.mY, mZ + input.mZ);
}

Vec3 Vec3::operator+(float input)
{
    return Vec3(mX + input, mY + input, mZ + input);
}

Vec3 Vec3::operator-=(Vec3 input)
{
    return *this - input;
}

Vec3 Vec3::operator+=(Vec3 input)
{
    return *this + input;
}

Vec3 Vec3::operator*(float input)
{
    return Vec3(mX * input, mY * input, mZ * input);
}

String Vec3::toString()
{
    return (String) mX + ", " + mY + ", " + mZ;
}

void Vec3::operator=(Vec3 input)
{
    mX = input.mX;
    mY = input.mY;
    mZ = input.mZ;
}

//=============================Vec4=============================
Vec4::Vec4(float x, float y, float z, float w)
{
    mX = x;
    mY = y;
    mZ = z;
    mW = w;
}

Vec4::Vec4(Vec3 vec, float w)
{
    mX = vec.mX;
    mY = vec.mY;
    mZ = vec.mZ;
    mW = w;
}

Vec4::operator Vec3() const
{
    return Vec3(mX, mY, mZ);
}

//=============================Mat4=============================
Mat4::Mat4()
{
    set(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
}

void Mat4::set(float val)
{
    set(val, val, val, val,
        val, val, val, val,
        val, val, val, val,
        val, val, val, val);
}

void Mat4::set(Mat4 mat)
{
    set(mat.mMatrix[0][0], mat.mMatrix[0][1], mat.mMatrix[0][2], mat.mMatrix[0][3],
        mat.mMatrix[1][0], mat.mMatrix[1][1], mat.mMatrix[1][2], mat.mMatrix[1][3],
        mat.mMatrix[2][0], mat.mMatrix[2][1], mat.mMatrix[2][2], mat.mMatrix[2][3],
        mat.mMatrix[3][0], mat.mMatrix[3][1], mat.mMatrix[3][2], mat.mMatrix[3][3]);
}

void Mat4::set(float val11, float val12, float val13, float val14, float val21, float val22, float val23, float val24, float val31, float val32, float val33, float val34, float val41, float val42, float val43, float val44)
{
    //Row 1
    mMatrix[0][0] = val11;
    mMatrix[0][1] = val12;
    mMatrix[0][2] = val13;
    mMatrix[0][3] = val14;

    //Row 2
    mMatrix[1][0] = val21;
    mMatrix[1][1] = val22;
    mMatrix[1][2] = val23;
    mMatrix[1][3] = val24;

    //Row 3
    mMatrix[2][0] = val31;
    mMatrix[2][1] = val32;
    mMatrix[2][2] = val33;
    mMatrix[2][3] = val34;

    //Row 4
    mMatrix[3][0] = val41;
    mMatrix[3][1] = val42;
    mMatrix[3][2] = val43;
    mMatrix[3][3] = val44;
}

Vec4 Mat4::multiply(const Vec4 &vec)
{
    Vec4 result;

    result.mX = mMatrix[0][0] * vec.mX + mMatrix[0][1] * vec.mY + mMatrix[0][2] * vec.mZ + mMatrix[0][3] * vec.mW;
    result.mY = mMatrix[1][0] * vec.mX + mMatrix[1][1] * vec.mY + mMatrix[1][2] * vec.mZ + mMatrix[1][3] * vec.mW;
    result.mZ = mMatrix[2][0] * vec.mX + mMatrix[2][1] * vec.mY + mMatrix[2][2] * vec.mZ + mMatrix[2][3] * vec.mW;
    result.mW = mMatrix[3][0] * vec.mX + mMatrix[3][1] * vec.mY + mMatrix[3][2] * vec.mZ + mMatrix[3][3] * vec.mW;

    return result;
}

Mat4 Mat4::multiply(const Mat4 &matB)
{
    float(*a)[4] = mMatrix;
    const float(*b)[4] = matB.mMatrix;

    Mat4 result;
    //Row 1
    result.mMatrix[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0] + a[0][3] * b[3][0];
    result.mMatrix[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1] + a[0][3] * b[3][1];
    result.mMatrix[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2] + a[0][3] * b[3][2];
    result.mMatrix[0][3] = a[0][0] * b[0][3] + a[0][1] * b[1][3] + a[0][2] * b[2][3] + a[0][3] * b[3][3];

    //Row 2
    result.mMatrix[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0] + a[1][3] * b[3][0];
    result.mMatrix[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1] + a[1][3] * b[3][1];
    result.mMatrix[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] * b[3][2];
    result.mMatrix[1][3] = a[1][0] * b[0][3] + a[1][1] * b[1][3] + a[1][2] * b[2][3] + a[1][3] * b[3][3];

    //Row 3
    result.mMatrix[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0] + a[2][3] * b[3][0];
    result.mMatrix[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1] + a[2][3] * b[3][1];
    result.mMatrix[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2] + a[2][3] * b[3][2];
    result.mMatrix[2][3] = a[2][0] * b[0][3] + a[2][1] * b[1][3] + a[2][2] * b[2][3] + a[2][3] * b[3][3];

    //Row 4
    result.mMatrix[3][0] = a[3][0] * b[0][0] + a[3][1] * b[1][0] + a[3][2] * b[2][0] + a[3][3] * b[3][0];
    result.mMatrix[3][1] = a[3][0] * b[0][1] + a[3][1] * b[1][1] + a[3][2] * b[2][1] + a[3][3] * b[3][1];
    result.mMatrix[3][2] = a[3][0] * b[0][2] + a[3][1] * b[1][2] + a[3][2] * b[2][2] + a[3][3] * b[3][2];
    result.mMatrix[3][3] = a[3][0] * b[0][3] + a[3][1] * b[1][3] + a[3][2] * b[2][3] + a[3][3] * b[3][3];

    return result;
}

Mat4 Mat4::translate(const Vec3 &translation)
{
    Mat4 temp;
    temp.mMatrix[0][3] = translation.mX;
    temp.mMatrix[1][3] = translation.mY;
    temp.mMatrix[2][3] = translation.mZ;

    return multiply(temp);
}

Mat4 Mat4::rotate(float rad, const Vec3 &axis)
{
    float c = cos(rad);
    float s = sin(rad);
    float t = 1 - c;
    float x = axis.mX, y = axis.mY, z = axis.mZ;
    float tx = t * x, ty = t * y;

    Mat4 res;

    res.set(
        tx * x + c, tx * y - z * s, tx * z + y * s, 0,
        ty * x + z * s, ty * y + c, ty * z + x * s, 0,
        tx * z - y * s, ty * z + x * s, t * z * z + c, 0,
        0, 0, 0, 1);

    return multiply(res);
}

Mat4 Mat4::rotate(const Vec3 &eulerAngles)
{
    Mat4 res;
    res = res.rotate(eulerAngles.mX, Vec3(1, 0, 0));
    res = res.rotate(eulerAngles.mY, Vec3(0, 1, 0));
    res = res.rotate(eulerAngles.mZ, Vec3(0, 0, 1));

    return multiply(res);
}

Mat4 Mat4::inverse()
{
    float(*a)[4] = mMatrix;

    float t0 = (a[1][1] * a[2][2] * a[3][3]) + (a[1][2] * a[2][3] * a[3][1]) + (a[1][3] * a[2][1] * a[3][2]) - (a[1][3] * a[2][2] * a[3][1]) - (a[1][2] * a[2][1] * a[3][3]) - (a[1][1] * a[2][3] * a[3][2]);
    float t1 = (a[0][1] * a[2][2] * a[3][3]) + (a[0][2] * a[2][3] * a[3][1]) + (a[0][3] * a[2][1] * a[3][2]) - (a[0][3] * a[2][2] * a[3][1]) - (a[0][2] * a[2][1] * a[3][3]) - (a[0][1] * a[2][3] * a[3][2]);
    float t2 = (a[0][1] * a[1][2] * a[3][3]) + (a[0][2] * a[1][3] * a[3][1]) + (a[0][3] * a[1][1] * a[3][2]) - (a[0][3] * a[1][2] * a[3][1]) - (a[0][2] * a[1][1] * a[3][3]) - (a[0][1] * a[1][3] * a[3][2]);
    float t3 = (a[0][1] * a[1][2] * a[2][3]) + (a[0][2] * a[1][3] * a[2][1]) + (a[0][3] * a[1][1] * a[2][2]) - (a[0][3] * a[1][2] * a[2][1]) - (a[0][2] * a[1][1] * a[2][3]) - (a[0][1] * a[1][3] * a[2][2]);

    float det = a[0][0] * t0 - a[1][0] * t1 + a[2][0] * t2 - a[3][0] * t3;

    Mat4 res;

    if (det == 0)
        return res;

    float detInv = 1 / det;

    res.mMatrix[0][0] = t0 * detInv;
    res.mMatrix[0][1] = -t1 * detInv;
    res.mMatrix[0][2] = t2 * detInv;
    res.mMatrix[0][3] = -t3 * detInv;

    res.mMatrix[1][0] = -(a[1][0] * a[2][2] * a[3][3]) - (a[1][2] * a[2][3] * a[3][0]) - (a[1][3] * a[2][0] * a[3][2]) + (a[1][3] * a[2][2] * a[3][0]) + (a[1][2] * a[2][0] * a[3][3]) + (a[1][0] * a[2][3] * a[3][2]);
    res.mMatrix[1][1] = (a[0][0] * a[2][2] * a[3][3]) + (a[0][2] * a[2][3] * a[3][0]) + (a[0][3] * a[2][0] * a[3][2]) - (a[0][3] * a[2][2] * a[3][0]) - (a[0][2] * a[2][0] * a[3][3]) - (a[0][0] * a[2][3] * a[3][2]);
    res.mMatrix[1][2] = -(a[0][0] * a[1][2] * a[3][3]) - (a[0][2] * a[1][3] * a[3][0]) - (a[0][3] * a[1][0] * a[3][2]) + (a[0][3] * a[1][2] * a[3][0]) + (a[0][2] * a[1][0] * a[3][3]) + (a[0][0] * a[1][3] * a[3][2]);
    res.mMatrix[1][3] = (a[0][0] * a[1][2] * a[2][3]) + (a[0][2] * a[1][3] * a[2][0]) + (a[0][3] * a[1][0] * a[2][2]) - (a[0][3] * a[1][2] * a[2][0]) - (a[0][2] * a[1][0] * a[2][3]) - (a[0][0] * a[1][3] * a[2][2]);

    res.mMatrix[2][0] = (a[1][0] * a[2][1] * a[3][3]) + (a[1][1] * a[2][3] * a[3][0]) + (a[1][3] * a[2][0] * a[3][1]) - (a[1][3] * a[2][1] * a[3][0]) - (a[1][1] * a[2][0] * a[3][3]) - (a[1][0] * a[2][3] * a[3][1]);
    res.mMatrix[2][1] = -(a[0][0] * a[2][1] * a[3][3]) - (a[0][1] * a[2][3] * a[3][0]) - (a[0][3] * a[2][0] * a[3][1]) + (a[0][3] * a[2][1] * a[3][0]) + (a[0][1] * a[2][0] * a[3][3]) + (a[0][0] * a[2][3] * a[3][1]);
    res.mMatrix[2][2] = (a[0][0] * a[1][1] * a[3][3]) + (a[0][1] * a[1][3] * a[3][0]) + (a[0][3] * a[1][0] * a[3][1]) - (a[0][3] * a[1][1] * a[3][0]) - (a[0][1] * a[1][0] * a[3][3]) - (a[0][0] * a[1][3] * a[3][1]);
    res.mMatrix[2][3] = -(a[0][0] * a[1][1] * a[2][3]) - (a[0][1] * a[1][3] * a[2][0]) - (a[0][3] * a[1][0] * a[2][1]) + (a[0][3] * a[1][1] * a[2][0]) + (a[0][1] * a[1][0] * a[2][3]) + (a[0][0] * a[1][3] * a[2][1]);

    res.mMatrix[3][0] = -(a[1][0] * a[2][1] * a[3][2]) - (a[1][1] * a[2][2] * a[3][0]) - (a[1][2] * a[2][0] * a[3][1]) + (a[1][2] * a[2][1] * a[3][0]) + (a[1][1] * a[2][0] * a[3][2]) + (a[1][0] * a[2][2] * a[3][1]);
    res.mMatrix[3][1] = (a[0][0] * a[2][1] * a[3][2]) + (a[0][1] * a[2][2] * a[3][0]) + (a[0][2] * a[2][0] * a[3][1]) - (a[0][2] * a[2][1] * a[3][0]) - (a[0][1] * a[2][0] * a[3][2]) - (a[0][0] * a[2][2] * a[3][1]);
    res.mMatrix[3][2] = -(a[0][0] * a[1][1] * a[3][2]) - (a[0][1] * a[1][2] * a[3][0]) - (a[0][2] * a[1][0] * a[3][1]) + (a[0][2] * a[1][1] * a[3][0]) + (a[0][1] * a[1][0] * a[3][2]) + (a[0][0] * a[1][2] * a[3][1]);
    res.mMatrix[3][3] = (a[0][0] * a[1][1] * a[2][2]) + (a[0][1] * a[1][2] * a[2][0]) + (a[0][2] * a[1][0] * a[2][1]) - (a[0][2] * a[1][1] * a[2][0]) - (a[0][1] * a[1][0] * a[2][2]) - (a[0][0] * a[1][2] * a[2][1]);

    return res;
}

Vec3 Mat4::getPos()
{
    return Vec3(mMatrix[0][3], mMatrix[1][3], mMatrix[2][3]);
}

String Mat4::toString()
{
    String result = "[";

    for (int row = 0; row < 4; row++)
    {
        result += "[";
        for (int col = 0; col < 4; col++)
        {
            result += mMatrix[row][col];
            if (col < 3)
                result += ", ";
        }

        result += "]";
        if (row < 3)
            result += "\n";
    }

    result += "]";

    return result;
}