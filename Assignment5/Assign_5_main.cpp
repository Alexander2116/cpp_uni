/*============================================================
** UTF-8
**
** Assignment 5  (Deadline: 24/03/2023)
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
**         :
**
** Date:  17 March 2023
**
===========================================================*/


//=== includes ===
#include<iostream>
#include<cmath>

//=== defined classes ===
class Matrix
{
	// Friends
	friend std::ostream & operator<<(std::ostream &os, const Matrix &mat);
private:
	int _rows{0}, _columns{0};
	double *_matrix_data{nullptr}; // it will be double[] 1D array/list
public:
	// Default constructor
	Matrix()= default;
	// Parameterized constructors
	Matrix(int m, int n){
		if(m<1 && n<1){
			std::cout<<"Cannot create the matrix"<<std::endl;
			exit(1);
		}
		_rows = m;
		_columns = n;
		_matrix_data = new double[m*n];
		for(int i=0; i<m*n; i++){
			_matrix_data[i] = 0;
		}
	}
	Matrix(double *p, int m, int n){
		if(m<1 && n<1){
			std::cout<<"Cannot create the matrix"<<std::endl;
			exit(1);
		}
		_rows = m;
		_columns = n;
		_matrix_data = new double[m*n];
		for(int i=0; i < m*n; i++){
			_matrix_data[i] = p[i];
		}
	}
	// Copy constructor

	// Move constructor

	// Destructor
	~Matrix(){delete[] _matrix_data; std::cout << "Destructor was called" << std::endl;}
	
	// Access functions
	int get_rows() const{
		return _rows;
	} // Return number of rows
	int get_cols() const{
		return _columns;
	} // Return number of columns
	int index(int m, int n) const{
		return (n-1)+(m-1)*_columns;
	} // Return position in array of element (m,n)
	
	void show(){
		for(int i=0; i<_rows; i++){
			std::cout<< "| ";
			for(int j=0; j<_columns;j++){
				std::cout << _matrix_data[i*_columns + j] << " ";
			}
			std::cout<< "|";
			std::cout << std::endl;
		}
	}
	
	// Determinant Expansion by Minors
	double determinant(){
		return 0;
	}
	
	double& operator[](int m){
		return _matrix_data[m];
	}
	
	Matrix operator+(const Matrix& m){
		if(m._rows == _rows && m._columns == _columns){
			double *temp;
			temp = new double[_columns*_rows];
			for(int i=0; i<_rows+_columns; i++){
				temp[i] = m._matrix_data[i] + _matrix_data[i];
			}
			return Matrix(temp, _rows,_columns);
		}
		else{
			// Cannot add these matrices
			exit(1);
		}
	}

	Matrix operator-(const Matrix& m){
		Matrix result_m;
		return result_m;
	}
	Matrix operator*(const Matrix& m){
		double u[9] = {5,5,5,6,6,6,4,4,4};
		Matrix result_m = Matrix(u,3,3);
		return result_m;
	}
	Matrix operator^(int n){
		if(n>0){
			
			Matrix result_matrix = Matrix(_matrix_data,_rows,_columns);
			Matrix original = Matrix(_matrix_data,_rows,_columns);

			for(int i = 1; i < n; i++){
				result_matrix = result_matrix*original;
			}
			return result_matrix;
		}
		else{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		
	}
};

// Functions to overload (arthmetic operations):
Matrix operator+(const Matrix& m1, const Matrix& m2){
	Matrix temp;
	return temp;
}
Matrix operator-(const Matrix& m1, const Matrix& m2){
	Matrix temp;
	return temp;
}
Matrix operator*(const Matrix& m1, const Matrix& m2){
	Matrix temp;
	return temp;
}
Matrix operator*(const Matrix& m, double a){
	Matrix temp;
	return temp;
}
Matrix operator*(double a, const Matrix& m){
	Matrix temp;
	return temp;
}
Matrix operator/(const Matrix& m, double a){
	Matrix temp;
	return temp;
}
//=== defined functions ===
// Functions to overload: << and >> operator for complex



//=== main ===
int main(){
    Matrix m = Matrix(3,3);
	double p[9] = 
		{1,1,1,
		2,2,2,
		3,3,3};
	Matrix n = Matrix(p,3,3);
	n.show();
	Matrix mm;
	mm = n^2;
	m.show();
    return 0;
}