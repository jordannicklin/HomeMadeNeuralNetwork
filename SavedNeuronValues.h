#pragma once

#include "NeuronNetwork.h"
#include <vector>

class SavedNeuronValues
{
private:
	std::vector<std::vector<float>> _values;

public:

	SavedNeuronValues(std::vector<int> sizes);
	SavedNeuronValues(NeuronNetwork* neuronNetwork);
	~SavedNeuronValues();

	void setValues(NeuronNetwork* neuronNetwork);

	std::vector<std::vector<float>> getValues();

	std::vector<float> at(int index);
};