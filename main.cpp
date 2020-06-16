#include "MyMatrix.h"
#include "MyVector.h"
#include <iostream>
using std::cout;

int main() {

    // Vector of size 1, no element
    MyVector<double> vector0;
    // prints empty vector
    //vector0.display_elements();

    // Vector of arbitrary size with initial values
    MyVector<double> vector1(25, 0.0);
    // Prints the vector with initial values
    //vector1.display_elements();

    // Vector from array
    double values[] = {1.0, 2.0, 3.0, 4.0};
    MyVector<double> vector2(4, values);
    vector2.display_elements();

    //Vector from for loop
    MyVector<double> vector3;
    for (double i=0; i<25; i++)
    {
        vector3.push(i);
    }
    //vector3.display_elements();

    //Copy vector
    MyVector<double> vector4 = vector3;
    //vector4.display_elements();

    //Scalar multiplication
    double scalar = 15;
    MyVector<double> vector5 = vector4 * scalar;
    MyVector<double> vector6 = scalar * vector4;
    //vector5.display_elements();
    //vector6.display_elements();

    //Vector addition
    MyVector<double> vector7 = vector5 + vector6;
    MyVector<double> vector8 = vector6 + vector5;
    //vector7.display_elements();
    //vector8.display_elements();

    //Matrix
    MyMatrix<MyVector<double>> matrix0();
    MyMatrix<MyVector<double>> matrix1(25);
    MyVector<double> vectors[] = {vector5, vector6, vector7, vector8};
    MyMatrix<MyVector<double>> matrix2(4, vectors);
    // matrix2.display_elements();

    //Vector and Matrix multiplication
    MyVector<double> vector9 = matrix2 * vector3;
    //vector9.display_elements();

    double valuesa[] = {1.0, 2.0, 3.0};
    double valuesb[] = {1.0, 2.0, 3.0};
    double valuesc[] = {1.0, 2.0, 3.0};
    double valuesd[] = {1.0, 2.0, 3.0};

    MyVector<double> vectora(3, valuesa);
    vectora.display_elements();
    MyVector<double> vectorb(3, valuesb);
    MyVector<double> vectorc(3, valuesc);
    MyVector<double> vectord(3, valuesd);
    MyVector<double> vectorsm[] = {vectora, vectorb, vectorc};
    MyMatrix<MyVector<double>> matrixm(3, vectorsm);
    MyVector<double> vectore = matrixm * vectord; 
    vectore.display_elements();


    delete[] &vector5;
    delete[] &vector6;
    delete[] &vector7;
    delete[] &vector8;
    delete[] &vector9;
    delete[] &vectore;

    return 0;
};
