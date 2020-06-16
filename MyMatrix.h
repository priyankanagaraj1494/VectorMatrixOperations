// TODO
// Move declarations to header files
// Create author
#ifndef MYMATRIX_H
#define MYMATRIX_H

#include "MyVector.h"

template <class MyVector>
class MyMatrix
{
private:
    /* data */
    unsigned int rows;
    unsigned int columns;
    MyVector *start;
    unsigned int current_capacity;

public:
    // Default constructor
    MyMatrix();
    // Constructor with parameter
    MyMatrix(unsigned int m, unsigned int n, double value);
    // Constructor with parameter
    MyMatrix(unsigned int m, double value);
    // Brace-enclosed initializer list constructor
    MyMatrix(std::initializer_list<MyVector> list);
    // Rule of three
    // Copy constructor
    MyMatrix(const MyMatrix &source);
    // Overload assignment
    MyMatrix<MyVector> &operator=(const MyMatrix<MyVector> &source);
    // Destructor
    ~MyMatrix();

    // Display elements of Matrix
    void display_elements();

    // push row elements to matrix
    void push(MyVector element);

    // delete last element
    void pop();

    //Vector multiplication with matrix
    template <class U>
    friend U &operator*(MyMatrix<U> &matrix, U vector);

    //Scalar multiplication of matrix
    template <class U>
    friend MyMatrix<U> *operator*(MyMatrix<U> &matrix, double scalar);

    //Scalar multiplication of matrix commutative
    template <class U>
    friend MyMatrix<U> *operator*(double scalar, MyMatrix<U> &matrix);

    //Matrix addition
    template <class U>
    friend MyMatrix<U> *operator+(MyMatrix<U> &matrix1, MyMatrix<U> &matrix2);

    //to access single elements
    MyVector &operator[](const unsigned &index);

    // Get rows
    unsigned int get_rows();

    // Get columns
    unsigned int get_columns();
};
#endif