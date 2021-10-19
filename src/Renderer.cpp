#include "Renderer.h"

Renderer::Renderer(int width, int height, Color bg_color, const Rect2f& range_rect) : width(width), height(height), bg_color(bg_color) {
    SDL_Init(SDL_INIT_EVERYTHING);
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    int windowFlags = 0;
    window = SDL_CreateWindow("Patcher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");


    renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, open_color(current_color));

    TTF_Init();
    font = TTF_OpenFont("Anonymous.ttf", 24);
    assert(font);

    coord_system = new PixelCoordSystem(range_rect, {0., 0., (float)width, (float)height});
}

Renderer::~Renderer() {
    delete coord_system;
    printf("renderer destroyed!\n");
}

void Renderer::setColor(Color new_color) {
    current_color = new_color;
    SDL_SetRenderDrawColor(renderer, open_color(current_color));
}

void Renderer::drawFilledCircle(const Vector2& center, const float r, Color color) const {
    SDL_SetRenderDrawColor(renderer, open_color(color));
    float r2 = r * r;
    Vector2 center_point(center);
    Vector2 circle_quadr_diagonal(r, -r);
    center_point -= circle_quadr_diagonal;
    Vector2 pixel_left_up_point = coord_system->translatePoint(center_point);
    center_point += circle_quadr_diagonal;
    center_point += circle_quadr_diagonal;
    Vector2 pixel_right_down_point = coord_system->translatePoint(center_point);
    for (int py = pixel_left_up_point.getY(); py <= pixel_right_down_point.getY(); ++py) {
        for (int px = pixel_left_up_point.getX(); px <= pixel_right_down_point.getX(); ++px) {
            Vector2 coord_point = coord_system->translatePixel({(float)px, (float)py});
            float x_c = (coord_point.getX() - center.getX());
            float y_c = (coord_point.getY() - center.getY()); 
            if (x_c * x_c + y_c * y_c <= r2) {
                SDL_RenderDrawPointF(renderer, px, py);
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::drawRect(const Vector2& p1, const Vector2& p2, Color color) const {
    Vector2 pixel_p1 = coord_system->translatePoint(p1);
    Vector2 pixel_p2 = coord_system->translatePoint(p2);
    SDL_FRect rect = {pixel_p1.getX(), pixel_p1.getY(), pixel_p2.getX() - pixel_p1.getX(), pixel_p2.getY() - pixel_p1.getY()};
    SDL_SetRenderDrawColor(renderer, open_color(color));
    SDL_RenderDrawRectF(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::drawFilledRect(const Vector2& p1, const Vector2& p2, Color color) const {
    Vector2 pixel_p1 = coord_system->translatePoint(p1);
    Vector2 pixel_p2 = coord_system->translatePoint(p2);
    SDL_SetRenderDrawColor(renderer, open_color(color));
    for (int x = pixel_p1.getX(); x <= pixel_p2.getX(); ++x) {
        SDL_RenderDrawLineF(renderer, x, pixel_p1.getY(), x, pixel_p2.getY());
    }
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::drawSegment(const Vector2& p1, const Vector2& p2, Color color) const {
    Vector2 pixel_p1 = coord_system->translatePoint(p1);
    Vector2 pixel_p2 = coord_system->translatePoint(p2);
    SDL_SetRenderDrawColor(renderer, open_color(color));
    SDL_RenderDrawLineF(renderer, pixel_p1.getX(), pixel_p1.getY(), pixel_p2.getX(), pixel_p2.getY());
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::drawLine(const Vector2& p1, const Vector2& p2, Color color) const {
    Vector2 pixel_p1 = coord_system->translatePoint(p1);
    Vector2 pixel_p2 = coord_system->translatePoint(p2);
    SDL_SetRenderDrawColor(renderer, open_color(color));
    SDL_RenderDrawLine(renderer, (int)pixel_p1.getX(), (int)pixel_p1.getY(), (int)pixel_p2.getX(), (int)pixel_p2.getY());
    SDL_RenderDrawLine(renderer, (int)pixel_p1.getX(), (int)pixel_p1.getY(), (int)pixel_p2.getX(), (int)pixel_p2.getY());
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::drawPoint(const Vector2& pos, Color color) const {
    SDL_SetRenderDrawColor(renderer, open_color(color));
    SDL_RenderDrawPointF(renderer, pos.getX(), pos.getY());
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
}

void Renderer::render() {
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, open_color(bg_color));
    SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, open_color(current_color));
}

SystemEvent Renderer::getEvent() const {
    SDL_Event event;
    int res = SDL_PollEvent(&event);
    SystemEvent result_event; // oh...
    if (event.type == SDL_QUIT) {
        result_event.event_type = QUIT_EVENT;
        return result_event;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        result_event.event_type = MOUSE_BUTTON_DOWN;
        result_event.mouse_pos = {coord_system->translatePixel(Vector2(event.button.x, event.button.y))};
        return result_event;
    }
    if (res == 0) {
        result_event.event_type = NO_EVENT;
        return result_event;
    }
    result_event.event_type = OTHER_EVENTS;
    return result_event;
}

void Renderer::drawText(const Vector2& pos, const Vector2& size, const char* text, Color color) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, {open_color(color)});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    Vector2 p1 = coord_system->translatePoint(pos);
    Vector2 p2 = coord_system->translatePoint(pos + size);
    float y = p1.getY();
    p1.setY(p2.getY());
    p2.setY(y);
    int text_width = text_surface->w;
    int text_height = text_surface->h;
    // printf("%f %f %f %f\n", p1.getX(), p1.getY(), p2.getX(), p2.getY());
    SDL_Rect rect = {p1.getX() + 5, p1.getY() + (p2 - p1).getY() / 2 - 24 / 2, (p2 - p1).getX() - 5, 24};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}