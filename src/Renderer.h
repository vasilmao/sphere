#ifndef RENDERER_INCLUDE
#define RENDERER_INCLUDE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "CoordSystem.h"
#include "Tools.h"

enum EventTypes {
    NO_EVENT,
    QUIT_EVENT,
    MOUSE_BUTTON_DOWN,
    OTHER_EVENTS
};

struct MousePos {
    Vector2 pos;
};

struct BigEvent {
    char data[64];
};

struct SystemEvent {
    int event_type;
    union
    {
        MousePos mouse_pos;
        BigEvent big_event;
    };
    SystemEvent(){}
    SystemEvent(const SystemEvent& other_event){
        event_type = other_event.event_type;
        for (int i = 0; i < 64; ++i) {
            big_event.data[i] = other_event.big_event.data[i];
        }
    }
    ~SystemEvent(){}
};

class Renderer {
private:
    SDL_Window* window     = NULL;
    SDL_Renderer* renderer = NULL;
    TTF_Font* font         = NULL;
    // SDL_Surface* surface   = NULL;

    PixelCoordSystem* coord_system;

    // int32_t* pixels = NULL;
    int width = 0;
    int height = 0;

    Color bg_color;
    Color current_color;


public:

    Renderer(){}

    ~Renderer();
    Renderer(int width, int height, Color bg_color, const Rect2f& range_rect);
    void setColor(Color new_color);
    void drawFilledCircle(const Vector2& center, const float r, Color color) const;
    void drawRect(const Vector2& p1, const Vector2& p2, Color color) const;
    void drawFilledRect(const Vector2& p1, const Vector2& p2, Color color) const;
    void drawSegment(const Vector2& p1, const Vector2& p2, Color color) const;
    void drawLine(const Vector2& p1, const Vector2& p2, Color color) const;
    void drawPoint(const Vector2& pos, Color color) const;
    void render();
    void drawText(const Vector2& pos, const Vector2& size, const char* text, Color color);
    SystemEvent getEvent() const;
};

#endif