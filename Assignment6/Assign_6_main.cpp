/*============================================================
** UTF-8, Win32
**
** Assignment 5  (Deadline: 24/03/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Creating a matrix with functionalities like calculating determinant, multiplying, cropping (removing a column and a row)
**        : Creating overloading function for arithmetic operation AND ostream(<<), istream(>>)
**
** Classes: Matrix(double, double) / Matrix(array, double, double)
**
** Comments : Not protected from division by 0
**          : Using uint32_t (or size_t) and putting negative value means value = size(uint32_t)-value.
				so user can put negative value but it will be turned into some large (2^32 - 1 - VALUE) positive value
			: User can creat its own matrix
			: Determinant is calculated using Expansion by Minors algorithm (a recursive alg.)
			: Multiplication and Determinant calculations were tested and compered with https://matrix.reshish.com/determinant.php
**
** Date:  22 March 2023
**
===========================================================*/


//=== includes ===
#include<vector>
#include "Shapes.cpp" // cmath + iostream

using namespace myShapes;

//=== main ===
int main(){
	std::vector<Shape2D*> shapes2D;
	shapes2D.push_back(new Rectangle{2,1});
	shapes2D.push_back(new Square{5});
	shapes2D.push_back(new Ellipse{4,2});
	shapes2D.push_back(new Circle{3});

	std::vector<Shape3D*> shapes3D;
	shapes3D.push_back(new Cuboid{2,1,1});
	shapes3D.push_back(new Cube{5});
	shapes3D.push_back(new Ellipsoid{4,2,1});
	shapes3D.push_back(new Sphere{3});

	for(auto sh : shapes2D){
		sh->Info();
	}
	std::cout << std::endl;
	for(auto sh : shapes3D){
		sh->Info();
	}
	std::cout << std::endl;

	shapes2D.clear();
	shapes3D.clear();

	Prism prism_example{new Square{3}, 5};
	prism_example.Info();
	std::cout << "Volume: " << prism_example.GetVolume();

}