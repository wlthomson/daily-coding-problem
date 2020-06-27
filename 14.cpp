#include <iostream>
#include <iomanip>
#include <math.h> 
#include <stdlib.h>

using namespace std;

double rand_d() {
    return (double)rand() / RAND_MAX;
}

class Point {
    public:
        double x;
        double y;

        Point();
        Point(double x, double y);

};

class Square {
    private:
        Point p;
        double w;
        double h;
    public:
        Square(Point p, double w, double h);
        Point get_random_point();
};

class Circle {
    private:
        Point c;
        double r;
    public:
        Circle(double r);
        bool contains_point(Point p);
};

Point::Point() {
    this->x = 0.0;
    this->y = 0.0;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Square::Square(Point p, double w, double h) {
    this->p = p;
    this->w = w;
    this->h = h;
}

Point Square::get_random_point() {
    double x_min = this->p.x;
    double x_max = this->p.x + this->w;
    double x = rand_d() * (x_max-x_min)+x_min;

    double y_min = this->p.y;
    double y_max = this->p.y + this->h;
    double y = rand_d() * (y_max-y_min)+y_min;

    return Point(x, y);
}

Circle::Circle(double r) {
    this->c = Point(0.0, 0.0);
    this->r = r;
}

bool Circle::contains_point(Point p) {
    double a = pow(p.x-this->c.x, 2);
    double b = pow(p.y-this->c.y, 2);
    double c = pow(this->r, 2);
    return a + b < c;
}

int main() {
    double r = 1.0;

    Circle c(r);
    Point p(-r,-r);
    Square s(p, 2*r, 2*r);

    int i_max = 10000000;
    int count = 0;
    for (int i = 0; i < i_max; i++) {
        if (c.contains_point(s.get_random_point())) count++;
    }
    double pi = count * 4.0 / i_max;
    
    cout << fixed;
    cout << setprecision(3);
    cout << pi << endl;
}