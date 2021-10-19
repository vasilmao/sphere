#include "App.h"

const int WIDTH  = 800;
const int HEIGHT = 800;

const Color bg_color = {185, 226, 235, 255};
const Rect2f range_rect = {0, 0, 800, 800};
const Rect2f pixel_rect = {0, 0, WIDTH, HEIGHT};

App::App() {
    running = false;

    width = WIDTH;
    height = HEIGHT;
    renderer = new Renderer(width, height, bg_color, range_rect);
    camera = new Camera({0, 0, 150}, {0, 1, 0}, {range_rect.width, range_rect.height});
    sphere = new Sphere({0, 0, 0}, 120, {1, 0, 0});
    light_source = new Light({-1300, -1300, 0}, {1, 1, 1});

}

App::~App() {
    delete renderer;
    delete light_source;
    delete camera;
    delete sphere;
    printf("app destroyed!\n");
    return;
}

void App::run() {
    running = true;
    while (running) {
        SystemEvent event_result = renderer->getEvent();
        while (event_result.event_type > 0) {
            parseEvent(event_result);
            if (!running) {
                break;
            }
            event_result = renderer->getEvent();
        }
        // printf("events passed!\n");
        if (!running) {
            break;
        }
        // float dt = 0.002;
        sphere->render(renderer, camera, light_source);
        // light_source->render(renderer);
        printf("Yes!!\n");
        renderer->render();
        SDL_Delay(1000);
    }
}

void App::parseEvent(const SystemEvent& event) {
    switch (event.event_type)
    {
    case QUIT_EVENT:
        running = false;
        break;
    case MOUSE_BUTTON_DOWN:
        break;
    default:
        break;
    }
}