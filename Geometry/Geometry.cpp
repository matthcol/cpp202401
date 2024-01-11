#include <iostream>
#include "Point.h"
#include <vector>

void playWithPoints() {
    Point p0; // default constructor
    Point pA("A", 3.5, 4.75);
    Point pB("B", 7.5, 1.75);
    std::cout << p0.toString() << std::endl;
    std::cout << pA.toString() << std::endl;
    Form& f = pA;
    std::cout << f.toString() << std::endl; 
    std::cout << f << std::endl;
    std::cout << pA << std::endl;
    std::cout << "Distance A-B: "
        << pA.distance(pB)
        << " or " << pB.distance(pA)
        << std::endl;
    for (auto& p : { p0, pA, pB }) {
        std::cout << "before translate: " << p << std::endl;
    }
    std::vector<Point> points{ p0, pA, pB };
    for (auto& p : points) {
        p.translate(1, -1);
        std::cout << "before translate: " << p << std::endl;
    }
}

int main()
{
    playWithPoints();
    return 0;
}
