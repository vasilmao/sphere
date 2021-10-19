#ifndef INCLUDE_APP
#define INCLUDE_APP

#include <time.h>
#include <stdio.h>
#include "Renderer.h"
// #include "DynamicArray.h"
#include "Tools.h"
// #include "List.h"
#include "Objects.h"

class App {
private:
    friend Renderer;
    Renderer* renderer;

    Camera* camera;
    Sphere* sphere;
    Light* light_source;
    bool running;

    int width;
    int height;

    void parseEvent(const SystemEvent& event);

public:
    App();

    void run();

    ~App();
};

#endif