#ifndef INCLUDE_VECTOR_CLASS
#define INCLUDE_VECTOR_CLASS

#include <stdio.h>
#include <math.h>
#include "ToolStructs.h"

class Vector {

private:
    float x = 0;
    float y = 0;
    float z = 0;
    float length = 0;

public:
    Vector(float x, float y, float z);
    Vector(const Vector& other);

    Vector(){}
    ~Vector(){}

    void update();
    float getX() const;
    float getY() const;
    float getZ() const;
    float getLength() const;
    void normalize();

    friend Vector& operator += (Vector& v1,     const Vector& v2);
    friend Vector& operator -= (Vector& v1,     const Vector& v2);
    friend Vector operator + (const Vector& v1, const Vector& v2);
    friend Point3f operator + (const Point3f& p, const Vector& v);
    friend Vector operator - (const Vector& v1, const Vector& v2);
    friend Vector& operator *= (Vector& vector, const float coef);
    friend Vector operator * (const Vector& vector, const float coef);

};


#endif