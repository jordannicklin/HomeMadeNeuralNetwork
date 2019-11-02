#pragma once

#include "MathVector.h"
#include "Layer.h"
#include "Neuron.h"

#include "SavedNeuronValues.h"

class NeuronNetwork
{
private:
	Layer* _inputLayer;
	std::vector<Layer*> _hiddenLayers;
	Layer* _outputLayer;

	std::vector<float> _loss;

public:
	NeuronNetwork();
	NeuronNetwork(std::vector<std::vector<std::vector<std::string>>> values);
	NeuronNetwork(int numOfLayers, int layerSizes[]);
	~NeuronNetwork();

	int loadFromFile(char* path);
	int saveToFile(char* path);

	void calcLoss(MathVector expectedResult);
	void calcHiddenLayer();

	void setInputLayer(std::vector<float> input);

	void backProp(std::vector<float> adjustments);

	void testNetwork();

	void randomize();

	Layer* getInputLayer();
	std::vector<Layer*> getHiddeLayer();
	Layer* getOutputLayer();

	void debugLoss();
};