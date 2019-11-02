#pragma once

#include "Neuron.h"
#include "MathVector.h"
#include <vector>

class Layer
{
private:
	std::vector<Neuron*> neurons;

public:
	Layer(); //empty constructor
	Layer(std::vector<Neuron*> input); //copy constructor
	Layer(int n);
	~Layer(); //destructor

	void calculateLayer(Layer* prevLayer); //calculates values for itself based on input from the previous layer

	void setNeuron(int i, Neuron* n); //setter at index
	Neuron* operator[](int index); //getter at index
	Neuron* at(int index);
	unsigned int getLength();

	void randomizeLayer();
};