#pragma once

#include "MathVector.h"

#include <vector>

class Neuron
{
private:
	MathVector* _weights;
	float _bias;
	float _output;

public:
	Neuron(void);
	Neuron(int size);
	~Neuron();

	float calcOutput(MathVector* input);
	float clacSigmod(float input);

	float getOutput();
	void setOutput(float output);

	float getBias();
	void setBias(float bias);

	MathVector* getWeights();
	void setWeights(float values[], int size);

	void setValues(std::vector<std::string> values);

	void randomizeBias();
	void randomizeWeights();
	void randomizeNeuron();
};