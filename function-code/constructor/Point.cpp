#include "./Point.h"

Point::Point(int x, int y, int r) {
    x = x;
    y = y;
    radius = r;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

int Point::getRadius() {
    return radius;
}