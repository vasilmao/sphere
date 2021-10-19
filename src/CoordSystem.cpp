#include "CoordSystem.h"

Rect2f PixelCoordSystem::getPixelRect() const{
    return {pixel_x, pixel_y, pixel_width, pixel_height};
}

Rect2f PixelCoordSystem::getCoordRect() const {
    return {x_min, y_min, x_max - x_min, y_max - y_min};
}

PixelCoordSystem::PixelCoordSystem(Rect2f range_rect, Rect2f pixel_rect) {
    x_min = range_rect.x;
    y_min = range_rect.y;
    x_max = range_rect.x + range_rect.width;
    y_max = range_rect.y + range_rect.height;

    pixel_x = pixel_rect.x;
    pixel_y = pixel_rect.y;
    pixel_width = pixel_rect.width;
    pixel_height = pixel_rect.height;

    point_to_pixel_coeff_x = pixel_width   / (x_max - x_min);
    point_to_pixel_coeff_y = pixel_height  / (y_max - y_min);
}

Vector2 PixelCoordSystem::translatePoint(const Vector2& point) const {
    // printf("(%f %f %f %f) ___ (%f %f %f %f) (%f %f)\n", x_min, y_min, x_max, y_max, pixel_x, pixel_y, pixel_width, pixel_height, point_to_pixel_coeff_x, point_to_pixel_coeff_y);
    // printf("input: (%f %f)\n", point.getX(), point.getY());
    float delta_x  = point.getX() - x_min;
    float delta_y  = point.getY() - y_min;
    float result_x = pixel_x +                 delta_x * point_to_pixel_coeff_x;
    float result_y = pixel_y + (pixel_height - delta_y * point_to_pixel_coeff_y); // (pixel_height - ...) because y counts for top
    return Vector2(result_x, result_y);
}

Vector2 PixelCoordSystem::translatePixel(const Vector2& pixel) const {
    // printf("(%f %f %f %f) ___ (%f %f %f %f) (%f %f)\n", x_min, y_min, x_max, y_max, pixel_x, pixel_y, pixel_width, pixel_height, point_to_pixel_coeff_x, point_to_pixel_coeff_y);
    float delta_x  = pixel.getX() - pixel_x;
    float delta_y  = pixel.getY() - pixel_y;
    float result_x = x_min +                    delta_x / point_to_pixel_coeff_x;
    float result_y = y_min + ((y_max - y_min) - delta_y / point_to_pixel_coeff_y); // (pixel_height - ...) because y counts for top
    return Vector2(result_x, result_y);
}


CoordSystem::CoordSystem(Rect2f range_rect, Rect2f absolute_rect) {
    relative_pos = Vector2(range_rect.x, range_rect.y);
    relative_size = Vector2(range_rect.width, range_rect.height);
    absolute_pos = Vector2(absolute_rect.x, absolute_rect.y);
    absolute_size = Vector2(absolute_rect.width, absolute_rect.height);

    rel_to_abs_coeff_x = relative_size.getX()  / absolute_size.getX();
    rel_to_abs_coeff_y = relative_size.getY()  / absolute_size.getY();
}

Vector2 CoordSystem::translateToAbsolute(const Vector2& point) const {
    // printf("(%f %f %f %f) ___ (%f %f %f %f) (%f %f)\n", x_min, y_min, x_max, y_max, pixel_x, pixel_y, pixel_width, pixel_height, point_to_pixel_coeff_x, point_to_pixel_coeff_y);
    // printf("input: (%f %f)\n", point.getX(), point.getY());
    float delta_x  = point.getX() - relative_pos.getX();
    float delta_y  = point.getY() - relative_pos.getY();
    float result_x = absolute_pos.getX() + delta_x * rel_to_abs_coeff_x;
    float result_y = absolute_pos.getY() + delta_y * rel_to_abs_coeff_y;
    return Vector2(result_x, result_y);
}

void CoordSystem::setRelativeSize(const Vector2& new_size) {
    relative_size = new_size;
    rel_to_abs_coeff_x = relative_size.getX()  / absolute_size.getX();
    rel_to_abs_coeff_y = relative_size.getY()  / absolute_size.getY();
}

void CoordSystem::setAbsoluteSize(const Vector2& new_size) {
    absolute_size = new_size;
    rel_to_abs_coeff_x = relative_size.getX()  / absolute_size.getX();
    rel_to_abs_coeff_y = relative_size.getY()  / absolute_size.getY();
}

void CoordSystem::setRelativePos(const Vector2& new_pos) {
    relative_pos = new_pos;
}
void CoordSystem::setAbsolutePos(const Vector2& new_pos) {
    absolute_pos = new_pos;
}

const Vector2& CoordSystem::getRelativeSize() {
    return relative_size;
}

const Vector2& CoordSystem::getAbsoluteSize() {
    return absolute_size;
}

const Vector2& CoordSystem::getRelativePos() {
    return relative_pos;
}
const Vector2& CoordSystem::getAbsolutePos() {
    return absolute_pos;
}