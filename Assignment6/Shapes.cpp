// Shapes.cpp
#include "Shapes.hpp"
#define _USE_MATH_DEFINES
namespace myShapes{

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
        sur_area = 0;
        vol = 0;
        shape_name = "";
        n_objects -= 1;
    }
    double Shape3D::GetVolume(){return vol;}
    double Shape3D::GetSurfaceArea(){return sur_area;}
    void Shape3D::Info(){
        std::cout << "This is a " << shape_name << " of volume " << vol 
        << " and surface area of " << sur_area << std::endl;
    }
    void Shape3D::NumberShapeInfo(){
        std::cout << "There are " << n_objects <<" 3D shapes in total" << std::endl;
    }
    int Shape3D::n_objects{0};

    /* Cuboid */
    Cuboid::Cuboid(double h, double l, double w): Shape3D{"Cuboid"}{
        count += 1;
        vol = h*l*w;
        sur_area = 2*(h*l + l*w + w*h);
    }
    Cuboid::~Cuboid(){count -= 1;}
    void Cuboid::CountInfo(){
        std::cout << "This is one of " << count << " cuboids" << std::endl;
    }
    int Cuboid::count{0};

    /* Cube */
    Cube::Cube(double a): Shape3D{"Cube"}{
        count += 1;
        vol = a*a*a;
        sur_area = 6*a*a;
    }
    Cube::~Cube(){count -= 1;}
    void Cube::CountInfo(){
        std::cout << "This is one of " << count << " cubes" << std::endl;
    }
    int Cube::count{0};

    /* Ellipsoid */
    Ellipsoid::Ellipsoid(double a, double b, double c): Shape3D{"Ellipsoid"}{
        count += 1;
        vol = (4/3)*M_PI*a*b*c;
        double temp = std::pow(a*b,1.6) + std::pow(b*c,1.6) + std::pow(a*c,1.6);
        sur_area = 4*M_PI*std::pow(temp/3, 1/1.6); // Approximate formula
    }
    Ellipsoid::~Ellipsoid(){count -= 1;}
    void Ellipsoid::Info(){
        std::cout << "This is a " << shape_name << " of volume " << vol 
        << " and the surface area is approximately " << sur_area << std::endl;
    }
    void Ellipsoid::CountInfo(){
        std::cout << "This is one of " << count << " ellipsoids" << std::endl;
    }
    int Ellipsoid::count{0};

    /* Sphere*/
    Sphere::Sphere(double a): Shape3D{"Sphere"}{
        count += 1;
        vol = (4/3)*M_PI*a*a*a;
        sur_area = 4*M_PI*a*a;
    }
    Sphere::~Sphere(){count -= 1;}
    void Sphere::CountInfo(){
        std::cout << "This is one of " << count << " spheres" << std::endl;
    }
    int Sphere::count{0};

    /* Prism */
    Prism::Prism(Shape2D* shape, double h): Shape3D("Prism"){
        vol = shape->GetArea() * h;
    }
    Prism::~Prism(){}
    void Prism::Info(){
        std::cout << "This is a " << shape_name << " of volume " << vol << std::endl;
    }

}