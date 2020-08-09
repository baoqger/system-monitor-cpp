#include <iostream>
#include "./Point.h"


int main() {
    Point p{1,1,10};
    std::cout << p.getRadius() << std::endl;
    return 0;
}