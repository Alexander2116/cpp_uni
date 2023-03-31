// Shapes.cpp
#include "Shapes.hpp"

using namespace myShapes;

/* Shape2D */
Shape2D::Shape2D(std::string shape_type){
    shape_name = shape_type;
    n_objects += 1;
}
Shape2D::~Shape2D(){
    ar = 0;
    shape_name = "";
    n_objects -= 1;
}
double Shape2D::GetArea(){return ar;}
void Shape2D::Info(){
    std::cout << "This is a " << shape_name << " of area " << ar << std::endl;
}
void Shape2D::NumberShapeInfo(){
    std::cout << "There are " << n_objects <<" 2D shapes in total" << std::endl;
}
int Shape2D::n_objects{0};

/* Rectangle */
Rectangle::Rectangle(double a, double b): Shape2D{"Rectangle"}{
    count += 1;
    ar = a*b;
}
Rectangle::~Rectangle(){count -= 1;}
void Rectangle::CountInfo(){
    std::cout << "This is one of " << count << " rectangles" << std::endl;
}
int Rectangle::count{0};

/* Square */
Square::Square(double a): Shape2D{"Square"}{
    count += 1;
    ar = a*a;
}
Square::~Square(){count -= 1;}
void Square::CountInfo(){
    std::cout << "This is one of " << count << " rectangles" << std::endl;
}
int Square::count{0};

/* Ellipse */
Ellipse::Ellipse(double a, double b): Shape2D{"Ellipse"}{
    count += 1;
    ar = M_PI*a*b;
}
Ellipse::~Ellipse(){count -= 1;}
void Ellipse::CountInfo(){
    std::cout << "This is one of " << count << " rectangles" << std::endl;
}
int Ellipse::count{0};

/* Circle */
Circle::Circle(double a): Shape2D{"Circle"}{
    count += 1;
    ar = M_PI*a*a;
}
Circle::~Circle(){count -= 1;}
void Circle::CountInfo(){
    std::cout << "This is one of " << count << " rectangles" << std::endl;
}
int Circle::count{0};

/* Shape3D */
Shape3D::Shape3D(std::string shape_type){
    shape_name = shape_type;
    n_objects += 1;
}
Shape3D::~Shape3D(){
    vol = 0;
    shape_name = "";
    n_objects -= 1;
}
double Shape3D::GetVolume(){return vol;}
void Shape3D::ShapeInfo(){
    std::cout << "There are " << n_objects <<" 3D shapes in total" << std::endl;
}
int Shape3D::n_objects{0};

/* Cuboid */
Cuboid::Cuboid(double h, double l, double w): Shape3D{"Cuboid"}{
    count += 1;
    vol = h*l*w;
}
Cuboid::~Cuboid(){count -= 1;}
void Cuboid::Info(){
    ShapeInfo();
    std::cout << "This is a " << shape_name << " of volume " << vol << std::endl;
    std::cout << "This is one of " << count << " cuboids" << std::endl;
}
int Cuboid::count{0};

/* Cube */
Cube::Cube(double a): Shape3D{"Cube"}{
    count += 1;
    vol = a*a*a;
}
Cube::~Cube(){count -= 1;}
void Cube::Info(){
    ShapeInfo();
    std::cout << "This is a " << shape_name << " of volume " << vol << std::endl;
    std::cout << "This is one of " << count << " cubes" << std::endl;
}
int Cube::count{0};

/* Ellipsoid */
Ellipsoid::Ellipsoid(double a, double b, double c): Shape3D{"Ellipsoid"}{
    count += 1;
    vol = (4/3)*M_PI*a*b*c;
}
Ellipsoid::~Ellipsoid(){count -= 1;}
void Ellipsoid::Info(){
    ShapeInfo();
    std::cout << "This is a " << shape_name << " of volume " << vol << std::endl;
    std::cout << "This is one of " << count << " ellipsoids" << std::endl;
}
int Ellipsoid::count{0};

/* Sphere*/
Sphere::Sphere(double a): Shape3D{"Sphere"}{
    count += 1;
    vol = (4/3)*M_PI*a*a*a;
}
Sphere::~Sphere(){count -= 1;}
void Sphere::Info(){
    ShapeInfo();
    std::cout << "This is a " << shape_name << " of volume " << vol << std::endl;
    std::cout << "This is one of " << count << " spheres" << std::endl;
}
int Sphere::count{0};