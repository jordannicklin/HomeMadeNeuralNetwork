#include "Neuron.h"
#include "MathVector.h"

#include <stdlib.h>
#include <cmath>
#include<vector>
#include <string>

Neuron::Neuron(void)
{
	_weights = new MathVector(0);
}

Neuron::Neuron(int size)
{
	_weights = new MathVector(size);
}

Neuron::~Neuron()
{
	delete _weights;
}

float Neuron::calcOutput(MathVector* input)
{
	// calculates and adds the output of the neuron
	_output = Neuron::clacSigmod(_weights->dotWithVector(*input));
	return _output;
}

float Neuron::clacSigmod(float input)
{
	return (float)((pow (2.71, input)) / (pow(2.71, input) + 1));
}

float Neuron::getOutput()
{
	return _output;
}

MathVector* Neuron::getWeights()
{
	return _weights;
}

void Neuron::setWeights(float values[], int size)
{
	_weights->setValues(values, size);
}

void Neuron::randomizeBias()
{
	// sets the value of the bias to a random value between 0 to 1
	_bias = (float)(float(rand()) / (float(RAND_MAX) + 1.0));
}

void Neuron::randomizeWeights()
{
	//sets all the weights to a random value
	for (int i = 0; i < _weights->size(); i++)
	{
		// sets the value at the index i to a random value between 0 to 1
		_weights->setValueAt((float)(float(rand()) / (float(RAND_MAX) + 1.0)), i);
	}
}

void Neuron::randomizeNeuron()
{
	randomizeWeights();
	randomizeBias();
}

void Neuron::setValues(std::vector<std::string> values)
{
	std::vector < float > floatValues;

	for (int i = 0; i < values.size() - 1; i++)
	{
		floatValues.push_back(std::stof(values.at(i)));
	}

	this->_weights->setValues(floatValues.data(), floatValues.size());

	this->_bias = std::stof(values.at(values.size() - 1));
}

float Neuron::getBias()
{
	return this->_bias;
}
void Neuron::setBias(float bias)
{
	this->_bias = bias;
}

void Neuron::setOutput(float output)
{
	this->_output = output;
}