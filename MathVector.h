#pragma once

class MathVector
{
private:
	float* _elements;
	int _capacity;
	int _size;
	int _resizeFactor; 

public:
	float* getValues();
	void setValues(float values[], int size);
	float operator[](int index);
	float dotWithVector(MathVector other);

	void setValueAt(float value, int index);
	MathVector(int n);
	~MathVector();
	int size() const;
	int capacity() const;//return capacity of vector
	int resizeFactor() const; //return vector's resizeFactor
	bool empty() const; //returns true if size = 0

						//B
						//Modifiers
	void push_back(const float& val);//adds element at the end of the vector
	float pop_back();//removes and returns the last element of the vector
	void reserve(int n);//change the capacity
	void resize(int n);//change _size to n, unless n is greater than the vector's capacity
	void assign(float val);//assigns val to all elemnts
	void resize(int n, const float& val);//same as above, if new elements added their value is val

									   //C
									   //The big three (d'tor is above)
	MathVector(const MathVector& other);
	MathVector& operator=(const MathVector& other);

};