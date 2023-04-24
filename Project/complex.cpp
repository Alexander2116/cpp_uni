// complex.cpp

#include "complex.hpp"

namespace myComplex{

    // Constructors and deconstructor
    complex::complex(){re=im=0;}
    complex::complex(double re_in, double im_in){
        re = re_in;
        im = im_in;
    }
    complex::~complex(){re=im=0;}

    // return real part
    double complex::get_real() const{
        return re;
    }
    // return imaginary part
    double complex::get_imaginary() const{
        return im;
    }
    // return modulus of a+ib: |a+ib| = sqrt(a2+b2)
    double complex::get_modulus() const{
        return sqrt(re*re + im*im);
    }
    // return complex conjugate: change sign of imaginary part
    complex complex::get_conjugate() const{
        return complex(re, -im);
    }
    // return phase in radians: arctan(|im|/|re|)
    double complex::get_argument() const{
      return atan2(im, re); // radians
    }
    // Complex addition
    // (a+ib)+(c+id) = (a+c) + i(b+d)
    complex complex::operator+(const complex& z){
        return complex(re+z.re, im+z.im);
    }
    // Complex subtraction
    // (a+ib)-(c+id) = (a-c) + i(b-d)
    complex complex::operator-(const complex& z){
        return complex(re-z.re, im-z.im);
    }
    // Complex multiplication
    // (a+ib)*(c+id) = ac-bd + i(ad+bc)
    complex complex::operator*(const complex& z){
        return complex(re*z.re-im*z.im, re*z.im + im*z.re);
    }
    // Complex division
    // (a+ib)/(c+id) = (a+ib)(c-id)/(c2+d2) = (ac+bd)/(c2+d2) + i (ad-bc)/(c2+d2)
    // Could be also defined as: a(re,im)*c.get_conjugate() * (1/c.get_modulus() ^2)
    complex complex::operator/(const complex& z){
        double denom = 1/(z.re*z.re + z.im*z.im);
        return complex(denom*(re*z.re + im*z.im), denom*(im*z.re - re*z.im));
    }
    // Scaling by a float
    // A(a+ib) = Aa + i Ab
    complex complex::operator*(const double& a){
        return complex(re*a, im*a);
    }
    // (a+ib)/A = a/A + i b/A
    complex complex::operator/(const double& a){
        return complex(re/a, im/a);
    }


    //=== defined functions ===
    // Functions to overload: << and >> operator for complex
    std::ostream& operator<<(std::ostream& os, const complex& z){
        // I want string to look like "a + bi" or "a - bi"
        if(z.im >= 0){
            os << z.re << " + " << z.im << "i";
        }
        else{
            // I just want to have sign separated by space on both sides
            os << z.re << " - " << std::abs(z.im) << "i";
        }
        return os;
    }
    // Syntax: a+ib or a-ib
    std::istream& operator>>(std::istream& is, complex& z){
        char sign{}; // Either + or -
        char i_u{}; // i unit

        // Syntax to enter
        is >> z.re >> sign >> i_u >> z.im;
        // If user enters a-ib then than means a+i(-b)
        if(sign == '-' && (i_u == 'i' || i_u == 'j')){
            z.im = -z.im;
        }
        else if(sign == '+' && (i_u == 'i' || i_u == 'j')){
            // All good
        }
        else{
            std::cout << "Not valid input" << std::endl;
            is.clear();
            z.re = 0;
            z.im = 0;
            return is;
        }
        return is;
    }

    // This is made so I could use a*z, NOT ONLY z*a
    complex operator*(const double a, const complex& z){
        return complex(a*z.get_real(), a*z.get_imaginary());
    }

    complex operator/(const double a, const complex& z){
        return complex(a*z.get_real()/z.get_modulus(), -a*z.get_imaginary()/z.get_modulus());
    }

    complex operator+(const complex& z1, const complex& z2){
        return z1+z2;
    }

    complex operator+=(const complex& z1, const complex& z2){
        return z1+z2;
    }
}