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
    unsigned int rows;
    unsigned int columns;
    MyVector* start;
    unsigned int current_capacity;
public:
    // Default constructor
	MyMatrix();
    // Constructor with parameter
    MyMatrix(unsigned int m, unsigned int n, double value);
    // Constructor with parameter
    MyMatrix(unsigned int m, double value);
    // Constructor with array of vectors
    MyMatrix(unsigned int m, MyVector* vectors);
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

    // push row elements to matrix
    void push(MyVector element);

    // delete last element
    void pop();

    //Vector multiplication with matrix
    template<class U>
	friend U& operator*(MyMatrix<U> &matrix, U vector);

    //Scalar multiplication of matrix
    template<class U>
    friend MyMatrix<U>* operator*(MyMatrix<U> &matrix, double scalar);

    //Scalar multiplication of matrix commutative
    template<class U>
    friend MyMatrix<U>* operator*(double scalar, MyMatrix<U> &matrix);

    //Matrix addition
    template<class U>
    friend MyMatrix<U>* operator+( MyMatrix<U> &matrix1, MyMatrix<U> &matrix2);

    //to access single elements
	MyVector& operator[](const unsigned &index);

    // Get rows
	unsigned int get_rows();

    // Get columns
	unsigned int get_columns();
};

// Default constructor
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix()
        :rows(1), columns(1), start(new MyVector[1]), current_capacity(1)
{}

// Constructor with one parameter
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(unsigned int m, double value)
        :rows(m), columns(m), start(new MyVector[m]), current_capacity(m)
{
    for (unsigned int index=0; index < rows; ++index)
    {
        MyVector vector(columns, value);
        start[index] = vector;
    }
}

// Constructor with two parameters
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(unsigned int m, unsigned int n, double value)
        :rows(m), columns(n), start(new MyVector[m]), current_capacity(m)
{
    for (unsigned int index=0; index < rows; ++index)
    {
        MyVector vector(columns, value);
        start[index] = vector;
    }
}

// Constructor with array of vectors
template<class MyVector> 
MyMatrix<MyVector>::MyMatrix(unsigned int m, MyVector* vectors)
        :rows(m), columns(0), start(new MyVector[rows]), current_capacity(m)
{
    unsigned int max_length=0;
    for (unsigned int index = 0; index < rows; ++index)
    {
        if (vectors[index].get_current_capacity() >= max_length)
            max_length = vectors[index].get_current_capacity();
        else
        {
            for (unsigned int i=vectors[index].get_current_capacity(); i < max_length; ++i)
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
        :rows(list.size()), start(new MyVector[list.size()]), current_capacity(list.size())
{
	unsigned int index = 0;
    unsigned int max_length=0;
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
        :rows(source.rows), columns(source.columns), start(new MyVector[source.columns]), current_capacity(source.rows)
{
    for (unsigned int index = 0; index < source.current_capacity; ++index)
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
		for (unsigned int index = 0; index < source.current_capacity; ++index)
		{
			start[index] = source.start[index];
			rows = source.rows;
            current_capacity = source.current_capacity;
			return *this;
		}
	}

    // If current vector size is less than source vector size, new dynamic allocation

	MyVector* new_start = new MyVector[source.rows];

	for (unsigned int index = 0; index < source.current_capacity; ++index)
		new_start[index] = source.start[index];

	delete[] start;
	rows = source.rows;
    current_capacity = source.current_capacity;
	start = new_start;
	return *this;
}

// Destructor
template<class MyVector> 
MyMatrix<MyVector>::~MyMatrix()
{
    delete [] start;
}

template<class MyVector> 
void MyMatrix<MyVector>::push(MyVector element)
{
	// If the vector is full, create a new vector in heap
	if (rows == current_capacity)
	{
		MyVector* temp = new MyVector[rows + 1];
		for (unsigned int index = 0; index < rows; ++index)
		{
			temp[index] = start[index];
		}
		delete[] start;
		rows += 1;
		start = temp; 
	}
	start[current_capacity] = element;
	current_capacity++;
}

// function to delete last element 
template<class MyVector>
void MyMatrix<MyVector>::pop() 
{ 
    current_capacity--; 
} 


// Display elements of Matrix
template<class MyVector> 
void MyMatrix<MyVector>::display_elements()
{
	cout << "[";
    cout << std::endl;
    for (unsigned int index = 0; index < rows; ++index)
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
unsigned int MyMatrix<MyVector>::get_rows()
{
    return this->rows;
}

//to access the columns of matrix
template<class MyVector>
unsigned int MyMatrix<MyVector>::get_columns()
{
    return this->columns;
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
	for (unsigned int index = 0; index < matrix.get_rows(); ++index)
		(*product)[index] = vector * matrix[index];
	return *product;
}

// Scalar multiplication
template<class MyVector>
MyMatrix<MyVector>* operator*(MyMatrix<MyVector> &matrix, double scalar)
{
	MyMatrix<MyVector>* product = new MyMatrix<MyVector>();
    product->pop();
	for (unsigned int index = 0; index < matrix.get_rows(); ++index)
    {
        MyVector temp = scalar * matrix.start[index];
        product->push(temp);
    }
	return product;
}

// Scalar multiplication commutative
template<class MyVector>
MyMatrix<MyVector>* operator*(double scalar, MyMatrix<MyVector> &matrix)
{
	return matrix * scalar;
}

// Matrix addition
template<class MyVector>
MyMatrix<MyVector>* operator+(MyMatrix<MyVector> &matrix1, MyMatrix<MyVector> &matrix2)
{
    MyMatrix<MyVector>* sum = new MyMatrix<MyVector>();
    sum->pop();
    if ((matrix1.get_rows() != matrix2.get_rows()) && (matrix1.get_columns() != matrix2.get_columns()))
    {
        cout << "Matrices size do not match! Hence cannot be added. \n";
        return sum;
    }
	for (unsigned int index = 0; index < matrix1.get_rows(); ++index)
    {
        MyVector temp = matrix1[index] + matrix2[index];
        sum->push(temp);
    }
	return sum;
}

#endif