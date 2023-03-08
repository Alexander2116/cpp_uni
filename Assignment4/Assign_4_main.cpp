/*============================================================
** UTF-8
**
** Assignment 4  (Deadline: 10/03/2023)
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Creating complex numbers using a class
**        : Creating overloading function for arthmetic operation AND osteam(<<), istream(>>)
**
** Classes: complex(double, double)
**
** Comments: Not protected from division by 0
**         :
**
** Date:  8 March 2023
**
===========================================================*/


//=== includes ===
#include<iostream>
#include<cmath>

//=== defined classes ===
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
    complex(){re=im=0;}
    complex(double re_in, double im_in){
        re = re_in;
        im = im_in;
    }
    ~complex(){}

    // return real part
    double get_real() const{
        return re;
    }
    // return imaginary part
    double get_imaginary() const{
        return im;
    }
    // return modulus of a+ib: |a+ib| = sqrt(a2+b2)
    double get_modulus() const{
        return sqrt(re*re + im*im);
    }
    // return complex conjugate: change sign of imaginaty part
    complex get_conjugate() const{
        return complex(re, -im);
    }
    // return phase in radians: arctan(|im|/|re|)
    double get_argument() const{
      return atan2(im, re); // radians
    }
    // Complex addition
    // (a+ib)+(c+id) = (a+c) + i(b+d)
    complex operator+(const complex& z){
        return complex(re+z.re, im+z.im);
    }
    // Complex subtration
    // (a+ib)-(c+id) = (a-c) + i(b-d)
    complex operator-(const complex& z){
        return complex(re-z.re, im-z.im);
    }
    // Complex multiplication
    // (a+ib)*(c+id) = ac-bd + i(ad+bc)
    complex operator*(const complex& z){
        return complex(re*z.re-im*z.im, re*z.im + im*z.re);
    }
    // Complex division
    // (a+ib)/(c+id) = (a+ib)(c-id)/(c2+d2) = (ac+bd)/(c2+d2) + i (ad-bc)/(c2+d2)
    // Could be also defined as: a(re,im)*c.get_conjugate() * (1/c.get_modulus() ^2)
    complex operator/(const complex& z){
        double denom = 1/(z.re*z.re + z.im*z.im);
        return complex(denom*(re*z.re + im*z.im), denom*(im*z.re - re*z.im));
    }
    // Scaling by a float
    // A(a+ib) = Aa + i Ab
    complex operator*(const double& a){
        return complex(re*a, im*a);
    }
    // (a+ib)/A = a/A + i b/A
    complex operator/(const double& a){
        return complex(re/a, im/a);
    }
};

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

//=== main ===
int main(){
    std::cout.precision(3);

    // Create two complex numbers
    complex a(3,4);
    complex b(1,-2);

    // Get real and imaginary components, modulus and argument - One line in terminal
    std::cout << a.get_real() << ", " << a.get_imaginary() << ", "; // 3, 4,
    std::cout << a.get_modulus() << ", " << a.get_argument() <<std::endl; // 5, arctan(4/3) = 0.927295
    // Get conjugates
    std::cout << a << " :  " << a.get_conjugate() << std::endl;
    std::cout << b << " :  " << b.get_conjugate() << std::endl;

    // Get sum, difference, product and quotient of a and b
    // Print out results, also demonstrating use of overloaded operator<<
    std::cout << "a+b = " << a+b << std::endl; // 4-2
    std::cout << "a-b = " << a-b << std::endl; // 2+6
    std::cout << "a*b = " << a*b << std::endl; // 11-2
    std::cout << "a/b = " << a/b << std::endl; // -1+2
    // Scale
    std::cout << a+b*2 << std::endl; // 5+0
    std::cout << a+2*b << std::endl; // 5+0
    std::cout << (a+b*2)*2 << std::endl; // 10+0

    // Use of >> operator
    complex zin;
    std::cout << "--- Enter a+ib or a-ib or anything really to test:  ";
    std::cin >> zin;
    std::cout << "You entered: " << zin;

    return 0;
}