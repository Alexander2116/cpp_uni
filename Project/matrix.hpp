/*============================================================
** UTF-8, Win32
**
** Name:  Aleksander Kedziora
** Student ID:  10458000
**
**
** Purpose: Storing strings in a matrix form. Usefull for graphical components storage
**
** Classes: StringMatrix(int, int)
**
** Comments : Modified code of assignment-5
**
** Date:  22 March 2023
**
===========================================================*/

#ifndef MATRIX_H // include guard
#define MATRIX_H

#include<iostream>
#include<cmath>

namespace myMatrix{


    //=== defined classes ===
    class StringMatrix
    {
        // Friends
        friend std::ostream& operator<<(std::ostream &os, StringMatrix &m);
        friend std::istream& operator>>(std::istream &is, StringMatrix &m);
    private:
        uint32_t _rows{0}, _columns{0};
        std::string *_matrix_data{nullptr}; // it will be string[] 1D array/list
    public:
        // Default constructor
        StringMatrix()= default;
        // Parameterized constructors
        // Using (int) instead of (uint32_t) makes it easier to detect negative value (by the cost of memory)
        StringMatrix(int m, int n);
        // Copy constructor
        StringMatrix(StringMatrix &m);
        // Move constructor
        StringMatrix(StringMatrix &&m);
        // Destructor
        ~StringMatrix();
        
        // Access functions
        int get_rows() const; // Return number of rows
        int get_cols() const; // Return number of columns

        // Return array's position of the value by putting its matrix coordinates 
        int index(uint32_t m, uint32_t n) const;
        // Display the data in a nice way
        void show();

        // For easy return of M_(mn) item of the matrix M
        std::string& operator()(uint32_t m, uint32_t n);

        // To return m-th element of the array
        std::string& operator[](uint32_t m);
        
        // Copy assignment operator
        StringMatrix& operator=(StringMatrix &m) noexcept;

        // Move assignment operator
        StringMatrix& operator=(StringMatrix &&m) noexcept;
    };

    // === Functions to overload ===
    std::ostream &operator<<(std::ostream &os, StringMatrix &m);
    std::istream &operator>>(std::istream &is, StringMatrix &m);

}

#endif /* !MATRIX_H */