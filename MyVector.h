#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <memory>
#include <iomanip>

template <class T>
class MyVector
{
private:
	T *start;
	unsigned int size;
	unsigned int current_capacity;

public:
	// Default constructor
	MyVector();
	// Constructor with parameter with zero intial values
	MyVector(unsigned int n, T value);
	// Constructor with size and initial values
	MyVector(unsigned int n, T *values);
	// Brace-enclosed initializer list constructor
	MyVector(std::initializer_list<T> list);
	// Rule of three
	//Copy constructor
	MyVector(const MyVector &source);
	// Overload assignment
	MyVector<T> &operator=(const MyVector<T> &source);
	// Destructor
	~MyVector();

	// Display elements of vector
	void display_elements();
	// Get size
	unsigned int get_size();
	// Get current capacity
	unsigned int get_current_capacity() const;
	// Push elements
	void push(T element);
	// remove last element
	void pop();
	//to access single elements
	T &operator[](const unsigned &index);

	//Scalar multiplication of vectors
	template <class U>
	friend MyVector<U> &operator*(MyVector<U> vector, U scalar);
	template <class U>
	friend MyVector<U> &operator*(U scalar, MyVector<U> vector);
	//Dot product of vectors
	template <class U>
	friend U &operator*(MyVector<U> vector1, MyVector<U> vector2);
	// Addition of two vectors
	MyVector<T> &operator+(MyVector<T> other);
};
#endif