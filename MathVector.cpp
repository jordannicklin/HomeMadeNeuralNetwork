#include "MathVector.h"


float* MathVector::getValues()
{
	return _elements;
}


void MathVector::setValues(float values[], int size)
{
	for (int i = 0; i < _size; i++)
	{
		pop_back();
	}

	for (int i = 0; i < size; i++)
	{
		push_back(values[i]);
	}
}


void MathVector::setValueAt(float value, int index)
{
	//delete _elements[index];
	_elements[index] = value;
}


float MathVector::operator[](int index)
{
	return _elements[index];
}

float MathVector::dotWithVector(MathVector other)
{
	if (other.size() != _size)
	{
		return 0; //ERROR return
	}


	float result = 0;

	for (int i = 0; i < other.size(); i++)
	{
		result += other[i] * (*this)[i];
	}

	return result;
}

/////////////// 

/* initializes class
Input - starting size
Output - none */

MathVector::MathVector(int n) : _size(0), _resizeFactor(_capacity), _capacity(n < 2 ? n = 2 : n = n)
{
	_elements = new float[_capacity];
}

/* Deletes class
Input - none
Output - none */

MathVector::~MathVector()
{
	//deletes dynamic array
	delete[] _elements;

	//change pointer to point to 0
	_elements = 0;
}

/* Returns size of array (number of varibels)
Input- none
Output- size of array (number of varibels) */

int MathVector::size() const
{
	//return size
	return _size;
}

/* Returns array capcity
Input- none
Output- array capacity */

int MathVector::capacity() const
{
	//retruns capacity
	return _capacity;
}

/* Returns resize factor (original size)
Input - none
Output - resize factor */

int MathVector::resizeFactor() const
{
	//return resize factor
	return _resizeFactor;
}

/* Checks if vector is empty
Input - none
Output - if the vector empty */

bool MathVector::empty() const
{
	//returns if vector is empty
	return (_size == 0);
}

/* Adds value to array
Input- value to add
Output- none*/

void MathVector::push_back(const float& val)
{
	//checks if array is full
	if (size() == capacity())
	{
		//grows array
		reserve(_capacity + 1);
	}

	//inputs value
	_elements[_size] = val;

	//adds 1 to counter
	_size++;
}

/* Returns last value*/

float MathVector::pop_back()
{
	//sets return value as defult value
	int returnValue = -9999;

	//checks if array is empty
	if (empty())
	{
		//prints error message
		//std::cout << "error: pop from empty vector" << std::endl;
	}
	else
	{
		//sets return value as value of array in inputed index
		_size--;
		returnValue = _elements[_size];
		_elements[_size] = 0;
	}

	//returns return value
	return returnValue;
}

/* Makes sure dynamic array is bigger or equal to inputed value
Input- minimum array size
Output- none */

void MathVector::reserve(int n)
{
	//checks if array is smaller than inputed size
	if (_capacity < n)
	{
		//calculates new size
		int newSize = ((n - _capacity) % _resizeFactor) * _resizeFactor + _capacity;

		//creates new array in new size
		float* newElements = new float[newSize];

		//copys over old values to new array
		for (int i = 0; i < _size; i++)
		{
			newElements[i] = _elements[i];
		}

		//delets old array
		delete[] _elements;

		//sets array as new array
		_elements = newElements;

		//changes capacity to new capacity
		_capacity = newSize;
	}
}

/* Changes values in array to inputed value
Input- value to set
Output- none */

void MathVector::assign(float val)
{
	//Changes values in array to inputed value
	for (int i = 0; i < _size; i++)
	{
		_elements[i] = val;
	}
}

/* Overload the operator []
Input- index
Output- value in index */

int& MathVector::operator[](int n) const
{
	int returnValue = 0;

	if (n >= _capacity)
	{
		//sets return value as value in index 0 and prints error message
		returnValue = _elements[0];
	}
	else
	{
		//returns value in index n
		returnValue = _elements[n];
	}

	//returns return value
	return returnValue;
}

/* Overload the operator =
Input- vector refernce
Output- class after initializes */

MathVector& MathVector::operator=(const MathVector& other)
{
	//sets the array as a new copy of inputer class array
	delete[] _elements;

	//creates new array
	_elements = new float[other._capacity];

	//copys over old values
	for (int i = 0; i < other._capacity; i++)
	{
		_elements[i] = other._elements[i];
	}

	//copys over variables
	_size = other._size;
	_capacity = other._capacity;
	_resizeFactor = other._resizeFactor;

	//returns the class
	return *this;
}

/* Resizes the array and sets new spaces as inputed value
Input- new size, value to set
Output- none */

void MathVector::resize(int n, const float& val)
{
	//saves old capcity into new array
	int oldCapacity = _capacity;

	//resizes array
	resize(n);

	//sets value of new spaces into inputed value
	for (int i = oldCapacity; i < n; i++)
	{
		_elements[i] = val;
	}
}

/* Resizes array
Input- new size
Output- none */

void MathVector::resize(int n)
{
	//checks if n is smaller than capacity
	if (n < _capacity)
	{
		//calls function to grow array
		reserve(n);
	}
	else
	{
		//creates new array
		float* newElements = new float[n];

		//copys over old values
		for (int i = 0; i < n; i++)
		{
			newElements[i] = _elements[i];
		}

		//delets old array
		delete[] _elements;

		//sets old array as new array
		_elements = newElements;

		//sets capacity and size as n
		_size = _capacity = n;
	}
}

/* initializes class
Input - class vector
Output - none */

MathVector::MathVector(const MathVector& other) : _size(other._size), _resizeFactor(other._resizeFactor), _capacity(other._capacity)
{
	//creates new array
	_elements = new float[other._capacity];

	//copys over old values
	for (int i = 0; i < other._capacity; i++)
	{
		_elements[i] = other._elements[i];
	}
}