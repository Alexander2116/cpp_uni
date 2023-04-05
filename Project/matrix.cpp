// circuit.cpp

#include "matrix.hpp"

namespace myMatrix{


    //=== defined classes ===
    
        StringMatrix::StringMatrix(int m, int n){
            if(m<1 || n<1){
                std::cout<<"Cannot create the matrix"<<std::endl;
                exit(1);
            }
            _rows = m;
            _columns = n;
            _matrix_data = new std::string[m*n];
            for(int i=0; i<m*n; i++){
                _matrix_data[i] = "       "; // 7 chars
            }
        }
        // Copy constructor
        StringMatrix::StringMatrix(StringMatrix &m){
            // Just copy the data
            _rows = m._rows;
            _columns = m._columns;
            _matrix_data = new std::string[_rows*_columns];
            for(int i = 0; i<_rows*_columns; i++){
                _matrix_data[i] = m._matrix_data[i];
            }
        }
        // Move constructor
        StringMatrix::StringMatrix(StringMatrix &&m){	
            //std::cout << "Move constructor called" << std::endl;
            _rows = m._rows;
            _columns = m._columns;
            _matrix_data = m._matrix_data;
            m._rows = 0;
            m._columns = 0;
            m._matrix_data = nullptr;
        }	
        // Destructor
        StringMatrix::~StringMatrix(){
            delete[] _matrix_data;
            _rows = 0;
            _columns = 0;
            // Uncomment if you want to make sure that the object is deconstructed (I like my terminal clean)
            //std::cout << "Destructor was called" << std::endl;
        }
        
        // Access functions
        int StringMatrix::get_rows() const {return _rows;} // Return number of rows
        int StringMatrix::get_cols() const {return _columns;} // Return number of columns

        // Return array's position of the value by putting its matrix coordinates 
        int StringMatrix::index(uint32_t m, uint32_t n) const{
            if(m>_rows || n>_columns){
                std::cout << "Index out of range" << std::endl;
                exit(1);
            }
            return (n-1)+(m-1)*_columns;
        } // Return position in array of element (m,n)
        // Display the data in a nice way
        void StringMatrix::show(){
            for(int i=0; i<_rows; i++){
                std::cout<< "| ";
                for(int j=0; j<_columns;j++){
                    std::cout << _matrix_data[i*_columns + j] << " ";
                }
                std::cout<< "|";
                std::cout << std::endl;
            }
        }

    

        // For easy return of M_(mn) item of the matrix M
        std::string& StringMatrix::operator()(uint32_t m, uint32_t n){
            // input is checked inside index() method
            return _matrix_data[index(m,n)];
        }

        // To return m-th element of the array
        std::string& StringMatrix::operator[](uint32_t m){
            if(m>_rows*_columns-1){
                std::cout << "Index out of range" << std::endl;
                exit(1);
            }
            return _matrix_data[m];
        }
        
        // Copy assignment operator
        StringMatrix& StringMatrix::operator=(StringMatrix &m) noexcept{
            // No need to move when the given input is exactly the same object 
            if (this == &m) {
                return *this;
            }
            _rows = m._rows;
            _columns = m._columns;
            _matrix_data = nullptr;
            delete[] _matrix_data;
            _matrix_data = new std::string[_rows*_columns];
            for(int i = 0; i < _rows*_columns; i++){
                _matrix_data[i] = m._matrix_data[i];
            }
            return *this;
        }

        // Move assignment operator
        StringMatrix& StringMatrix::operator=(StringMatrix &&m) noexcept{
            //std::cout << "Move assignment operator called" << std::endl;
            // No need to move when the given input is exactly the same object 
            if (this == &m) {
                return *this;
            }
            std::swap(_rows, m._rows);
            std::swap(_columns, m._columns);
            std::swap(_matrix_data, m._matrix_data);
            return *this;
        }

    std::ostream &operator<<(std::ostream &os, StringMatrix &m){
        os << std::endl;
        // I have written this method initially so I'm using it, no point of rewritting the code
        m.show();
        return os;
    }
    std::istream &operator>>(std::istream &is, StringMatrix &m){
        int r{0};
        int c{0};
        std::cout << "Number of rows: ";
        is >> r;
        std::cout << "Number of columns: ";
        is >> c;
        
        // Simple validation, return unchanged matrix
        if(r<1 || c<1){
            std::cout << "Matrix of this dimension cannot be created" << std::endl;
            return is;
        }
        m._rows = r;
        m._columns = c;
        m._matrix_data = new std::string[m._rows*m._columns];
        for(int i = 1; i<=m._rows; i++){
            for(int j = 1; j<=m._columns; j++){
                std::cout << "Enter value for index (" << i <<"," <<j <<"): ";
                is >> m._matrix_data[m.index(i,j)];
            }
        }
        return is;
    }

}