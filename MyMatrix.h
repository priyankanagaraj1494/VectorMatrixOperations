// TODO
// Move declarations to header files
// Create author
#ifndef MYMATRIX_H
#define MYMATRIX_H

#include "MyVector.h"

template<class MyVector> 
class MyMatrix
{
private:
    /* data */
    int rows;
    int columns;
    MyVector* start;
public:
    // Default constructor
	MyMatrix();
    // Constructor with parameter
    MyMatrix(int m, int n);
    // Constructor with parameter
    MyMatrix(int m, double value);
    // Constructor with array of vectors
    MyMatrix(int m, MyVector* vectors);
    // Brace-enclosed initializer list constructor
	MyMatrix(std::initializer_list<MyVector> list);
    // Rule of three
    // Copy constructor
	MyMatrix(const MyMatrix& source);
    // Overload assignment
    MyMatrix<MyVector>& operator=(const MyMatrix<MyVector>& source);
    // Destructor
    ~MyMatrix();

    // Display elements of Matrix
	void display_elements();
    //Vector multiplication with matrix
    template<class U>
	friend U& operator*(MyMatrix<U> &matrix, U vector);
    //to access single elements
	MyVector& operator[](const unsigned &index);
    // Get current capacity
	int get_rows();
};

// Default constructor
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix()
        :rows(1), columns(1), start(new MyVector[1])
{}

// Constructor with one parameter
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(int m, double value)
        :rows(m), columns(m), start(new MyVector[m])
{
    for (int index=0; index < rows; ++index)
    {
        MyVector vector(columns, value);
        start[index] = vector;
    }
}

// Constructor with two parameters
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(int m, int n)
        :rows(m), columns(n), start(new MyVector[m])
{
    for (int index=0; index < rows; ++index)
    {
        MyVector vector(columns, 0.0);
        start[index] = vector;
    }
}

// Constructor with array of vectors
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(int m, MyVector* vectors)
        :rows(m), columns(0), start(new MyVector[rows])
{
    int max_length=0;
    for (int index = 0; index < rows; ++index)
    {
        if (vectors[index].get_current_capacity() >= max_length)
            max_length = vectors[index].get_current_capacity();
        else
        {
            for (int i=vectors[index].get_current_capacity(); i < max_length; ++i)
            {
                vectors[index].push(0);
            }
        }
        start[index] = vectors[index];
    } 
    columns = max_length;
}

// Brace-enclosed initializer list constructor
template<class MyVector>
MyMatrix<MyVector>::MyMatrix(std::initializer_list<MyVector> list)
        :rows(list.size()), start(new MyVector[list.size()])
{
	int index = 0;
    int max_length=0;
    columns =list.begin()->get_current_capacity();
	for (auto i = list.begin(); i != list.end(); i++) 
    {
        if (i->get_current_capacity() != columns)
            cout << "Error: Vectors are of unequal length.";
		start[index] = *i;
		++index;
    }
}

// Copy constructor
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(const MyMatrix& source)
        :rows(source.rows), columns(source.columns), start(new MyVector[source.columns])
{
    for (int index = 0; index < source.rows; ++index)
		start[index] = source.start[index];

}

template<class MyVector> 
inline MyMatrix<MyVector>& MyMatrix<MyVector>::operator=(const MyMatrix<MyVector>& source)
{
    // If assigning the same object
	if (this == &source) 
        return *this;	

	// If current vector size is greater than source vector size, no allocation
	if (source.rows <= rows)
	{
		for (int index = 0; index < source.rows; ++index)
		{
			start[index] = source.start[index];
			rows = source.rows;
			return *this;
		}
	}

    // If current vector size is less than source vector size, new dynamic allocation

	MyVector* new_start = new MyVector[source.rows];

	for (int index = 0; index < source.rows; ++index)
		new_start[index] = source.start[index];

	delete[] start;
	rows = source.rows;
	start = new_start;
	return *this;
}

// Destructor
template<class MyVector> 
MyMatrix<MyVector>::~MyMatrix()
{
    delete [] start;
}

// Display elements of Matrix
template<class MyVector> 
void MyMatrix<MyVector>::display_elements()
{
	cout << "[";
    cout << std::endl;
    for (int index = 0; index < rows; ++index)
    {
        start[index].display_elements();
    }
    cout << "]";
	cout << std::endl;
}

//to access single elements
template<class MyVector>
MyVector& MyMatrix<MyVector>::operator[](const unsigned &index)
{
    return this->start[index];
}

//to access the rows of matrix
template<class MyVector>
int MyMatrix<MyVector>::get_rows()
{
    return this->rows;
}

// Vector multiplication
template<class MyVector>
MyVector& operator*(MyMatrix<MyVector> &matrix, MyVector vector)
{
	MyVector* product = new MyVector(matrix.get_rows(), 0.0);
    if (matrix.columns != vector.get_size())
    {
        cout << "Matrix and vector multiplication not possible since shapes do not match\n";
        return *product;
    }
	for (int index = 0; index < matrix.get_rows(); ++index)
		(*product)[index] = vector * matrix[index];
	return *product;
}

#endif