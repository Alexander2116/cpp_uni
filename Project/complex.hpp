/*============================================================
** UTF-8
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Creating complex numbers using a class
**        : Creating overloading function for arithmetic operation AND ostream(<<), istream(>>)
**
** Classes: complex(double, double)
**
** Comments: Not protected from division by 0
**         : Code copied from my 4th assignment
**
** Date:  8 March 2023
**
===========================================================*/

#ifndef COMPLEX_H // include guard
#define COMPLEX_H

#include<iostream>
#include<cmath>

namespace myComplex{
	class complex
	{
	private:
		// Real and Imaginary part
		double re,im;
	public:
		// Functions to overload operator << and >>
		friend std::ostream& operator<<(std::ostream& os, const complex& z);
		friend std::istream& operator>>(std::istream& is, complex& z);

		// Constructors and deconstructor
		complex();
		complex(double re_in, double im_in);
		~complex();

		// return real part
		double get_real() const;
		// return imaginary part
		double get_imaginary() const;
		// return modulus of a+ib: |a+ib| = sqrt(a2+b2)
		double get_modulus() const;
		// return complex conjugate: change sign of imaginaty part
		complex get_conjugate() const;
		// return phase in radians: arctan(|im|/|re|)
		double get_argument() const;
		// Complex addition
		// (a+ib)+(c+id) = (a+c) + i(b+d)
		complex operator+(const complex& z);
		// Complex subtration
		// (a+ib)-(c+id) = (a-c) + i(b-d)
		complex operator-(const complex& z);
		// Complex multiplication
		// (a+ib)*(c+id) = ac-bd + i(ad+bc)
		complex operator*(const complex& z);
		// Complex division
		// (a+ib)/(c+id) = (a+ib)(c-id)/(c2+d2) = (ac+bd)/(c2+d2) + i (ad-bc)/(c2+d2)
		// Could be also defined as: a(re,im)*c.get_conjugate() * (1/c.get_modulus() ^2)
		complex operator/(const complex& z);
		// Scaling by a float
		// A(a+ib) = Aa + i Ab
		complex operator*(const double& a);
		// (a+ib)/A = a/A + i b/A
		complex operator/(const double& a);

	};

	//=== defined functions ===
	// Functions to overload: << and >> operator for complex
	std::ostream& operator<<(std::ostream& os, const complex& z);
	// Syntax: a+ib or a-ib
	std::istream& operator>>(std::istream& is, complex& z);

	// This is made so I could use a*z, NOT ONLY z*a
	complex operator*(const double a, const complex& z);

	complex operator/(const double a, const complex& z);

	complex operator+(const complex& z1, const complex& z2);

	complex operator+=(const complex& z1, const complex& z2);

}

#endif /* !COMPLEX_H */