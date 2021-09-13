#include "Vector.h"

Vector::Vector(float x, float y, float z): x(x), y(y), z(z) {
    length = sqrt(x * x + y * y + z * z);
}

Vector::Vector(const Vector&other): x(other.x), y(other.y), z(other.z), length(other.length) {}

float Vector::getX() const {
    return x;
}

float Vector::getY() const {
    return y;
}

float Vector::getZ() const {
    return z;
}

float Vector::getLength() const {
    return length;
}

void Vector::normalize() {
    x /= length;
    y /= length;
    z /= length;
    length = 1;
}

Vector& operator += (Vector& v1, const Vector& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

Vector& operator -= (Vector& v1, const Vector& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

Vector operator + (const Vector& v1, const Vector& v2) {
    Vector result(v1);
    result += v2;
    return result;
}

Point3f operator + (const Point3f& p, const Vector& v) {
    return {p.x + v.x, p.y + v.y, p.z + v.z};
}

Vector operator - (const Vector& v1, const Vector& v2) {
    Vector result(v1);
    result -= v2;
    return result;
}

Vector& operator *= (Vector& vector, const float coef) {
    vector.x *= coef;
    vector.y *= coef;
    vector.z *= coef;
    vector.length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    return vector;
}

Vector operator * (const Vector& vector, const float coef) {
    Vector result(vector);
    result *= coef;
    return result;
}
