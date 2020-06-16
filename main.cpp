#include "MyMatrix.h"
#include "MyVector.h"
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
    vector3.display_elements();

    //Vector from for loop
    MyVector<double> vector4;
    for (double i=1; i<=5; i++)
    {
        vector4.push(i);
    }
    vector4.display_elements();

    //Copy vector
    MyVector<double> vector5 = vector4;
    cout << "Vector5";
    vector5.display_elements();

    //Scalar multiplication
    double scalar = 15;
    MyVector<double> vector6 = vector5 * scalar;
    MyVector<double> vector7 = scalar * vector5;
    cout << "Vector6";
    vector6.display_elements();
    cout << "Vector7";
    vector7.display_elements();

    //Vector addition commutative
    MyVector<double> vector8 = vector6 + vector7;
    MyVector<double> vector9 = vector7 + vector6;
    cout << "Vector8";
    vector8.display_elements();
    cout << "Vector9";
    vector9.display_elements();

    //Matrix
    MyMatrix<MyVector<double>> matrix0();
    MyMatrix<MyVector<double>> matrix1(25, 1);
    MyVector<double> a = {1.0, 2, 3.0};
    MyVector<double> b = {1.0, 2.0, 3.0};
    MyVector<double> c = {1.0, 2.0, 3.0};
    MyVector<double> d = {100, 2.0, 3.0};
    MyMatrix<MyVector<double>> matrix2 = {a, b, c};

    //MyMatrix<MyVector<double>> matrix2 = {vector5, vector6, vector7, vector8};
    cout << "Matrix2";
    matrix2.display_elements();
    cout << "vector4\n";
    vector4.display_elements();

    //Vector and Matrix multiplication
    MyVector<double> my = matrix2 * d;

    cout << "Product vector";
    my.display_elements();


    delete[] &vector6;
    delete[] &vector7;
    delete[] &vector8;
    delete[] &vector9;
    delete[] &my;

    return 0;
};
