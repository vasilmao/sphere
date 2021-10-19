#ifndef INCLUDE_OBJECTS
#define INCLUDE_OBJECTS

#include "Renderer.h"
#include "RayCaster.h"
#include "Vector.h"

class Light {
private:
    Vector3 pos;
    Color01 color;
    Vector3 color_v;
public:
    Light(){}
    Light(const Vector3& pos, Color01 color);
    const Vector3& getPos() const;
    void setPos(const Vector3& new_pos);
    Color01 getColor() const;
    const Vector3& getColorV() const;
    void setColor(Color01 new_color);
    void render(Renderer* renderer);
    ~Light(){}
};

class Camera {
private:
    Vector3 pos;
    Vector3 direction;
    Vector2 view_area;
public:
    Camera(){}
    Camera(const Vector3& pos, const Vector3& direction, const Vector2& view_area);
    const Vector3& getPos() const;
    const Vector3& getDirection() const;
    const Vector2& getViewArea() const;
    void setPos(const Vector3& new_pos);
    void setDirection(const Vector3& new_direction);
    void setViewArea(const Vector2& new_view_area);
    ~Camera(){}
};

class Sphere {
private:
    Vector3 pos;
    float r;
    Color01 color;
    Vector3 color_v;
public:
    Sphere(){}
    Sphere(const Vector3& pos, float r, Color01 color);
    const Vector3& getPos() const;
    void setPos(const Vector3& new_pos);
    float getR() const;
    void setR(float new_r);
    Color01 getColor() const;
    const Vector3& getColorV() const;
    void setColor(Color01 new_color);
    void render(Renderer* renderer, Camera* camera, Light* light);
    bool intersecsRay(float x, float y) const;
    float computeZByXY(float x, float y) const;

    ~Sphere(){}
};

#endif