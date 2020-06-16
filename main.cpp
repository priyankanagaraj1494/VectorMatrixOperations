#include "MyMatrix.cpp"
#include "MyVector.cpp"
#include <iostream>
using std::cout;

int main() {

    // Vector of size 1, no element
    MyVector<double> vector0;
    cout << "Vector of zero elements\n";
    vector0.display_elements();

    // Vector of arbitrary size with initial values
    MyVector<double> vector1(25, 5.0);
    cout << "Vector initialized with same values for all elements\n";
    vector1.display_elements();

    // Vector from array
    double values[] = {1.0, 2.0, 3.0, 4.0};
    MyVector<double> vector2(4, values);
    cout << "Vector created from array\n";
    vector2.display_elements();

    // Vector created from brace-enclosed initializer list
    MyVector<double> vector3 = {1.0, 2.0, 3.0};
    cout << "Vector created from brace-enclosed initializer list\n";
    vector3.display_elements();

    //Vector from for loop
    MyVector<double> vector4;
    for (double i=1; i<=5; i++)
    {
        vector4.push(i);
    }
    cout << "Vector created from loop\n";
    vector4.display_elements();

    //Copy vector
    MyVector<double> vector5 = vector4;
    cout << "Vector created from copy constructor\n";
    vector5.display_elements();

    //scalar multiplication of Vector
    double scalar = 4;
    MyVector<double> vector6 = vector5 * scalar;
    MyVector<double> vector7 = scalar * vector5;
    cout << "Commutative multiplication of vector with a scalar\n";
    vector6.display_elements();
    vector7.display_elements();

    //Vector addition
    MyVector<double> vector8 = vector6 + vector7;
    MyVector<double> vector9 = vector7 + vector6;
    cout << "Commutative addition of vectors\n";
    vector8.display_elements();
    vector9.display_elements();

    /************        MATRIX     ****************/
    //Creation of matrix will no elements
    MyMatrix<MyVector<double>> matrix0();

    //Creation of square Matrix with input assize and initial values
    MyMatrix<MyVector<double>> matrix1(25, 1);

    //Creation of matrix with input as a list of vectors
    MyVector<double> row1 = {1.0, 2, 3.0};
    MyVector<double> row2 = {1.0, 5.0, 3.0};
    MyVector<double> row3 = {4.0, 2.0, 3.1};
    MyVector<double> vectorMul = {10, 2.5, 3.0};
    MyMatrix<MyVector<double>> matrix2 = {row1, row2, row3};
    cout << "Matrix(matrix2) created from list of elements\n";
    matrix2.display_elements();
    cout << "vectorMul\n";
    vectorMul.display_elements();

    //Vector and Matrix multiplication
    MyVector<double> product = matrix2 * vectorMul;
    cout << "Product vector of matrix2 and vectorMul\n";
    product.display_elements();

    //append a vector/row to matrix
    MyVector<double> row4 = {5, 1, 3.1};
    matrix2.push(row4);
    cout << "Appended matrix\n";
    matrix2.display_elements();

    // Scalar multiplication
    cout << "Multiplication of matrix2 with a scalar: product1 & product2\n";
    MyMatrix<MyVector<double>>* product1 = matrix2 * 3.0;
    (*product1).display_elements();

    MyMatrix<MyVector<double>>* product2 = 3.0 * matrix2;
    (*product2).display_elements();

    //Addition of matrices
    MyMatrix<MyVector<double>>* sum = (*product1) + (*product2);
    cout << "Addition of two matrices(product1 & product2)\n";
    (*sum).display_elements();

    delete[] &vector6;
    delete[] &vector7;
    delete[] &vector8;
    delete[] &vector9;
    delete[] &product;
    delete[] &product1;
    delete[] &product2;
    delete[] &sum;

    return 0;
};
