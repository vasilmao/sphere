#ifndef INCLUDE_PLOT
#define INCLUDE_PLOT
#include "Vector.h"
#include "CoordSystem.h"
#include "Renderer.h"

// полезно - больше универсальности и меньше зависимости от конкретной библиотеки


class Plot {
private:
    CoordSystem coord_system;
    float (*function)(float x);
public:

    Plot(){}
    Plot(CoordSystem coord_system, float (*function)(float x));
    ~Plot(){}

    Recti getScreenRect() const;
    void setFunction(float (*function)(float x));
    void render(Renderer* render) const;
    void renderVector(Renderer* renderer, const Vector& vector, const Pointf& point) const;
    void renderSegment(Renderer* renderer, const Vector& seg_vector, const Pointf& point) const;
};


void updatePlot(Plot* plot);
void renderPlot(SDL_Renderer* renderer, Plot* plot, int x, int y);
void destroyPlot(Plot* plot);
void addVector(Plot* plot, Vector vector);
#endif