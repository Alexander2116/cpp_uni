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
**         : Using uint32_t (or size_t) and putting negative value mean value = size(uint32_t)-value.
				so user can put negative value but it will be turned into some large (2^32 - 1 - VALUE) positive value
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
	friend std::ostream& operator<<(std::ostream &os, Matrix &m);
	friend std::istream& operator>>(std::istream &is, Matrix &m);
private:
	uint32_t _rows{0}, _columns{0};
	double *_matrix_data{nullptr}; // it will be double[] 1D array/list
public:
	// Default constructor
	Matrix()= default;
	// Parameterized constructors
	// Using (int) instead of (uint32_t) makes it easier to detect negative value (by the cost of memory)
	Matrix(int m, int n){
		if(m<1 || n<1){
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
	// Using (int) instead of (uint32_t) makes it easier to detect negative value (by the cost of memory)
	Matrix(double *p, int m, int n){
		if(m<1 || n<1){
			std::cout<<"Cannot create the matrix"<<std::endl;
			exit(1);
		}
		_rows = m;
		_columns = n;
		// Alternatively; _matrix_data = p;
		_matrix_data = new double[m*n];
		for(int i=0; i < m*n; i++){
			_matrix_data[i] = p[i];
		}
	}
	// Copy constructor
	Matrix(const Matrix &m){
		// Just copy the data
		_rows = m._rows;
		_columns = m._columns;
		_matrix_data = m._matrix_data;
	}
	// Move constructor
	Matrix(Matrix &&m):
		_rows(std::move(m._rows)),
		_columns(std::move(m._columns)),
		_matrix_data(std::move(m._matrix_data))
	{	
		//std::cout << "Move constructor called" << std::endl;
		m._matrix_data = NULL;
	}	
	// Destructor
	~Matrix(){
		// Assigning NULL first is necessary to avoid "Exception: unknown signal"
		// Possible that it tries to remove uninitialized object but in default _matarix_data=nullptr, STRANGE
		_matrix_data = NULL;
		delete[] _matrix_data;
		// Uncomment if you want to make sure that the object is deconstructed (I like my terminal clean)
		//std::cout << "Destructor was called" << std::endl;
	}
	
	// Access functions
	int get_rows() const {return _rows;} // Return number of rows
	int get_cols() const {return _columns;} // Return number of columns

	int index(uint32_t m, uint32_t n) const{
		if(m>_rows || n>_columns){
			std::cout << "Index out of range" << std::endl;
			exit(1);
		}
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

	// Gives cropped matrix with removed m-th row and n-th column of the current matrix
	Matrix crop(uint32_t m, uint32_t n){
		if(m<1 || n<1 || m>_rows || n>_columns){
			std::cout << "Crop(): row or column index must be greater than 0" << std::endl;
			exit(1);
		}
		double *temp;
		uint32_t new_m{_rows-1};
		uint32_t new_n{_columns-1};

		temp = new double[new_m*new_n];
		// Temporary variables used in the loop
		uint32_t curr_idx{0};
		uint32_t temp_idx{0};
		// m-th row starts at "(m-1)*columns" index and goes to "(m-1)*columns + columns" every 1 increment
		// n-th columns starts at "(n-1)"" index and goes to "(rows-1)*columns + (n-1)" every "columns" increment
		// It's easier to create new array than to copy and remove item from an existing array
		for(int i = 0; i<_rows; i++){
			for(int j = 0; j<_columns; j++){
				curr_idx = i*_columns + j;
				// Conditions for removed column/row as described above 
				if(!((m-1)*_columns <= curr_idx && curr_idx < m*_columns) && !(curr_idx == (i*_columns+n-1))){
					//std::cout << curr_idx;
					temp[temp_idx] = _matrix_data[curr_idx];
					temp_idx++;
				}
			}
		}
		return Matrix(temp, new_m, new_n);
	}
	
	// Determinant Expansion by Minors - recursion alg.
	// https://mathworld.wolfram.com/DeterminantExpansionbyMinors.html
	double determinant(){
		// if square and 2x2
		if(_rows*_columns == 1){return _matrix_data[0];}
		if(_rows == _columns && _rows == 2){
			return _matrix_data[index(1,1)]*_matrix_data[index(2,2)] - _matrix_data[index(1,2)]*_matrix_data[index(2,1)];
		}
		// Could also do a manual if statement for 3x3
		// if(_row == _columns && _rows == 3){}
		// Actual code using recursion
		if(_rows == _columns){
			double det{0};
			Matrix temp_m = Matrix(_matrix_data, _rows, _columns);
			// Fixed row, row = 1 (first row), just change the column
			for(int i = 1; i <= _columns; i++){
				det += std::pow(-1,1+i)*_matrix_data[index(1,i)]*temp_m.crop(1,i).determinant();
			}
			return det;
		}
		else{
			std::cout << "Cannot calculate determinant for this matrix, returning 0." << std::endl;
			return 0;
		}
	}

	// For easy return of M_(mn) item of the matrix M
	double& operator()(uint32_t m, uint32_t n){
		if(m>_rows || n>_columns){
			std::cout << "Index out of range" << std::endl;
			exit(1);
		}
		return _matrix_data[index(m,n)];
	}

	// To return m-th element of the array
	double& operator[](uint32_t m){
		if(m>_rows*_columns-1){
			std::cout << "Index out of range" << std::endl;
			exit(1);
		}
		return _matrix_data[m];
	}
	
	// Copy assignment operator
	Matrix& operator=(Matrix &m) noexcept{
		// No need to move when the given input is exactly the same object 
		if (this == &m) {
        	return *this;
    	}
		_rows = m._rows;
		_columns = m._columns;
		_matrix_data = nullptr;
		_matrix_data = m._matrix_data;
		return *this;
	}

	// Move assignment operator
	Matrix& operator=(Matrix &&m) noexcept{
		// No need to move when the given input is exactly the same object 
		if (this == &m) {
        	return *this;
    	}
		_rows = m._rows;
		_columns = m._columns;
		_matrix_data = nullptr;
		_matrix_data = m._matrix_data;
		m._rows = 0;
		m._columns = 0;
		m._matrix_data = nullptr;
		return *this;
	}

	Matrix operator+(const Matrix &m){
		if(m._rows == _rows && m._columns == _columns){
			double *temp;
			temp = new double[_columns*_rows];
			for(int i=0; i<_rows*_columns; i++){
				temp[i] = m._matrix_data[i] + _matrix_data[i];
			}
			return Matrix(temp, _rows, _columns);
		}
		else{
			// Cannot add these matrices
			std::cout << "Matrices cannot be added together" << std::endl;
			exit(1);
		}
	}

	Matrix operator-(const Matrix &m){
		if(m._rows == _rows && m._columns == _columns){
			double *temp;
			temp = new double[_columns*_rows];
			for(int i=0; i<_rows*_columns; i++){
				temp[i] = _matrix_data[i] - m._matrix_data[i];
			}
			return Matrix(temp, _rows, _columns);
		}
		else{
			std::cout << "Matrices cannot be subtracted together" << std::endl;
			exit(1);
		}
	}

	/* Let a11 be a new matrix (multiplication of M1 and M2) then a11 = sum M1_(1i)*M2_(i1)
	a12 = sum M1_(1i)*M2(i2)... a21 = sum M1_(2i)*M2_(i1)
	So it can be generalized by introducing i, j, k increments
	i goes for new Matrix row length (from 0 to length-1)
	j goes for new Matrix column length (from 0 to length-1)
	k goes for old Matrix column/row length (from 0 to length-1)
	a_ij = sum(k) M1_(jk)*M2_(ki)
	Position of a_ij is given by a position in 1D array
	a_11 = [0], a_12 = [1], ... a_21 = [columns], a_22 = [columns+1].. a_ij = [i*columns + j]
	*/
	Matrix operator*(const Matrix &m){
		// This is a array for the NEW Matrix (the result of multiplication)
		double *temp;
		temp = new double[_rows * m._columns];
		Matrix result_m;
		if(m._rows == _columns){
			// Go for i-th row of the New Matrix
			for(int i = 0; i<_rows; i++){
				// Go for j-th columns
				for(int j = 0; j<m._columns; j++){
					// Do the rows*columns summation
					for(int k = 0; k<_columns; k++){
						temp[i*m._columns+j] += _matrix_data[i*_columns + k] * m._matrix_data[j + k*m._columns];
						// Could also use index to do that, but I like it more like this
					}
				}
			}
			result_m = Matrix(temp, _rows, m._columns);
		}
		else{
			std::cout << "cannot be multiplied" << std::endl;
			//exit(1);
			return Matrix();
		}
		return result_m;
	}

	Matrix operator*(const double &a){
		// This is a array for the NEW Matrix (the result of multiplication)
		double *temp;
		temp = new double[_rows * _columns];
		Matrix result_m;
		// Go for i-th row of the New Matrix
		for(int i = 0; i<_rows*_columns; i++){
			temp[i] = _matrix_data[i]*a;
		}
		result_m = Matrix(temp, _rows, _columns);
		return result_m;
	}

	Matrix operator^(int n){
		if(n>0 && _matrix_data != nullptr){
			Matrix result_matrix = Matrix(_matrix_data,_rows,_columns);
			Matrix original = Matrix(_matrix_data,_rows,_columns);
			// Do multiplication by the original matrix n-1 times
			for(int i = 1; i < n; i++){
				result_matrix = result_matrix*original;
			}
			return result_matrix;
		}
		else{
			std::cout << "Error while rising matrices to the power of "<< n << std::endl;
			//exit(1);
			return Matrix();
		}
		
	}
};

// === Functions to overload ===
Matrix operator+(const Matrix &m1, const Matrix &m2){
	return m1+m2;
}
Matrix operator-(const Matrix &m1, const Matrix &m2){
	return m1-m2;
}
Matrix operator*(const Matrix &m1, const Matrix &m2){
	return m1*m2;
}
Matrix operator*(const double a, Matrix &m){
	return m*a;
}
std::ostream &operator<<(std::ostream &os, Matrix &m){
	os << std::endl;
	// I have written this method initially so I'm using it, no point of rewritting the code
	m.show();
  	return os;
}
std::istream &operator>>(std::istream &is, Matrix &m){
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
	m._matrix_data = new double[m._rows*m._columns];
	for(int i = 1; i<=m._rows; i++){
		for(int j = 1; j<=m._columns; j++){
			std::cout << "Enter value for index (" << i <<"," <<j <<"): ";
			is >> m._matrix_data[m.index(i,j)];
		}
	}
	return is;
}

//=== main ===
int main(){
	// --- Test Data ---
	//  The arrays of required matrixes, placed like the matrix should look like
	double a1[9] = 
		{1,2,3,
		9,8,7,
		4,2,6};
	double a2[9] = 
		{5,5,4,
		1,2,3,
		6,9,8};
	double a3[6] = 
		{3,4,1,
		2,5,6};

	Matrix A(a1,3,3);
	Matrix B(a2,3,3);
	Matrix C(a3,2,3);

	// A+B,A-B,A*B,C*B,B*C
	std::cout << "A+B=";
	Matrix add(A+B);
	std::cout << add << std::endl;

	std::cout << "A-B=";
	Matrix sub(A-B);
	std::cout << sub << std::endl;

	std::cout << "A*B=";
	Matrix AB(A*B);
	std::cout << AB << std::endl;

	std::cout << "C*B=";
	Matrix CB(C*B);
	std::cout << CB << std::endl;

	std::cout << "B*C=";
	Matrix BC(B*C);
	std::cout << BC << std::endl;

	// Determinants
	std::cout << "det(A)= " << A.determinant() << std::endl; // results should be -60 (online matrix calculator)
	std::cout << "det(B)= " << B.determinant() << std::endl << std::endl; // -17

	// copy A
	Matrix cA(A);
	// modify A
	A = A^2;
	// Output copy and modified A
	std::cout << "Copied A:" << cA << std::endl;
	std::cout << "Modified A:" << A << std::endl;

	// move A

    return 0;
}