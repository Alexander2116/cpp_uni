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
#include<iostream>
#include<cmath>
#include "Shapes.cpp"

using namespace myShapes;
//=== main ===
void call_2Dshapes(){
	Rectangle r1(1,1);
	Rectangle r2(2,2);
	r2.ShapeInfo();
}

int main(){
	std::cout << "Welcome" << std::endl;
	Rectangle r(4.0,5.0);
	r.ShapeInfo();
	/* you should see new objects here, the count of total objects
	 should increase after calling the function below*/
	std::cout << std::endl << "Calling a function" << std::endl;
	call_2Dshapes();
	/* the deconstructor is called after function above is executed
	it means we should go back to number of shapes before that function*/
	std::cout << std::endl << "Total number of shapes after the function is executed" << std::endl;
	r.ShapeInfo();
}