
#include "SavedNeuronValues.h"

SavedNeuronValues::SavedNeuronValues(std::vector<int> sizes)
{
	//creates the layer in the vector
	_values = std::vector<std::vector<float>>(sizes.size());

	//creates the neurons in the vector
	for (int i = 0; i < sizes.size; i++)
	{
		_values.at(i) = std::vector<float>(sizes.at(i));
	}
}

SavedNeuronValues::SavedNeuronValues(NeuronNetwork* neuronNetwork)
{
	//creates the layer in the vector
	_values = std::vector<std::vector<float>>(neuronNetwork->getHiddeLayer().size() + 2);

	_values.at(0) = std::vector<float>(neuronNetwork->getInputLayer()->getLength());

	int layerIndex = 1;

	//copy hidden layer values
	for (layerIndex; layerIndex < neuronNetwork->getHiddeLayer().size() + 1; layerIndex++)
	{
		_values.at(layerIndex) = std::vector<float>(neuronNetwork->getInputLayer()->getLength());
	}

	layerIndex++;

	_values.at(layerIndex) = std::vector<float>(neuronNetwork->getOutputLayer()->getLength());
}

SavedNeuronValues::~SavedNeuronValues()
{

}

/* This function copys the value from the neurons from the network into the class variable
 Input- the neuron network to copy the values from
 Output- none */
void SavedNeuronValues::setValues(NeuronNetwork* neuronNetwork)
{
	//copys input layer values
	for (int i = 0; i < neuronNetwork->getInputLayer()->getLength(); i++)
	{
		_values.at(0).at(i) = neuronNetwork->getInputLayer()->at(i)->getOutput();
	}

	int layerIndex = 1;

	//copy hidden layer values
	for (layerIndex; layerIndex < neuronNetwork->getHiddeLayer().size() + 1; layerIndex++)
	{
		//copys the value of each layer in the hidden layer
		for (int neuronIndex = 0; neuronIndex < neuronNetwork->getHiddeLayer().at(layerIndex)->getLength(); neuronIndex++)
		{
			_values.at(layerIndex).at(neuronIndex) = neuronNetwork->getHiddeLayer().at(layerIndex)->at(neuronIndex)->getOutput();
		}
	}

	layerIndex++;

	//copys the output layer
	for (int i = 0; i < neuronNetwork->getOutputLayer()->getLength(); i++)
	{
		_values.at(layerIndex).at(i) = neuronNetwork->getOutputLayer()->at(i)->getOutput();
	}
}

std::vector<std::vector<float>> SavedNeuronValues::getValues()
{
	return _values;
}

std::vector<float> SavedNeuronValues::at(int index)
{
	return _values.at(index);
}