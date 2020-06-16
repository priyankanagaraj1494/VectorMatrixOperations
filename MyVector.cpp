#include "MyVector.h"
#include <iostream>
#include <memory>
#include <iomanip>
using std::cout;

// Default constructor
template <class T>
MyVector<T>::MyVector()
    : size(1), start(new T[1]), current_capacity(0)
{
}

// Constructor with parameter
template <class T>
MyVector<T>::MyVector(unsigned int n, T value)
    : size(n), start(new T[n]), current_capacity(0)
{
    for (unsigned int index = 0; index < size; ++index)
    {
        start[index] = value;
        current_capacity++;
    }
}

// Constructor with size and initial values
template <class T>
MyVector<T>::MyVector(unsigned int n, T *values)
    : size(n), start(new T[n]), current_capacity(n)
{
    for (unsigned int index = 0; index < size; ++index)
        start[index] = values[index];
}

// Brace-enclosed initializer list constructor
template <class T>
MyVector<T>::MyVector(std::initializer_list<T> list)
    : size(list.size()), start(new T[list.size()]), current_capacity(list.size())
{
    unsigned int index = 0;
    for (auto i = list.begin(); i != list.end(); i++)
    {
        start[index] = *i;
        ++index;
    }
}

// Copy constructor
template <class T>
MyVector<T>::MyVector(const MyVector &source)
    : size(source.size), start(new T[source.size]), current_capacity(source.current_capacity)
{
    for (unsigned int index = 0; index < source.current_capacity; ++index)
        start[index] = source.start[index];
}

// Assignment constructor
template <class T>
inline MyVector<T> &MyVector<T>::operator=(const MyVector<T> &source)
{
    // If assigning the same object
    if (this == &source)
        return *this;

    /* If current vector size is greater than source vector size, 
    no allocation*/
    if (source.size <= size)
    {
        for (unsigned int index = 0; index < source.current_capacity; ++index)
        {
            start[index] = source.start[index];
            size = source.size;
            current_capacity = source.current_capacity;
            return *this;
        }
    }

    /* If current vector size is less than source vector size, 
    new dynamic allocation */
    T *new_start = new T[source.size];

    for (unsigned int index = 0; index < source.current_capacity; ++index)
        new_start[index] = source.start[index];

    delete[] start;
    size = source.size;
    current_capacity = source.current_capacity;
    start = new_start;
    return *this;
}

// Destructor
template <class T>
MyVector<T>::~MyVector()
{
    delete[] start;
}

// Display elements of vector
template <class T>
void MyVector<T>::display_elements()
{
    cout << "[";
    for (unsigned int index = 0; index < current_capacity; ++index)
        cout << start[index] << std::setw(5);
    cout << "]";
    cout << std::endl;
}

//to access the size of vector
template <class T>
unsigned int MyVector<T>::get_size()
{
    return this->size;
}

//to access the current_capacity of vector
template <class T>
unsigned int MyVector<T>::get_current_capacity() const
{
    return this->current_capacity;
}

//to access single elements
template <class T>
T &MyVector<T>::operator[](const unsigned &index)
{
    return this->start[index];
}

template <class T>
void MyVector<T>::push(T element)
{
    // If the vector is full, create a new vector in heap
    if (size == current_capacity)
    {
        T *temp = new T[2 * size];
        for (unsigned int index = 0; index < size; ++index)
        {
            temp[index] = start[index];
        }
        delete[] start;
        size *= 2;
        start = temp;
    }
    start[current_capacity] = element;
    current_capacity++;
}

// function to delete last element
template <class T>
void MyVector<T>::pop()
{
    current_capacity--;
}

//Scalar multiplication of vectors
template <class T>
MyVector<T> &operator*(MyVector<T> vector, T scalar)
{
    MyVector<T> *product = new MyVector<T>(vector.current_capacity, 0.0);
    for (unsigned int index = 0; index < vector.current_capacity; ++index)
        (*product)[index] = scalar * vector[index];
    return *product;
}

//Scalar multiplication of vectors
template <class T>
MyVector<T> &operator*(T scalar, MyVector<T> vector)
{
    return vector * scalar;
}

//Dot product
template <class T>
T &operator*(MyVector<T> vector1, MyVector<T> vector2)
{
    T *sum = new T(0.0);
    if (vector1.get_current_capacity() != vector2.get_current_capacity())
    {
        cout << "Vector sizes not equal and hence cannot be multiplied!";
        return *sum;
    }
    for (unsigned int index = 0; index < vector1.current_capacity; ++index)
        *sum = *sum + (vector1[index] * vector2[index]);
    return *sum;
}

//Vector addition
template <class T>
MyVector<T> &MyVector<T>::operator+(MyVector<T> other)
{
    if (other.get_current_capacity() != current_capacity)
    {
        cout << "Vector shapes do not match, addition cannot be performed";
        return *this;
    }
    MyVector<T> *sum = new MyVector<T>(current_capacity, 0.0);
    for (unsigned int index = 0; index < current_capacity; ++index)
        (*sum)[index] = other[index] + start[index];
    return *sum;
}